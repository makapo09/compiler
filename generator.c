#include "generator.h"
#include "bison_symtable.h"
#include "icode.h"
#include "target_code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// --- Forward Declarations & Type Definitions ---
typedef void (*generator_func_t)(quad*);
void make_operand(expr* e, vmarg* arg);
void add_incomplete_jump(unsigned instrAddr, unsigned iaddress);
void patch_incomplete_jumps();

// --- Data structures for managing constants ---
#define STARTING_SIZE 128
static double* numConsts_t = NULL;
static unsigned totalNumConsts_t = 0;
static unsigned capacityNumConsts = 0;
static char** stringConsts_t = NULL;
static unsigned totalStringConsts_t = 0;
static unsigned capacityStringConsts = 0;
static Symbol_t** userFuncs_t = NULL;
static unsigned totalUserFuncs_t = 0;
static unsigned capacityUserFuncs = 0;
static char** namedLibfuncs_t = NULL;
static unsigned totalNamedLibfuncs_t = 0;
static unsigned capacityNamedLibfuncs = 0;

typedef struct IncompleteJump {
    unsigned instrAddr;
    unsigned iaddress;
    struct IncompleteJump* next;
} IncompleteJump;
static IncompleteJump* ij_head = NULL;

// --- Stack for Return Jumps ---
typedef struct ReturnList {
    unsigned label;
    struct ReturnList* next;
} ReturnList;
static ReturnList* return_stack_top = NULL;

void push_return_list(unsigned label) {
    ReturnList* new_node = (ReturnList*)malloc(sizeof(ReturnList));
    new_node->label = label;
    new_node->next = return_stack_top;
    return_stack_top = new_node;
}

// --- Constant Management & Accessor Functions ---
double* numConsts_get() { return numConsts_t; }
unsigned totalNumConsts_get() { return totalNumConsts_t; }
char** stringConsts_get() { return stringConsts_t; }
unsigned totalStringConsts_get() { return totalStringConsts_t; }
Symbol_t** userFuncs_get() { return userFuncs_t; }
unsigned totalUserFuncs_get() { return totalUserFuncs_t; }
char** namedLibfuncs_get() { return namedLibfuncs_t; }
unsigned totalNamedLibfuncs_get() { return totalNamedLibfuncs_t; }
unsigned consts_newnumber(double n) {
    if (!numConsts_t) {
        capacityNumConsts = STARTING_SIZE;
        numConsts_t = (double*)malloc(capacityNumConsts * sizeof(double));
    } else if (totalNumConsts_t >= capacityNumConsts) {
        capacityNumConsts *= 2;
        numConsts_t = (double*)realloc(numConsts_t, capacityNumConsts * sizeof(double));
    }
    numConsts_t[totalNumConsts_t] = n;
    return totalNumConsts_t++;
}
unsigned consts_newstring(char* s) {
    if (!stringConsts_t) {
        capacityStringConsts = STARTING_SIZE;
        stringConsts_t = (char**)malloc(capacityStringConsts * sizeof(char*));
    } else if (totalStringConsts_t >= capacityStringConsts) {
        capacityStringConsts *= 2;
        stringConsts_t = (char**)realloc(stringConsts_t, capacityStringConsts * sizeof(char*));
    }
    stringConsts_t[totalStringConsts_t] = strdup(s);
    return totalStringConsts_t++;
}
unsigned userfuncs_newfunc(Symbol_t* sym) {
    for(unsigned i = 0; i < totalUserFuncs_t; ++i) {
        if (userFuncs_t[i] == sym) return i;
    }
    if (!userFuncs_t) {
        capacityUserFuncs = STARTING_SIZE;
        userFuncs_t = (Symbol_t**)malloc(capacityUserFuncs * sizeof(Symbol_t*));
    } else if (totalUserFuncs_t >= capacityUserFuncs) {
        capacityUserFuncs *= 2;
        userFuncs_t = (Symbol_t**)realloc(userFuncs_t, capacityUserFuncs * sizeof(Symbol_t*));
    }
    userFuncs_t[totalUserFuncs_t] = sym;
    return totalUserFuncs_t++;
}
unsigned libfuncs_newused(const char* s) {
    for (unsigned i = 0; i < totalNamedLibfuncs_t; i++) {
        if (strcmp(namedLibfuncs_t[i], s) == 0) return i;
    }
    if (!namedLibfuncs_t) {
        capacityNamedLibfuncs = STARTING_SIZE;
        namedLibfuncs_t = (char**)malloc(capacityNamedLibfuncs * sizeof(char*));
    } else if (totalNamedLibfuncs_t >= capacityNamedLibfuncs) {
        capacityNamedLibfuncs *= 2;
        namedLibfuncs_t = (char**)realloc(namedLibfuncs_t, capacityNamedLibfuncs * sizeof(char*));
    }
    namedLibfuncs_t[totalNamedLibfuncs_t] = strdup(s);
    return totalNamedLibfuncs_t++;
}

// --- Operand Generation ---
void make_operand(expr* e, vmarg* arg) {
    if (e == NULL) {
        arg->type = NIL_A;
        arg->val = -1;
        return;
    }
    switch (e->type) {
        case var_e:
        case tableitem_e:
        case programfunc_e:
        case libraryfunc_e:
        case arithexpr_e:
        case boolexpr_e:
        case assignexpr_e:
        case newtable_e:
        {
            if (!e->sym) {
                arg->type = NIL_A;
                arg->val = -1;
                return;
            }
            arg->val = e->sym->scope;
            switch (e->sym->type) {
                case GLOBAL_VAR: arg->type = GLOBAL_A; break;
                case LOCAL_VAR:  arg->type = LOCAL_A;  break;
                case FORMAL_ARG: arg->type = FORMAL_A; break;
                default: break;
            }
            if (e->type == programfunc_e) {
                arg->type = USERFUNC_A;
                arg->val = userfuncs_newfunc(e->sym);
            } else if (e->type == libraryfunc_e) {
                arg->type = LIBFUNC_A;
                arg->val = libfuncs_newused(e->sym->name);
            }
            break;
        }
        case constnum_e:    arg->type = NUMBER_A; arg->val = consts_newnumber(e->numConst); break;
        case constbool_e:   arg->type = BOOL_A; arg->val = e->boolConst; break;
        case conststring_e: arg->type = STRING_A; arg->val = consts_newstring(e->strConst); break;
        case nil_e:         arg->type = NIL_A; break;
        default: assert(0);
    }
}

// --- Specific Quad to Instruction Generators ---
void generate_ASSIGN(quad* q); void generate_ADD(quad* q); void generate_SUB(quad* q); void generate_MUL(quad* q); void generate_DIV(quad* q); void generate_MOD(quad* q); void generate_UMINUS(quad* q); void generate_NEWTABLE(quad* q); void generate_TABLEGETELEM(quad* q); void generate_TABLESETELEM(quad* q); void generate_JUMP(quad* q); void generate_IF_EQ(quad* q); void generate_IF_NOTEQ(quad* q); void generate_IF_GREATER(quad* q); void generate_IF_GREATEREQ(quad* q); void generate_IF_LESS(quad* q); void generate_IF_LESSEQ(quad* q); void generate_PARAM(quad* q); void generate_CALL(quad* q); void generate_GETRETVAL(quad* q); void generate_FUNCSTART(quad* q); void generate_FUNCEND(quad* q); void generate_RETURN(quad* q);

void generate(vmopcode op, quad* q) {
    instruction t;
    t.opcode = op;
    t.srcLine = q->line;
    make_operand(q->result, &t.result);
    make_operand(q->arg1, &t.arg1);
    make_operand(q->arg2, &t.arg2);
    q->taddress = currInstr;
    emit_instruction(t.opcode, &t.result, &t.arg1, &t.arg2, t.srcLine);
}
void generate_relational(vmopcode op, quad* q) {
    instruction t;
    t.opcode = op;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.arg1);
    make_operand(q->arg2, &t.arg2);
    t.result.type = LABEL_A;
    t.result.val = q->label;
    add_incomplete_jump(currInstr, q->label);
    q->taddress = currInstr;
    emit_instruction(t.opcode, &t.result, &t.arg1, &t.arg2, t.srcLine);
}

void generate_ASSIGN(quad* q) { generate(ASSIGN_V, q); }
void generate_ADD(quad* q) { generate(ADD_V, q); }
void generate_SUB(quad* q) { generate(SUB_V, q); }
void generate_MUL(quad* q) { generate(MUL_V, q); }
void generate_DIV(quad* q) { generate(DIV_V, q); }
void generate_MOD(quad* q) { generate(MOD_V, q); }
void generate_UMINUS(quad* q) {
    instruction t;
    t.opcode = SUB_V;
    t.srcLine = q->line;
    make_operand(q->result, &t.result);
    t.arg1.type = NUMBER_A;
    t.arg1.val = consts_newnumber(0);
    make_operand(q->arg1, &t.arg2);
    q->taddress = currInstr;
    emit_instruction(t.opcode, &t.result, &t.arg1, &t.arg2, t.srcLine);
}
void generate_NEWTABLE(quad* q) { generate(NEWTABLE_V, q); }
void generate_TABLEGETELEM(quad* q) { generate(TABLEGETELEM_V, q); }
void generate_TABLESETELEM(quad* q) { generate(TABLESETELEM_V, q); }
void generate_JUMP(quad* q) { generate_relational(JUMP_V, q); }
void generate_IF_EQ(quad* q) { generate_relational(JEQ_V, q); }
void generate_IF_NOTEQ(quad* q) { generate_relational(JNE_V, q); }
void generate_IF_GREATER(quad* q) { generate_relational(JGT_V, q); }
void generate_IF_GREATEREQ(quad* q) { generate_relational(JGE_V, q); }
void generate_IF_LESS(quad* q) { generate_relational(JLT_V, q); }
void generate_IF_LESSEQ(quad* q) { generate_relational(JLE_V, q); }
void generate_PARAM(quad* q) { generate(PUSHARG_V, q); }
void generate_CALL(quad* q) { generate(CALL_V, q); }
void generate_GETRETVAL(quad* q) {
    instruction t;
    t.opcode = ASSIGN_V;
    t.srcLine = q->line;
    make_operand(q->result, &t.result);
    t.arg1.type = RETVAL_A;
    q->taddress = currInstr;
    emit_instruction(t.opcode, &t.result, &t.arg1, NULL, t.srcLine);
}
void generate_FUNCSTART(quad* q) {
    push_return_list(0);
    generate(FUNCENTER_V, q);
}
void generate_FUNCEND(quad* q) {
    ReturnList* current = return_stack_top;
    while(current && current->label != 0) {
        patchlabel(current->label, currInstr);
        ReturnList* next = current->next;
        free(current);
        current = next;
    }
    if (current) {
        return_stack_top = current->next;
        free(current);
    }
    generate(FUNCEXIT_V, q);
}
void generate_RETURN(quad* q) {
    instruction t;
    t.opcode = ASSIGN_V;
    t.srcLine = q->line;
    t.result.type = RETVAL_A;
    make_operand(q->arg1, &t.arg1);
    q->taddress = currInstr;
    emit_instruction(t.opcode, &t.result, &t.arg1, NULL, t.srcLine);
    
    instruction jump_instr;
    jump_instr.opcode = JUMP_V;
    jump_instr.srcLine = q->line;
    jump_instr.result.type = LABEL_A;
    jump_instr.result.val = 0; 
    push_return_list(currInstr); 
    emit_instruction(jump_instr.opcode, &jump_instr.result, NULL, NULL, jump_instr.srcLine);
}

generator_func_t generators[] = {
    generate_ASSIGN, generate_ADD, generate_SUB, generate_MUL, generate_DIV, generate_MOD,
    generate_UMINUS, NULL, NULL, NULL, 
    generate_IF_EQ, generate_IF_NOTEQ, generate_IF_LESSEQ, generate_IF_GREATEREQ, generate_IF_LESS, generate_IF_GREATER,
    generate_JUMP, generate_CALL, generate_PARAM,
    generate_RETURN, generate_GETRETVAL, generate_FUNCSTART, generate_FUNCEND,
    generate_NEWTABLE, generate_TABLEGETELEM, generate_TABLESETELEM
};

// --- Main Generation & Backpatching ---
void generate_instructions(void) {
    for (unsigned i = 0; i < currQuad; ++i) {
        quads[i].taddress = currInstr;
        if (quads[i].op < (sizeof(generators)/sizeof(generators[0])) && generators[quads[i].op]) {
            generators[quads[i].op](&quads[i]);
        }
    }
    patch_incomplete_jumps();
}

void add_incomplete_jump(unsigned instrAddr, unsigned iaddress) {
    IncompleteJump* new_jump = (IncompleteJump*)malloc(sizeof(IncompleteJump));
    new_jump->instrAddr = instrAddr;
    new_jump->iaddress = iaddress;
    new_jump->next = ij_head;
    ij_head = new_jump;
}

void patch_incomplete_jumps() {
    for (IncompleteJump* current = ij_head; current; current = current->next) {
        if (current->iaddress == currQuad) {
            instructions[current->instrAddr].result.val = currInstr;
        } else {
            assert(current->iaddress < currQuad);
            instructions[current->instrAddr].result.val = quads[current->iaddress].taddress;
        }
    }
}

// --- File Writing Functions ---
void write_binary_target_code(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) { perror("Cannot open binary file for writing"); return; }
    
    unsigned magic_number = 340200501;
    fwrite(&magic_number, sizeof(unsigned), 1, f);
    fwrite(&totalStringConsts_t, sizeof(unsigned), 1, f);
    for (unsigned i = 0; i < totalStringConsts_t; i++) {
        unsigned len = strlen(stringConsts_t[i]);
        fwrite(&len, sizeof(unsigned), 1, f);
        fwrite(stringConsts_t[i], sizeof(char), len, f);
    }
    fwrite(&totalNumConsts_t, sizeof(unsigned), 1, f);
    fwrite(numConsts_t, sizeof(double), totalNumConsts_t, f);
    fwrite(&totalUserFuncs_t, sizeof(unsigned), 1, f);
    for (unsigned i = 0; i < totalUserFuncs_t; i++) {
        Symbol_t* sym = userFuncs_t[i];
        unsigned addr = sym->scope; // Placeholder
        unsigned local_size = 0; // Placeholder
        fwrite(&addr, sizeof(unsigned), 1, f);
        fwrite(&local_size, sizeof(unsigned), 1, f);
        unsigned len = strlen(sym->name);
        fwrite(&len, sizeof(unsigned), 1, f);
        fwrite(sym->name, sizeof(char), len, f);
    }
    fwrite(&totalNamedLibfuncs_t, sizeof(unsigned), 1, f);
    for (unsigned i = 0; i < totalNamedLibfuncs_t; i++) {
        unsigned len = strlen(namedLibfuncs_t[i]);
        fwrite(&len, sizeof(unsigned), 1, f);
        fwrite(namedLibfuncs_t[i], sizeof(char), len, f);
    }
    fwrite(&currInstr, sizeof(unsigned), 1, f);
    fwrite(instructions, sizeof(instruction), currInstr, f);
    fclose(f);
}

void write_text_target_code(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) { perror("Cannot open text target file for writing"); return; }
    fprintf(f, "--- Target Code ---\n");
    print_instructions(f);
    fclose(f);
}
