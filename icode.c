#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "icode.h"

#define EXPAND_SIZE 1024
#define CURR_SIZE (total * sizeof(struct quad))
#define NEW_SIZE (EXPAND_SIZE * sizeof(struct quad) + CURR_SIZE)

extern int yylineno;  

quad* quads = NULL;
unsigned total = 0;
unsigned currQuad = 0;

static unsigned temp_counter = 0;

void expand(void) {
    assert(total == currQuad);
    quad* newQuads = (quad*)malloc(NEW_SIZE);
    if (quads) {
        memcpy(newQuads, quads, CURR_SIZE);
        free(quads);
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
	struct statement* st = malloc (sizeof(struct statement));
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
    e->type = constnum_e;
    e->numConst = n;
    return e;
}

expr* newexpr_constbool(unsigned char b) {
    expr* e = newexpr(constbool_e);
    e->type = constbool_e;
    e->boolConst = b;
    return e;
}

expr* newexpr_conststring(char* s) {
    expr* e = newexpr(conststring_e);
    e->type = conststring_e;
    e->strConst = strdup(s);
    return e;
}

expr* newexpr_nil(void) {
    expr* e = newexpr(nil_e);
    e->type=nil_e;
    return e;
}

expr* newexpr_var(Symbol* sym) {
    expr* e = newexpr(var_e);
    e->sym = sym;
    return e;
}


expr* make_call (expr* lv, expr* reversed_elist) {
    expr* func = emit_iftableitem(lv);
    while (reversed_elist) {
        emit(param, reversed_elist, NULL, NULL , 0, yylineno);
        reversed_elist = reversed_elist->next;
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
    Symbol* s = insert_temp(name);
    return newexpr_var(s);
}

const char* iopcode_to_string(iopcode op) {
    switch(op) {
        case assign: return "assign";
        case add: return "add";
        case sub: return "sub";
        case mul: return "mul";
        case div_i: return "div";
        case mod: return "mod";
        case uminus: return "uminus";
        case and: return "and";
        case or: return "or";
        case not: return "not";
        case if_eq: return "if_eq";
        case if_noteq: return "if_noteq";
        case if_lesseq: return "if_lesseq";
        case if_greatereq: return "if_greatereq";
        case if_less: return "if_less";
        case if_greater: return "if_greater";
        case jump: return "jump";
        case call: return "call";
        case param: return "param";
        case ret: return "ret";
        case getretval: return "getretval";
        case funcstart: return "funcstart";
        case funcend: return "funcend";
        case tablecreate: return "tablecreate";
        case tablegetelem: return "tablegetelem";
        case tablesetelem: return "tablesetelem";
        default: return "UNKNOWN";
    }
}

char* expr_to_string(expr* e) {
    char* buffer = (char*)malloc(128);
    if (e == NULL){
        return "";
    }

    if (e->type == constnum_e) {
        snprintf(buffer, 128, "%.2f", e->numConst);
    } else if (e->type == conststring_e && e->strConst) {
        snprintf(buffer, 128, "\"%s\"", e->strConst);
    } else if (e->type == constbool_e) {
        snprintf(buffer, 128, e->boolConst ? "true" : "false");
    } else {
        snprintf(buffer, 128, "%s", e->sym->name);
    }


    return buffer;
}

void print_quads(FILE* filep) {
    fprintf(filep,"%-5s %-12s %-15s %-15s %-15s %-6s\n", "ID", "Opcode", "Result", "Arg1", "Arg2", "Label");
    fprintf(filep,"-------------------------------------------------------------------------------\n");
    for (unsigned i = 0; i < currQuad; ++i) {
        quad q = quads[i];
        fprintf(filep,"%-5u %-12s %-15s %-15s %-15s %-6u\n",
            i,
            iopcode_to_string(q.op),
            expr_to_string(q.result),
            expr_to_string(q.arg1),
            expr_to_string(q.arg2),
            q.label
        );
    }
}

quad* get_quad_at(unsigned index) {
    assert(index < currQuad);
    return &quads[index];
}

unsigned nextquadlabel(void) {
    return currQuad;
}


expr* emit_iftableitem(expr* e){
    if(e->type != tableitem_e){
        return e;
    } else {
        expr* result = newexpr(var_e);
        result->sym = newtemp()->sym;
        emit(tablegetelem, e, e->index, result, 0, yylineno);
        return result;
    }

    return (expr*)0;
}

expr* member_item (expr* lv, char* name) {
    lv = emit_iftableitem(lv); // Emit code if r-value use of table item
    expr* ti = newexpr(tableitem_e); // Make a new expression
    ti->sym = lv->sym;
    ti->index = newexpr_conststring(name); // Const string index
    return ti;
}

void check_arith (expr* e) {
    if ( e->type == constbool_e ||
    e->type == conststring_e ||
    e->type == nil_e ||
    e->type == newtable_e ||
    e->type == programfunc_e ||
    e->type == libraryfunc_e ||
    e->type == boolexpr_e )
    fprintf(stderr, "Illegal expr used as arithmetic\n");
}


void write_quads_to_file(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("write_quads_to_file");
        return;
    }

    print_quads(f);

    fclose(f);
}

void patchlabel(unsigned quadNo, unsigned label) {
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}

void patchlist(struct jumpLabels* list, unsigned label) {
    while (list) {
        printf("Patching label at quad %d with label %d\n", list->label, label);
        patchlabel(list->label, label);
        list = list->next;
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
    struct jumpLabels* temp = l1;
    while (temp->next) temp = temp->next;
    temp->next = l2;
    return l1;
}

expr* make_bool_expr(expr* e) {
    if (e->type == boolexpr_e || e->type == constbool_e)
        return e;

    expr* result = newtemp();
    emit(if_eq, e, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
    emit(assign, result, newexpr_constbool(0), NULL, 0, yylineno);
    emit(jump, NULL, NULL, NULL, nextquadlabel() + 1, yylineno);
    emit(assign, result, newexpr_constbool(1), NULL, 0, yylineno);
    return result;
}
