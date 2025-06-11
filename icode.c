#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "icode.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(struct quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(struct quad) + CURR_SIZE)

extern int yynerrs;
extern int yylineno;

quad* quads = NULL;
unsigned total = 0;
unsigned currQuad = 0;

static unsigned temp_counter = 0;

void expand(void) {
    assert(total == currQuad);
    quad* newQuads = (quad*)realloc(quads, (total + EXPAND_SIZE) * sizeof(quad));
    if (!newQuads) {
        fprintf(stderr, "Failed to expand quad array.\n");
        exit(EXIT_FAILURE);
    }
    quads = newQuads;
    total += EXPAND_SIZE;
}

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line) {
    if (currQuad == total)
        expand();

    quads[currQuad].op = op;
    quads[currQuad].arg1 = arg1;
    quads[currQuad].arg2 = arg2;
    quads[currQuad].result = result;
    quads[currQuad].label = label;
    quads[currQuad].line = line;

    ++currQuad;
}

struct statement* create_statement (){
	struct statement* st = (struct statement*)malloc (sizeof(struct statement));
	st->breaklist = NULL;
	st->contlist =  NULL;
	return st;
}

expr* newexpr(expr_t type) {
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e, 0, sizeof(expr));
    e->type = type;
    return e;
}

expr* newexpr_constnum(double n) {
    expr* e = newexpr(constnum_e);
    e->numConst = n;
    return e;
}

expr* newexpr_constbool(unsigned char b) {
    expr* e = newexpr(constbool_e);
    e->boolConst = b;
    return e;
}

expr* newexpr_conststring(char* s) {
    expr* e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

expr* newexpr_nil(void) {
    return newexpr(nil_e);
}

expr* newexpr_var(Symbol* sym) {
    expr* e = newexpr(var_e);
    e->sym = sym;
    return e;
}

expr* make_call (expr* lv, expr* reversed_elist) {
    expr* func = emit_iftableitem(lv);
    expr* current_arg = reversed_elist;
    while (current_arg) {
        emit(param, current_arg, NULL, NULL , 0, yylineno);
        current_arg = current_arg->next;
    }
    emit(call, func, NULL, NULL, 0, yylineno);
    expr* result = newtemp();
    result->type = var_e;
    emit(getretval, NULL, NULL, result, 0, yylineno);
    return result;
}

expr* newtemp(void) {
    char name[64];
    sprintf(name, "_t%u", temp_counter++);
    Symbol* s = SymTable_lookup(name, 0); 
    if (!s) {
        s = insert_temp(name);
    }
    return newexpr_var(s);
}

const char* iopcode_to_string(iopcode op) {
    const char* op_map[] = {
        "assign", "add", "sub", "mul", "div", "mod", "uminus",
        "and", "or", "not", "if_eq", "if_noteq", "if_lesseq",
        "if_greatereq", "if_less", "if_greater", "jump", "call",
        "param", "ret", "getretval", "funcstart", "funcend",
        "tablecreate", "tablegetelem", "tablesetelem"
    };
    if (op < sizeof(op_map)/sizeof(op_map[0])) {
        return op_map[op];
    }
    return "UNKNOWN";
}


char* expr_to_string(expr* e) {
    char* buffer = (char*)malloc(256);
    if (!buffer) return strdup("(mem error)");

    if (e == NULL){
        strcpy(buffer, ""); 
        return buffer;
    }

    switch(e->type) {
        case constnum_e:    snprintf(buffer, 256, "%.2f", e->numConst); break;
        case conststring_e: snprintf(buffer, 256, "\"%s\"", e->strConst ? e->strConst : "NULL"); break;
        case constbool_e:   snprintf(buffer, 256, e->boolConst ? "true" : "false"); break;
        case nil_e:         strcpy(buffer, "nil"); break;
        default:
            if (e->sym && e->sym->name) {
                snprintf(buffer, 256, "%s", e->sym->name);
            } else {
                strcpy(buffer, "(null symbol)");
            }
            break;
    }
    return buffer;
}


void print_quads(FILE* filep) {
    fprintf(filep,"%-5s %-12s %-15s %-15s %-15s %-6s\n", "ID", "Opcode", "Result", "Arg1", "Arg2", "Label");
    fprintf(filep,"-------------------------------------------------------------------------------\n");
    for (unsigned i = 0; i < currQuad; ++i) {
        quad q = quads[i];
        char *res_str = expr_to_string(q.result);
        char *arg1_str = expr_to_string(q.arg1);
        char *arg2_str = expr_to_string(q.arg2);
        fprintf(filep,"%-5u %-12s %-15s %-15s %-15s %-6u\n",
            i, iopcode_to_string(q.op), res_str, arg1_str, arg2_str, q.label
        );
        free(res_str); free(arg1_str); free(arg2_str);
    }
}

void write_quads_to_file(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) { perror("write_quads_to_file"); return; }
    print_quads(f);
    fclose(f);
}

quad* get_quad_at(unsigned index) {
    assert(index < currQuad);
    return &quads[index];
}

unsigned nextquadlabel(void) {
    return currQuad;
}

expr* emit_iftableitem(expr* e){
    if(!e || e->type != tableitem_e){
        return e;
    } else {
        expr* result = newtemp();
        result->type = var_e;
        emit(tablegetelem, e, e->index, result, 0, yylineno);
        return result;
    }
}

expr* member_item (expr* lv, char* name) {
    lv = emit_iftableitem(lv);
    // FIX: Check if lv is NULL after emit_iftableitem (e.g. if it was nil)
    if (!lv) {
        yynerrs++;
        fprintf(stderr, "Error (line %d): Cannot access member '%s' of a non-table value.\n", yylineno, name);
        return NULL; // Return NULL to propagate the error
    }
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name);
    return ti;
}

void check_arith (expr* e) {
    if (!e) return;
    if ( e->type == constbool_e || e->type == conststring_e ||
        e->type == nil_e || e->type == newtable_e || e->type == programfunc_e ||
        e->type == libraryfunc_e || e->type == boolexpr_e ) {
            fprintf(stderr, "Error (line %d): Illegal expression used in arithmetic operation.\n", yylineno);
            yynerrs++;
    }
}

void patchlabel(unsigned quadNo, unsigned label) {
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

void patchlist(struct jumpLabels* list, unsigned label) {
    for (struct jumpLabels* current = list; current; current = current->next) {
        patchlabel(current->label, label);
    }
}

struct jumpLabels* makelist(unsigned label) {
    struct jumpLabels* node = (struct jumpLabels*)malloc(sizeof(struct jumpLabels));
    node->label = label;
    node->next = NULL;
    return node;
}

struct jumpLabels* mergelist(struct jumpLabels* l1, struct jumpLabels* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    struct jumpLabels* temp = l1;
    while (temp->next) temp = temp->next;
    temp->next = l2;
    return l1;
}

expr* make_bool_expr(expr* e) {
    if (!e) return NULL;
    if (e->type == boolexpr_e || e->type == constbool_e) return e;

    expr* result = newtemp();
    result->type = boolexpr_e;
    emit(if_eq, e, newexpr_constbool(1), NULL, nextquadlabel() + 3, yylineno);
    emit(assign, newexpr_constbool(0), NULL, result, 0, yylineno);
    emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
    emit(assign, newexpr_constbool(1), NULL, result, 0, yylineno);
    return result;
}
