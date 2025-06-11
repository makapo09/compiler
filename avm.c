#include "avm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

// --- Forward Declarations for Execute Functions ---
void execute_assign(instruction* instr);
void execute_add(instruction* instr);
void execute_sub(instruction* instr);
void execute_mul(instruction* instr);
void execute_div(instruction* instr);
void execute_mod(instruction* instr);
void execute_jump(instruction* instr);
void execute_jeq(instruction* instr);
void execute_jne(instruction* instr);
void execute_jle(instruction* instr);
void execute_jge(instruction* instr);
void execute_jlt(instruction* instr);
void execute_jgt(instruction* instr);
void execute_call(instruction* instr);
void execute_pusharg(instruction* instr);
void execute_funcenter(instruction* instr);
void execute_funcexit(instruction* instr);
void execute_newtable(instruction* instr);
void execute_tablegetelem(instruction* instr);
void execute_tablesetelem(instruction* instr);
void execute_nop(instruction* instr);


// --- Global VM State ---
avm_memcell stack[AVM_STACKSIZE];
avm_memcell ax, bx, cx, retval;
unsigned top, topsp;
unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned totalActuals = 0;

// --- Loaded Program Data ---
static instruction* code = NULL;
static unsigned codeSize = 0;
static double* numConsts = NULL;
static char** stringConsts = NULL;
struct userfunc* userFuncs = NULL;
unsigned totalUserFuncs = 0;
static char** namedLibfuncs = NULL;

// --- Library Function Management ---
typedef struct libfunc_entry {
    char* id;
    library_func_t func;
    struct libfunc_entry* next;
} libfunc_entry;
static libfunc_entry* libfuncs = NULL;


// --- Error Handling ---
void avm_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "AVM Error (line %u): ", currLine);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    executionFinished = 1;
}

void avm_warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "AVM Warning: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

// --- Memory Cell Management ---
void avm_memcellclear(avm_memcell* m) {
    if (m && m->type == string_m && m->data.strVal) {
        free(m->data.strVal);
    } else if (m && m->type == table_m && m->data.tableVal) {
        avm_tabledecrefcounter(m->data.tableVal);
    }
    if(m) m->type = undef_m;
}

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
    if (lv == rv) return;
    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));
    if (lv->type == string_m) {
        lv->data.strVal = strdup(rv->data.strVal);
    } else if (lv->type == table_m) {
        avm_tableincrefcounter(lv->data.tableVal);
    }
}


// --- Table Implementation ---
static unsigned avm_hash_number(double num) { return ((unsigned)num) % AVM_TABLE_HASHSIZE; }
static unsigned avm_hash_string(const char* str) {
    unsigned hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *(str++);
    return hash % AVM_TABLE_HASHSIZE;
}
avm_table* avm_tablenew(void) {
    avm_table* t = (avm_table*)malloc(sizeof(avm_table));
    t->refCounter = 0;
    t->total = 0;
    t->numIndexed = (avm_table_bucket**)calloc(AVM_TABLE_HASHSIZE, sizeof(avm_table_bucket*));
    t->strIndexed = (avm_table_bucket**)calloc(AVM_TABLE_HASHSIZE, sizeof(avm_table_bucket*));
    return t;
}
void avm_tableincrefcounter(avm_table* t) { ++t->refCounter; }
void avm_tabledecrefcounter(avm_table* t) {
    assert(t->refCounter > 0);
    if (--t->refCounter == 0) {
        avm_tablebucketsdestroy(t->numIndexed);
        avm_tablebucketsdestroy(t->strIndexed);
        free(t);
    }
}
void avm_tablebucketsdestroy(avm_table_bucket** p) {
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        for (avm_table_bucket* b = p[i]; b;) {
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = NULL;
    }
    free(p);
}
avm_memcell* avm_tablegetelem(avm_table* t, avm_memcell* key) {
    unsigned hash_val;
    avm_table_bucket* bucket_list;

    if (key->type == number_m) {
        hash_val = avm_hash_number(key->data.numVal);
        bucket_list = t->numIndexed[hash_val];
    } else if (key->type == string_m) {
        hash_val = avm_hash_string(key->data.strVal);
        bucket_list = t->strIndexed[hash_val];
    } else {
        avm_error("Unsupported table key type.");
        return NULL;
    }

    for (avm_table_bucket* curr = bucket_list; curr; curr = curr->next) {
        if (curr->key.type == key->type) {
            if (key->type == number_m && curr->key.data.numVal == key->data.numVal) return &curr->value;
            if (key->type == string_m && strcmp(curr->key.data.strVal, key->data.strVal) == 0) return &curr->value;
        }
    }
    return NULL; // Not found
}
void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value) {
    unsigned hash_val;
    avm_table_bucket** bucket_list_head;

    if (key->type == number_m) {
        hash_val = avm_hash_number(key->data.numVal);
        bucket_list_head = &t->numIndexed[hash_val];
    } else  if (key->type == string_m){
        hash_val = avm_hash_string(key->data.strVal);
        bucket_list_head = &t->strIndexed[hash_val];
    } else {
        avm_error("Unsupported table key type.");
        return;
    }
    
    for (avm_table_bucket* curr = *bucket_list_head; curr; curr = curr->next) {
        if (curr->key.type == key->type) {
            if ((key->type == number_m && curr->key.data.numVal == key->data.numVal) ||
                (key->type == string_m && strcmp(curr->key.data.strVal, key->data.strVal) == 0)) {
                avm_assign(&curr->value, value);
                return;
            }
        }
    }

    avm_table_bucket* new_bucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
    avm_assign(&new_bucket->key, key);
    avm_assign(&new_bucket->value, value);
    new_bucket->next = *bucket_list_head;
    *bucket_list_head = new_bucket;
    t->total++;
}


// --- Type Conversion ---
char* avm_tostring(avm_memcell* m) {
    if (!m || m->type == undef_m) return strdup("undefined");
    static char buffer[512];
    switch(m->type) {
        case number_m: sprintf(buffer, "%.3f", m->data.numVal); break;
        case string_m: return strdup(m->data.strVal);
        case bool_m: return strdup(m->data.boolVal ? "true" : "false");
        case table_m: return avm_table_tostring(m->data.tableVal);
        case userfunc_m: sprintf(buffer, "user function %s (%u)", userFuncs[m->data.funcVal].id, m->data.funcVal); break;
        case libfunc_m: sprintf(buffer, "library function %s", m->data.libfuncVal); break;
        case nil_m: return strdup("nil");
        default: assert(0);
    }
    return strdup(buffer);
}
char* avm_table_tostring(avm_table* t) {
    char* result = (char*)malloc(4096);
    strcpy(result, "[");
    int first = 1;
    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        for (avm_table_bucket* b = t->numIndexed[i]; b; b = b->next) {
            if (!first) strcat(result, ", "); else first = 0;
            char* keyStr = avm_tostring(&b->key);
            char* valStr = avm_tostring(&b->value);
            sprintf(result + strlen(result), " {%s: %s}", keyStr, valStr);
            free(keyStr); free(valStr);
        }
        for (avm_table_bucket* b = t->strIndexed[i]; b; b = b->next) {
            if (!first) strcat(result, ", "); else first = 0;
            char* keyStr = avm_tostring(&b->key);
            char* valStr = avm_tostring(&b->value);
            sprintf(result + strlen(result), " {%s: %s}", keyStr, valStr);
            free(keyStr); free(valStr);
        }
    }
    strcat(result, " ]");
    return result;
}
double avm_tonumber(avm_memcell* m) {
    if (!m || m->type == undef_m) return 0;
    switch(m->type) {
        case number_m: return m->data.numVal;
        case string_m: return atof(m->data.strVal);
        case bool_m:   return m->data.boolVal ? 1.0 : 0.0;
        case nil_m:    return 0;
        default:       avm_error("Cannot convert %s to number", avm_tostring(m)); return 0;
    }
}
unsigned char avm_tobool(avm_memcell* m) {
    if (!m || m->type == undef_m) return 0;
    switch(m->type) {
        case number_m: return m->data.numVal != 0;
        case string_m: return m->data.strVal[0] != '\0';
        case bool_m:   return m->data.boolVal;
        case table_m:  return 1;
        case userfunc_m: return 1;
        case libfunc_m:  return 1;
        case nil_m:      return 0;
        default:         assert(0); return 0;
    }
}


// --- Library Function Management ---
void avm_registerlibfunc(const char* id, library_func_t addr) {
    libfunc_entry* new_entry = (libfunc_entry*)malloc(sizeof(libfunc_entry));
    new_entry->id = strdup(id);
    new_entry->func = addr;
    new_entry->next = libfuncs;
    libfuncs = new_entry;
}
library_func_t avm_getlibraryfunc(const char* id) {
    for (libfunc_entry* p = libfuncs; p; p = p->next)
        if (strcmp(p->id, id) == 0) return p->func;
    return NULL;
}
void libfunc_print(void) {
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; ++i) {
        char* s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
    }
    printf("\n");
}
void libfunc_input(void) {
    char buffer[1024];
    avm_memcellclear(&retval);
    if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;
        retval.type = string_m;
        retval.data.strVal = strdup(buffer);
    } else {
        retval.type = nil_m;
    }
}
void libfunc_typeof(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("typeof expects 1 argument"); return; }
    avm_memcellclear(&retval);
    retval.type = string_m;
    switch(avm_getactual(0)->type){
        case number_m: retval.data.strVal = strdup("number"); break;
        case string_m: retval.data.strVal = strdup("string"); break;
        case bool_m: retval.data.strVal = strdup("boolean"); break;
        case table_m: retval.data.strVal = strdup("table"); break;
        case userfunc_m: retval.data.strVal = strdup("userfunction"); break;
        case libfunc_m: retval.data.strVal = strdup("libraryfunction"); break;
        case nil_m: retval.data.strVal = strdup("nil"); break;
        default: retval.data.strVal = strdup("undefined");
    }
}
void libfunc_totalarguments(void) {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if (p_topsp >= AVM_STACKSIZE) {
        avm_warning("totalarguments called outside a function context.");
        retval.type = nil_m;
    } else {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    }
}
void libfunc_argument(void) {
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if (p_topsp >= AVM_STACKSIZE) {
        avm_error("argument() called outside a function context");
        return;
    }
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("argument() takes one argument (index)"); return; }
    avm_memcell* arg_idx_cell = avm_getactual(0);
    if (arg_idx_cell->type != number_m) { avm_error("argument() index must be a number"); return; }
    
    unsigned arg_idx = (unsigned)arg_idx_cell->data.numVal;
    unsigned total_args_prev = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);

    if (arg_idx >= total_args_prev) {
        avm_error("argument index %u is out of bounds (total arguments: %u)", arg_idx, total_args_prev);
        retval.type = nil_m;
    } else {
        avm_memcell* arg_to_return = &stack[p_topsp + AVM_STACKENV_SIZE + 1 + arg_idx];
        avm_assign(&retval, arg_to_return);
    }
}
void libfunc_objectmemberkeys(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("objectmemberkeys() expects one table argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != table_m) { avm_error("objectmemberkeys() argument must be a table."); return; }

    avm_memcell* result_table_cell = &retval;
    avm_memcellclear(result_table_cell);
    result_table_cell->type = table_m;
    result_table_cell->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(result_table_cell->data.tableVal);
    
    unsigned index = 0;
    avm_table* t = arg->data.tableVal;

    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        for (avm_table_bucket* b = t->numIndexed[i]; b; b = b->next) {
            avm_memcell key_cell; key_cell.type = number_m; key_cell.data.numVal = index++;
            avm_tablesetelem(result_table_cell->data.tableVal, &key_cell, &b->key);
        }
        for (avm_table_bucket* b = t->strIndexed[i]; b; b = b->next) {
            avm_memcell key_cell; key_cell.type = number_m; key_cell.data.numVal = index++;
            avm_tablesetelem(result_table_cell->data.tableVal, &key_cell, &b->key);
        }
    }
}
void libfunc_objecttotalmembers(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("objecttotalmembers() expects one table argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != table_m) { avm_error("objecttotalmembers() argument must be a table."); return; }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = arg->data.tableVal->total;
}
void libfunc_objectcopy(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("objectcopy() expects one table argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != table_m) { avm_error("objectcopy() argument must be a table."); return; }
    
    avm_memcell* new_table_cell = &retval;
    avm_memcellclear(new_table_cell);
    new_table_cell->type = table_m;
    new_table_cell->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(new_table_cell->data.tableVal);
    
    avm_table* t_orig = arg->data.tableVal;
    avm_table* t_copy = new_table_cell->data.tableVal;

    for (unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        for (avm_table_bucket* b = t_orig->numIndexed[i]; b; b = b->next) avm_tablesetelem(t_copy, &b->key, &b->value);
        for (avm_table_bucket* b = t_orig->strIndexed[i]; b; b = b->next) avm_tablesetelem(t_copy, &b->key, &b->value);
    }
}
void libfunc_strtonum(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("strtonum() expects one string argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != string_m) { avm_error("strtonum() argument must be a string."); return; }
    
    avm_memcellclear(&retval);
    char* end;
    double val = strtod(arg->data.strVal, &end);
    if (*end) {
        retval.type = nil_m;
    } else {
        retval.type = number_m;
        retval.data.numVal = val;
    }
}
void libfunc_sqrt(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("sqrt() expects one numeric argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != number_m) { avm_error("sqrt() argument must be a number."); return; }

    avm_memcellclear(&retval);
    if (arg->data.numVal < 0) {
        retval.type = nil_m;
    } else {
        retval.type = number_m;
        retval.data.numVal = sqrt(arg->data.numVal);
    }
}
void libfunc_cos(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("cos() expects one numeric argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != number_m) { avm_error("cos() argument must be a number."); return; }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = cos(arg->data.numVal * M_PI / 180.0);
}
void libfunc_sin(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) { avm_error("sin() expects one numeric argument."); return; }
    avm_memcell* arg = avm_getactual(0);
    if (arg->type != number_m) { avm_error("sin() argument must be a number."); return; }

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = sin(arg->data.numVal * M_PI / 180.0);
}


// --- AVM Initialization & Loading ---
void avm_initialize(void) {
    top = AVM_STACKSIZE - 1;
    topsp = AVM_STACKSIZE - 1;
    for (int i = 0; i < AVM_STACKSIZE; ++i) stack[i].type = undef_m;
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("input", libfunc_input);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("totalarguments", libfunc_totalarguments);
    avm_registerlibfunc("argument", libfunc_argument);
    avm_registerlibfunc("strtonum", libfunc_strtonum);
    avm_registerlibfunc("sqrt", libfunc_sqrt);
    avm_registerlibfunc("cos", libfunc_cos);
    avm_registerlibfunc("sin", libfunc_sin);
    avm_registerlibfunc("objectmemberkeys", libfunc_objectmemberkeys);
    avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
    avm_registerlibfunc("objectcopy", libfunc_objectcopy);
}
void avm_load_program(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) { fprintf(stderr, "Cannot open binary file: %s\n", filename); exit(1); }
    unsigned magic;
    fread(&magic, sizeof(unsigned), 1, fp);
    if (magic != 340200501) { fprintf(stderr, "Invalid binary file format\n"); exit(1); }
    
    unsigned total_str_consts, total_num_consts, total_lib_funcs;
    fread(&total_str_consts, sizeof(unsigned), 1, fp);
    stringConsts = (char**)malloc(total_str_consts * sizeof(char*));
    for (unsigned i = 0; i < total_str_consts; i++) {
        unsigned len; fread(&len, sizeof(unsigned), 1, fp);
        stringConsts[i] = (char*)malloc(len + 1);
        fread(stringConsts[i], sizeof(char), len, fp);
        stringConsts[i][len] = '\0';
    }
    
    fread(&total_num_consts, sizeof(unsigned), 1, fp);
    numConsts = (double*)malloc(total_num_consts * sizeof(double));
    fread(numConsts, sizeof(double), total_num_consts, fp);
    
    fread(&totalUserFuncs, sizeof(unsigned), 1, fp);
    userFuncs = (struct userfunc*)malloc(totalUserFuncs * sizeof(struct userfunc));
    for (unsigned i = 0; i < totalUserFuncs; i++) {
        fread(&userFuncs[i].address, sizeof(unsigned), 1, fp);
        fread(&userFuncs[i].localSize, sizeof(unsigned), 1, fp);
        unsigned len; fread(&len, sizeof(unsigned), 1, fp);
        userFuncs[i].id = (char*)malloc(len + 1);
        fread(userFuncs[i].id, sizeof(char), len, fp);
        userFuncs[i].id[len] = '\0';
    }
    
    fread(&total_lib_funcs, sizeof(unsigned), 1, fp);
    namedLibfuncs = (char**)malloc(total_lib_funcs * sizeof(char*));
    for (unsigned i = 0; i < total_lib_funcs; i++) {
        unsigned len; fread(&len, sizeof(unsigned), 1, fp);
        namedLibfuncs[i] = (char*)malloc(len + 1);
        fread(namedLibfuncs[i], sizeof(char), len, fp);
        namedLibfuncs[i][len] = '\0';
    }
    
    fread(&codeSize, sizeof(unsigned), 1, fp);
    code = (instruction*)malloc(codeSize * sizeof(instruction));
    fread(code, sizeof(instruction), codeSize, fp);
    
    fclose(fp);
}

// --- AVM Helper Functions ---
unsigned avm_get_envvalue(unsigned i) {
    if (i >= AVM_STACKSIZE || stack[i].type != number_m) {
        avm_error("Invalid environment value access at stack index %u.", i);
        executionFinished = 1;
        return 0;
    }
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == (double)val);
    return val;
}
unsigned avm_totalactuals(void) {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}
avm_memcell* avm_getactual(unsigned i) {
    if (i >= avm_totalactuals()) {
        avm_error("Accessing out-of-bounds actual argument %u.", i);
        return NULL;
    }
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}


// --- Operand Translation ---
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg) {
    switch (arg->type) {
        case GLOBAL_A: return &stack[AVM_STACKSIZE - 1 - arg->val];
        case LOCAL_A:  return &stack[topsp - arg->val];
        case FORMAL_A: return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
        case RETVAL_A: return &retval;
        case NUMBER_A:
            reg->type = number_m;
            reg->data.numVal = numConsts[arg->val];
            return reg;
        case STRING_A:
            reg->type = string_m;
            reg->data.strVal = strdup(stringConsts[arg->val]);
            return reg;
        case BOOL_A:
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        case NIL_A:
            reg->type = nil_m;
            return reg;
        case USERFUNC_A:
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        case LIBFUNC_A:
            reg->type = libfunc_m;
            reg->data.libfuncVal = strdup(namedLibfuncs[arg->val]);
            return reg;
        default: assert(0); return NULL;
    }
}


// --- Execute Functions ---
void execute_assign(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell* rv = avm_translate_operand(&instr->arg1, &ax);
    if (!lv || !rv) return;
    avm_assign(lv, rv);
}
void execute_arithmetic(instruction* instr, double (*op)(double, double)) {
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (!lv || !rv1 || !rv2) return;
    if (rv1->type != number_m || rv2->type != number_m) { avm_error("Arithmetic on non-numbers."); return; }
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = op(rv1->data.numVal, rv2->data.numVal);
}
double add_op(double x, double y) { return x + y; }
double sub_op(double x, double y) { return x - y; }
double mul_op(double x, double y) { return x * y; }
double div_op(double x, double y) { if(y==0) {avm_error("Division by zero."); return 0;} return x / y; }
double mod_op(double x, double y) { if(y==0) {avm_error("Modulo by zero."); return 0;} return fmod(x, y); }
void execute_add(instruction* instr) { execute_arithmetic(instr, add_op); }
void execute_sub(instruction* instr) { execute_arithmetic(instr, sub_op); }
void execute_mul(instruction* instr) { execute_arithmetic(instr, mul_op); }
void execute_div(instruction* instr) { execute_arithmetic(instr, div_op); }
void execute_mod(instruction* instr) { execute_arithmetic(instr, mod_op); }
void execute_jump(instruction* instr) { pc = instr->result.val; }
void execute_jeq(instruction* instr) { 
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (executionFinished) return;
    if (avm_tobool(rv1) == avm_tobool(rv2)) pc = instr->result.val;
}
void execute_jne(instruction* instr) {
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (executionFinished) return;
    if (avm_tobool(rv1) != avm_tobool(rv2)) pc = instr->result.val;
}
void execute_jle(instruction* instr) { 
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (executionFinished) return;
    if (rv1->type != number_m || rv2->type != number_m) { avm_error("Comparison on non-numbers."); return; }
    if (rv1->data.numVal <= rv2->data.numVal) pc = instr->result.val;
}
void execute_jge(instruction* instr) { 
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (executionFinished) return;
    if (rv1->type != number_m || rv2->type != number_m) { avm_error("Comparison on non-numbers."); return; }
    if (rv1->data.numVal >= rv2->data.numVal) pc = instr->result.val;
}
void execute_jlt(instruction* instr) { 
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (executionFinished) return;
    if (rv1->type != number_m || rv2->type != number_m) { avm_error("Comparison on non-numbers."); return; }
    if (rv1->data.numVal < rv2->data.numVal) pc = instr->result.val;
}
void execute_jgt(instruction* instr) { 
    avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
    if (executionFinished) return;
    if (rv1->type != number_m || rv2->type != number_m) { avm_error("Comparison on non-numbers."); return; }
    if (rv1->data.numVal > rv2->data.numVal) pc = instr->result.val;
}

void execute_call(instruction* instr) {
    avm_memcell* func = avm_translate_operand(&instr->arg1, &ax);
    if (!func) { avm_error("Call to null expression."); return; }

    stack[top].type = number_m; stack[top--].data.numVal = pc + 1;
    stack[top].type = number_m; stack[top--].data.numVal = topsp;
    stack[top].type = number_m; stack[top--].data.numVal = totalActuals;
    
    switch(func->type) {
        case userfunc_m:
            pc = userFuncs[func->data.funcVal].address;
            assert(pc < codeSize);
            break;
        
        case string_m:
        case libfunc_m: {
            char* func_name = (func->type == string_m) ? func->data.strVal : func->data.libfuncVal;
            library_func_t f = avm_getlibraryfunc(func_name);
            if (!f) { 
                avm_error("Unsupported lib func '%s' called.", func_name); 
                return;
            }
            topsp = top;
            totalActuals = 0;
            f();
            if (!executionFinished) execute_funcexit(NULL);
            break;
        }

        default: {
            char* s = avm_tostring(func);
            avm_error("Call to non-function value: %s", s);
            free(s);
            break;
        }
    }
}
void execute_pusharg(instruction* instr) {
    avm_memcell* arg = avm_translate_operand(&instr->arg1, &ax);
    if (!arg) return;
    avm_assign(&stack[top], arg);
    totalActuals++;
    top--;
}
void execute_funcenter(instruction* instr) {
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func && func->type == userfunc_m);
    
    topsp = top;
    totalActuals = 0;
    
    top = topsp - userFuncs[func->data.funcVal].localSize;
}
void execute_funcexit(instruction* instr) {
    unsigned old_topsp = topsp;
    top = avm_get_envvalue(old_topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(old_topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(old_topsp + AVM_SAVEDTOPSP_OFFSET);
}
void execute_newtable(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    if (!lv) return;
    avm_memcellclear(lv);
    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}
void execute_tablegetelem(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell* t = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &bx);
    if (!lv || !t || !i) return;
    avm_memcellclear(lv);
    if (t->type != table_m) { avm_error("Illegal use of type %s as table.", avm_tostring(t)); return; }
    avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
    if (content) avm_assign(lv, content); else lv->type = nil_m;
}
void execute_tablesetelem(instruction* instr) {
    avm_memcell* t = avm_translate_operand(&instr->result, NULL);
    avm_memcell* i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* c = avm_translate_operand(&instr->arg2, &bx);
    if (!t || !i || !c) return;
    if (t->type != table_m) { avm_error("Illegal use of type %s as table.", avm_tostring(t)); return; }
    avm_tablesetelem(t->data.tableVal, i, c);
}
void execute_nop(instruction* instr) {}


// --- Execute Cycle ---
typedef void (*execute_func_t)(instruction*);
execute_func_t executeFuncs[] = {
    execute_assign, execute_add, execute_sub, execute_mul, execute_div, execute_mod,
    execute_jump, execute_jeq, execute_jne, execute_jle, execute_jge, execute_jlt, execute_jgt,
    execute_call, execute_pusharg, execute_funcenter, execute_funcexit,
    execute_newtable, execute_tablegetelem, execute_tablesetelem, execute_nop
};

void execute_cycle(void) {
    if (executionFinished) return;
    if (pc >= codeSize) {
        executionFinished = 1;
        return;
    }
    
    instruction* instr = &code[pc];
    assert(instr->opcode >= 0 && instr->opcode <= NOP_V);
    
    unsigned old_pc = pc;
    currLine = instr->srcLine;
    
    executeFuncs[instr->opcode](instr);
    
    if (pc == old_pc && !executionFinished) {
        pc++;
    }
}
