%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "icode.h"
#include "bison_symtable.h"
#include "alpha_tokens.h"


extern int alpha_yylex();
#define yylex alpha_yylex

extern int yylineno;
extern char* yytext;

extern int yyparse();
extern FILE* yyin;

int yyerror(const char* yaccProvidedMessage);
void printError(const char* format, ...);

int scope = 0;
int loop_counter = 0;
int func_counter = 0;
int is_not_member = 0;
int anonymous_counter = 0;

%}

%union {
    char* strVal;
    int intVal;
    float floatVal;
    struct expr* exprVal;
    struct statement* statementVal;
    struct call* callVal;
    struct forprefix forprefixVal;
    unsigned int quadlabel;
}

%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND OR NOT TRUE FALSE NIL LOCAL
%token ASSIGN PLUS MINUS MULTIPLY DIVIDE MODULO EQUAL NOT_EQUAL GREATER_THAN LESS_THAN GREATER_EQUAL LESS_EQUAL INCREMENT DECREMENT
%token BRACKET_OPEN BRACKET_CLOSE CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE COMMA SEMICOLON COLON DOUBLE_COLON DOT DOUBLE_DOT
%token OTHER

%token <strVal> IDENTIFIER 
%token <strVal> STRING_TOKEN
%token <intVal> INTCONST
%token <floatVal> FLOATCONST

%type <exprVal> expr term assignexpr primary lvalue member call objectdef const funcdef funcprefix elist indexed indexedelem 
%type <statementVal> stmt stmts returnstmt ifstmt block forstmt
%type <strVal> idlist funcname
%type <callVal> normcall methodcall callsuffix
%type <quadlabel> ifprefix whilestart whilecond N M
%type <forprefixVal> forprefix


%start program 
%nonassoc IFX
%nonassoc ELSE

%right ASSIGN      
%left OR
%left AND
%nonassoc EQUAL NOT_EQUAL
%nonassoc GREATER_THAN GREATER_EQUAL LESS_THAN LESS_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%right NOT INCREMENT DECREMENT UMINUS
%left DOT DOUBLE_DOT
%left SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE
%left BRACKET_OPEN BRACKET_CLOSE
%%

program: stmts {printf("program starting here: %d\n",yylineno);}
        ;
stmts:
    /* empty */ {
        $$ = create_statement();
    }
    | stmts stmt {
        $$ = create_statement();
        $$->breaklist = mergelist($1->breaklist, $2->breaklist);
        $$->contlist  = mergelist($1->contlist, $2->contlist);
    }
;


stmt:
    ifstmt {printf("ifstmt: %d\n",yylineno); $$=$1;}
    | whilestart whilecond stmt {
    emit(jump, NULL, NULL, NULL, $1, yylineno);              
    patchlabel($2, nextquadlabel());                        
    if ($3) {
    patchlist($3->breaklist, nextquadlabel());
    patchlist($3->contlist, $1);
    }                  
    $$ = create_statement();
    }
    | forstmt
        { $$ = $1; }
    | expr SEMICOLON {printf("expr SEMICOLON: %d\n",yylineno); $$=create_statement();}
    | returnstmt {printf("returnstmt: %d\n",yylineno); $$=$1;}
    | BREAK SEMICOLON { if (loop_counter==0) printError("Use of 'break' while not in a loop"); } {printf("break semicolon : %d\n",yylineno); $$=create_statement();}
    | CONTINUE SEMICOLON { if (loop_counter==0) printError("Use of 'continue' while not in a loop"); } {printf("continue semicolon : %d\n",yylineno); $$=create_statement();}
    | block {printf("block : %d\n",yylineno); $$=$1;}
    | funcdef {printf("funcdef : %d\n",yylineno); $$=create_statement();}
    | call ASSIGN expr SEMICOLON { printError("Grammar error: Function call is not lvalue"); } {printf("call assign expr semicolon : %d\n",yylineno);}
    | SEMICOLON  {printf("semicolon : %d\n",yylineno); $$=create_statement();}
;



expr:
    assignexpr {
        is_not_member = 1;
        $$ = $1;
        printf("assignexpr: %d\n", yylineno);
    }
    | expr OR expr {
            $$ = newtemp();
            $$->type = boolexpr_e;
            emit(or, $1, $3, $$, 0, yylineno);
        }
    | expr AND expr {
            $$ = newtemp();
            $$->type = boolexpr_e;
            emit(and, $1, $3, $$, 0, yylineno);
        }
    | expr EQUAL expr {
                printf("expr equal expr : %d\n", yylineno);
                $$ = newtemp();
                $$->type = boolexpr_e;

                emit(if_eq, $1, $3, NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, $$, 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
        }
    | expr NOT_EQUAL expr {
                printf("expr not_equal expr : %d\n", yylineno);
                $$ = newtemp();
                $$->type = boolexpr_e;

                emit(if_noteq, $1, $3, NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, $$, 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
        }
    | expr LESS_EQUAL expr {
                printf("expr less_equal expr : %d\n", yylineno);
                $$ = newtemp();
                $$->type = boolexpr_e;

                emit(if_lesseq, $1, $3, NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, $$, 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
        }
    | expr LESS_THAN expr {
                printf("expr less_than expr : %d\n", yylineno);
                $$ = newtemp();
                $$->type = boolexpr_e;

                emit(if_less, $1, $3, NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, $$, 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
        }
    | expr GREATER_EQUAL expr {
                printf("expr greater_equal expr : %d\n", yylineno);
                $$ = newtemp();
                $$->type = boolexpr_e;

                emit(if_greatereq, $1, $3, NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, $$, 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
        }
    | expr GREATER_THAN expr {
                printf("expr greater_than expr : %d\n", yylineno);
                $$ = newtemp();
                $$->type = boolexpr_e;

                emit(if_greater, $1, $3, NULL, nextquadlabel() + 3, yylineno);
                emit(assign, newexpr_constbool(0), NULL, $$, 0, yylineno);
                emit(jump, NULL, NULL, NULL, nextquadlabel() + 2, yylineno);
                emit(assign, newexpr_constbool(1), NULL, $$, 0, yylineno);
        }
  | expr MODULO expr {
        printf("expr modulo expr : %d\n", yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp()->sym;
        emit(mod, $1, $3, $$, 0, yylineno);
    }
  | expr DIVIDE expr {
        printf("expr divide expr : %d\n", yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp()->sym;
        emit(div_i, $1, $3, $$, 0, yylineno);
    }
  | expr MULTIPLY expr {
        printf("expr multiply expr : %d\n", yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp()->sym;
        emit(mul, $1, $3, $$, 0, yylineno);
    }
  | expr MINUS expr {
        printf("expr minus expr : %d\n", yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp()->sym;
        emit(sub, $1, $3, $$, 0, yylineno);
    }
  | expr PLUS expr {
        printf("expr plus expr : %d\n", yylineno);
        $$ = newexpr(arithexpr_e);
        $$->sym = newtemp()->sym;
        emit(add, $1, $3, $$, 0, yylineno);
    }
  | term {
        $$ = $1;
        printf("term : %d\n", yylineno);
    }
;

term:
    BRACKET_OPEN expr BRACKET_CLOSE { printf("bracket_open expr bracket_close : %d\n", yylineno); $$ = $2;}
    | MINUS expr %prec UMINUS       { 
        printf("minus expr : %d\n", yylineno); 
        check_arith($2);
        $$ = newtemp();
        $$->type = arithexpr_e;
        emit(uminus, $2, NULL, $$, 0, yylineno);
    }
    | NOT expr {
        $$ = newtemp();
        $$->type = boolexpr_e;
        emit(not, $2, NULL, $$, 0, yylineno);
        printf("not expr : %d\n", yylineno);
    }
    | INCREMENT lvalue              { printf("increment lvalue : %d\n", yylineno); 
            check_arith($2);
            if($2->type == tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(add, $$, newexpr_constnum(1), $$, 0, yylineno);
                emit(tablesetelem, $2->index, $$, $2, 0, yylineno);
            } else {
                emit(add, $2, newexpr_constnum(1), $2, 0, yylineno);
                $$ = newtemp();
                $$->type = arithexpr_e;
                emit(assign, $2, NULL, $$, 0, yylineno);
            }
    }
    | lvalue INCREMENT              { printf("lvalue increment : %d\n", yylineno); 
            check_arith($1);
            $$ = newtemp();
            $$->type = var_e;
            if($1->type == tableitem_e) {
                expr* val = emit_iftableitem($1);
                emit(assign, val, NULL, $$, 0, yylineno);
                emit(add, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, $1->index, val, $1, 0, yylineno);
            } else {
                emit(assign, $1, NULL, $$, 0, yylineno);
                emit(add, $1, newexpr_constnum(1), $1, 0, yylineno);
            }
    }
    | DECREMENT lvalue              { printf("decrement lvalue : %d\n", yylineno);
            check_arith($2);
            if($2->type == tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(sub, $$, newexpr_constnum(1), $$, 0, yylineno);
                emit(tablesetelem, $2->index, $$, $2, 0, yylineno);
            } else {
                emit(sub, $2, newexpr_constnum(1), $2, 0, yylineno);
                $$ = newtemp();
                $$->type = arithexpr_e;
                emit(assign, $2, NULL, $$, 0, yylineno);
            }
    }
    | lvalue DECREMENT              { printf("lvalue decrement : %d\n", yylineno);
            check_arith($1);
            $$ = newtemp();
            $$->type = var_e;
            if($1->type == tableitem_e) {
                expr* val = emit_iftableitem($1);
                emit(assign, val, NULL, $$, 0, yylineno);
                emit(sub, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, $1->index, val, $1, 0, yylineno);
            } else {
                emit(assign, $1, NULL, $$, 0, yylineno);
                emit(sub, $1, newexpr_constnum(1), $1, 0, yylineno);
            }
    }
    | primary                       { printf("primary : %d\n", yylineno);  $$ = $1;}
    ;

assignexpr:
    lvalue ASSIGN expr{
        printf("lvalue ASSIGN expr %d\n", yylineno);
        Symbol_t* s = SymTable_lookup($1->sym->name, scope);
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member)
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", $1);

        if($1->type == tableitem_e) {
            emit(tablesetelem, $1->index, $3, $1, 0, yylineno);
            $$ = emit_iftableitem($1);
            $$->type = assignexpr_e;
        } else {
            emit(assign, $3, NULL, $1, 0, yylineno);
            $$ = newtemp();
            emit(assign, $1, NULL, $$, 0, yylineno);
        }
    };

primary:
    lvalue                  {printf("lvalue : %d\n",yylineno); $$ = emit_iftableitem($1);}
    | call                  {printf("call : %d\n",yylineno);}
    | objectdef             {printf("objectdef : %d\n",yylineno);}
    | BRACKET_OPEN funcdef BRACKET_CLOSE { $$ = NULL;  printf("bracket_open funcdef bracket_close : %d\n",yylineno);
        $$ = newexpr(programfunc_e);
        $$->sym = $2->sym;
    }
    | const                 {printf("const : %d\n",yylineno); $$ = $1;}
    ;

lvalue:
    IDENTIFIER {
        Symbol_t* s;
        int temp_scope = scope;
        while(temp_scope >= 0){
            s = SymTable_lookup($1,temp_scope);
            if(s) break;
            temp_scope--;
        }
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member){
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", $1);
        }else if (s && s->type != LIB_FUNC && s->scope != 0 && s->scope < scope && s->scope < func_counter){
            printError("Cannot access '%s' identifier that is located before function", $1);
        }else if(!s){
            SymTable_insert($1, (scope==0)?GLOBAL_VAR:LOCAL_VAR, scope, yylineno);}
        
        $$ = newexpr(var_e);
        $$->sym = SymTable_lookup($1,scope);
        printf("identifier : %d\n",yylineno);
    }
    | LOCAL IDENTIFIER {
        if(SymTable_lookupGlobal($2) && SymTable_lookupGlobal($2)->type == LIB_FUNC)
            printError("Collision with '%s' library function", $2);
        else if(!SymTable_lookup($2, scope)) {
            SymTable_insert($2, (scope==0)?GLOBAL_VAR:LOCAL_VAR, scope, yylineno); 
        }
        
        $$ = newexpr(var_e);
        $$->sym = SymTable_lookup($2, scope);
        printf("local identifier : %d\n",yylineno);
    }
    | DOUBLE_COLON IDENTIFIER {
        if(!SymTable_lookupGlobal($2))
            printError("No global variable '::%s' exists", $2);
        
        $$ = newexpr(var_e);
        $$->sym = SymTable_lookupGlobal($2);
        printf("double_colon identifier : %d\n",yylineno);
    }
    | member { $$ = $1; printf("member : %d\n",yylineno);}
    ;

member:
    lvalue DOT IDENTIFIER { printf("lvalue DOT IDENTIFIER : %d\n", yylineno); $$ = member_item($1, $3); }
    | lvalue SQUARE_BRACKET_OPEN expr SQUARE_BRACKET_CLOSE { printf("lvalue [ expr ] : %d\n", yylineno);
            $1 = emit_iftableitem($1);
            $$ = newexpr(tableitem_e);
            $$->sym = $1->sym;
            $$->index = $3;
    }
    | call DOT IDENTIFIER {is_not_member = 0; printf("call DOT IDENTIFIER : %d\n", yylineno); $$ = $1; }
    | call SQUARE_BRACKET_OPEN expr SQUARE_BRACKET_CLOSE { printf("call [ expr ] : %d\n", yylineno); $$ = $1;}
    ;

call:
    call BRACKET_OPEN elist BRACKET_CLOSE { printf("call ( elist ) : %d\n", yylineno); 
        $$ = make_call($1, $3);
    }
    | lvalue callsuffix { printf("lvalue callsuffix : %d\n", yylineno); 
        $1 = emit_iftableitem($1);
        if($2->isMethod){
            expr* t = $1;
            $1 = emit_iftableitem(member_item(t, $2->name));
            $2->elist->next = t;
        }

        $$ = make_call($1, $2->elist);
    }
    | BRACKET_OPEN funcdef BRACKET_CLOSE BRACKET_OPEN elist BRACKET_CLOSE { printf("( funcdef )( elist ) : %d\n", yylineno); 
        expr* func = newexpr(programfunc_e);
        func->sym = $2->sym;
        $$ = make_call(func, $5);
    }
    ;


callsuffix:
    normcall { printf("normcall : %d\n", yylineno); $$ = $1;}
    | methodcall { printf("methodcall : %d\n", yylineno);  $$ = $1; }
    ;

normcall:
    BRACKET_OPEN elist BRACKET_CLOSE { printf("normcall ( elist ) : %d\n", yylineno);
        $$ = malloc(sizeof(struct call));
        $$->elist = $2;
        $$->isMethod = 0;
        $$->name = NULL;
    }
    ;

methodcall:
    DOUBLE_DOT IDENTIFIER BRACKET_OPEN elist BRACKET_CLOSE { printf("methodcall ..IDENTIFIER( elist ) : %d\n", yylineno); 
        $$ = malloc(sizeof(struct call));
        $$->elist = $4;
        $$->isMethod = 1;
        $$->name = strdup($2);
    }
    ;

elist:
    expr { printf("elist expr : %d\n", yylineno); 
        $$ = $1;
        $$->next = NULL;
    }
    | expr COMMA elist { printf("elist , expr : %d\n", yylineno); 
        $1->next = $3;
        $$ = $1;

    }
    | /* empty */ { printf("empty elist : %d\n", yylineno);
        $$ = NULL;
    }
    ;

objectdef:
    SQUARE_BRACKET_OPEN elist SQUARE_BRACKET_CLOSE { printf("objectdef [ elist ] : %d\n", yylineno); 
        expr* t = newtemp();
        t->type = newtable_e;
        emit(tablecreate, NULL, NULL, t, 0, yylineno);
        int i = 0;
        for(expr* tmp = $2; tmp; tmp = tmp->next, i++){
            emit(tablesetelem, newexpr_constnum(i), tmp, t, 0, yylineno);
        }
        $$ = t;
    }
    | SQUARE_BRACKET_OPEN indexed SQUARE_BRACKET_CLOSE { printf("objectdef [ indexed ] : %d\n", yylineno); 
        expr* t = newtemp();
        t->type = newtable_e;
        emit(tablecreate, NULL, NULL, t, 0, yylineno);
        for(expr* tmp = $2; tmp; tmp = tmp->next){
            emit(tablesetelem, tmp, tmp->index, t, 0, yylineno);
        }
        $$ = t;
    }
    ;

indexed:
    indexedelem { printf("indexed indexedelem : %d\n", yylineno); 
        $$ = $1;
        $$->next = NULL;
    }
    | indexedelem COMMA indexed { printf("indexed , indexedelem : %d\n", yylineno); 
        $1->next = $3;
        $$ = $1;
    }
    ;

indexedelem:
    CURLY_BRACKET_OPEN expr COLON expr CURLY_BRACKET_CLOSE { printf("indexedelem { expr : expr } : %d\n", yylineno); 
        $2->index = $4;
        $$ = $2;
    }
    ;


block:
    CURLY_BRACKET_OPEN stmts CURLY_BRACKET_CLOSE { $$ = $2; }
;



funcname:  IDENTIFIER {
    
            printf("funcname IDENTIFIER : %d\n", yylineno);

            Symbol_t* s = SymTable_lookup($1, scope);
            if(s){
                if(s->type==2){
                    printError("Collision with LOCAL_VAR named '%s'",$1);
                }else{
                    printError("Collision with USER_FUNC named '%s'",$1);
                }
            }else{
                SymTable_insert($1, USER_FUNC, scope, yylineno);
            }
            $$ = $1;
        }
        | {
            printf("empty funcname : %d\n", yylineno);
            char anonymous_funcname[10];
            sprintf(anonymous_funcname, "$%d", anonymous_counter);
            SymTable_insert(anonymous_funcname, USER_FUNC, scope, yylineno);
            anonymous_counter++;

            $$ = strdup(anonymous_funcname);
        }
        ;

funcprefix: FUNCTION funcname {
                $$ = newexpr(programfunc_e);
                $$->sym = SymTable_lookup($2, scope);
                emit(funcstart, $$, NULL, NULL, 0, yylineno);
            }
            ;

funcargs:   BRACKET_OPEN {scope++;} idlist BRACKET_CLOSE {scope--;}
            ;

funcbody:   block {func_counter--; }
            ;

funcdef:    funcprefix funcargs funcbody {
                $$ = $1;
                emit(funcend, $$, NULL, NULL, 0, yylineno);
            }
            ;

const:
    FLOATCONST { printf("FLOATCONST : %d\n", yylineno); $$=newexpr_constnum($1); }
    | INTCONST { printf("INTCONST : %d\n", yylineno); $$=newexpr_constnum($1);  }
    | STRING_TOKEN { printf("STRING_TOKEN : %d\n", yylineno); $$=newexpr_conststring($1); }
    | NIL { printf("NIL : %d\n", yylineno); $$=newexpr_nil(); }
    | TRUE { printf("TRUE : %d\n", yylineno); $$=newexpr_constbool(1); }
    | FALSE { printf("FALSE : %d\n", yylineno); $$=newexpr_constbool(0); }
    ;


idlist: {printf("empty idlist: %d\n",yylineno);}
    |IDENTIFIER { 
        if(SymTable_lookupGlobalFuncs($1)){
            printError("Collision with '%s' library function", $1);
        }else if(SymTable_lookup($1, scope)){ 
            printError("Variable '%s' already defined", $1);
        }else{
            SymTable_insert($1, FORMAL_ARG, scope, yylineno);
        }
    }
    | idlist COMMA IDENTIFIER {

        if(SymTable_lookupGlobalFuncs($3)){
            printError("Collision with '%s' library function", $3);
        }else if(SymTable_lookup($3, scope)){ 
            printError("Variable '%s' already defined", $3);
        }else{
            SymTable_insert($3, FORMAL_ARG, scope, yylineno);
        }
    }
    ;
ifprefix:
    IF BRACKET_OPEN expr BRACKET_CLOSE
    {
        emit(if_eq, $3, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        $$ = nextquadlabel();
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
;

ifstmt:
    ifprefix stmt %prec IFX
    {
        patchlabel($1, nextquadlabel());
        $$ = $2;
    }
  | ifprefix stmt ELSE stmt
    {
        unsigned after_if = nextquadlabel();
        emit(jump, NULL, NULL, NULL, 0, yylineno);  
        patchlabel($1, nextquadlabel());              
        patchlabel(after_if, nextquadlabel());        
        $$ = create_statement(); 
    }
;


whilestart:
    WHILE {
        $$ = nextquadlabel();
        ++loop_counter;
    }
;

whilecond:
    BRACKET_OPEN expr BRACKET_CLOSE {
        emit(if_eq, $2, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        $$ = nextquadlabel(); 
        emit(jump, NULL, NULL, NULL, 0, yylineno); 
    }
;

N: { $$ = nextquadlabel(); emit(jump, NULL, NULL, NULL, 0, yylineno); };
M: { $$ = nextquadlabel(); };


forprefix:
    FOR BRACKET_OPEN elist SEMICOLON M expr SEMICOLON elist BRACKET_CLOSE {
        $$.test = $5;                 
        expr* cond = make_bool_expr($6);  
        emit(if_eq, cond, newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);  
        $$.enter = nextquadlabel();
        emit(assign, NULL, NULL, NULL, 0, yylineno); 
    }
;

forstmt:
    forprefix N elist BRACKET_CLOSE N stmt N {
        patchlabel($1.enter, $2 + 1);      
        patchlabel($2, nextquadlabel());    
        patchlabel($5, $1.test);           
        patchlabel($7, $2 + 1);              
        patchlist($6->breaklist, nextquadlabel());
        patchlist($6->contlist, $2 + 1);
        $$ = $6;
    }
;

returnstmt:
    RETURN expr SEMICOLON { if (func_counter==0) printError("Use of 'return' while not in a function"); 
        emit(ret, $2, NULL, NULL, 0, yylineno);
    }
    | RETURN SEMICOLON { if (func_counter==0) printError("Use of 'return' while not in a function"); 
        emit(ret, NULL, NULL, NULL, 0, yylineno);
    }  
    ;
%%

int yyerror(const char* yaccProvidedMessage){
    fprintf(stderr,"Syntax error at line %d: %s, near '%s'\n",yylineno,yaccProvidedMessage,yytext);
    return 0;
}

void printError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Error (line %d): ", yylineno);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    SymTable_init();
    yyparse();
    SymTable_print();
    print_quads(stdout);
    write_quads_to_file("quads.txt");
    return 0;
}
