#ifndef ICODE_H
#define ICODE_H

#include "bison_symtable.h"
#include "backpatch.h" 

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
    labelList* truelist;
    labelList* falselist;
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
} quad;

extern quad* quads;
extern unsigned total;
extern unsigned currQuad;

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line);
void expand(void);

const char* iopcode_to_string(iopcode op);
char* expr_to_string(expr* e);
void print_quads(void);
void write_quads_to_file(const char* filename);

expr* newexpr(expr_t type);
expr* newexpr_constnum(double n); 
expr* newexpr_constbool(unsigned char b); 
expr* newexpr_conststring(char* s);
expr* newexpr_nil(void);
expr* newexpr_var(Symbol* sym);

struct statement* create_statement ();

expr* newtemp(void);
quad* get_quad_at(unsigned index);
unsigned nextquadlabel(void);
expr* make_bool_expr(expr* e);

#endif 