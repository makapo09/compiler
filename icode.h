#ifndef ICODE_H
#define ICODE_H

#include <stdio.h>
#include "bison_symtable.h"

extern int yynerrs;
extern int yylineno;

typedef Symbol_t Symbol;

typedef enum expr_t {
    var_e,
    tableitem_e,
    programfunc_e,
    libraryfunc_e,
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    constnum_e,
    constbool_e,
    conststring_e,
    nil_e
} expr_t;

typedef struct expr {
    expr_t type;
    Symbol* sym;
    struct expr* index;
    double numConst;
    char* strConst;
    unsigned char boolConst;
    struct expr* next;
} expr;

struct call {
    int scope;
    char *name;
    unsigned char isMethod;
    struct expr *elist;
};

struct jumpLabels {
	int label;
	struct jumpLabels* next;
};

struct statement {
    struct jumpLabels* contlist;
    struct jumpLabels* breaklist;
};

struct forprefix {
    unsigned int test;
    unsigned int enter;
};

typedef enum iopcode {
    assign, add, sub, mul, div_i, mod,
    uminus, and, or, not,
    if_eq, if_noteq, if_lesseq, if_greatereq, if_less, if_greater,
    jump,
    call, param, ret, getretval,
    funcstart, funcend,
    tablecreate, tablegetelem, tablesetelem
} iopcode;

typedef struct quad {
    iopcode op;
    expr* arg1;
    expr* arg2;
    expr* result;
    unsigned label;
    unsigned line;
    unsigned taddress; 
} quad;

extern quad* quads;
extern unsigned total;
extern unsigned currQuad;

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
void expand(void);

const char* iopcode_to_string(iopcode op);
char* expr_to_string(expr* e);
void print_quads(FILE* filep);
void write_quads_to_file(const char* filename);

expr* newexpr(expr_t type);
expr* newexpr_constnum(double n); 
expr* newexpr_constbool(unsigned char b); 
expr* newexpr_conststring(char* s);
expr* newexpr_nil(void);
expr* newexpr_var(Symbol* sym);

struct statement* create_statement ();

expr* make_call (expr* lv, expr* reversed_elist);

expr* newtemp(void);
quad* get_quad_at(unsigned index);
unsigned nextquadlabel(void);
expr* make_bool_expr(expr* e);

expr* member_item (expr* lv, char* name);   
expr* emit_iftableitem(expr* e);

void check_arith (expr* e);
void patchlabel(unsigned quadNo, unsigned label);
void patchlist(struct jumpLabels* list, unsigned label);
struct jumpLabels* makelist(unsigned label);
struct jumpLabels* mergelist(struct jumpLabels* l1, struct jumpLabels* l2);

#endif
