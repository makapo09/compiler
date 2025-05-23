%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "bison_symtable.h"
#include "alpha_tokens.h"
#include "icode.h"
#include "backpatch.h"

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
}

%token IF ELSE WHILE FOR FUNCTION RETURN BREAK CONTINUE AND OR NOT TRUE FALSE NIL LOCAL
%token ASSIGN PLUS MINUS MULTIPLY DIVIDE MODULO EQUAL NOT_EQUAL GREATER_THAN LESS_THAN GREATER_EQUAL LESS_EQUAL INCREMENT DECREMENT
%token BRACKET_OPEN BRACKET_CLOSE CURLY_BRACKET_OPEN CURLY_BRACKET_CLOSE SQUARE_BRACKET_OPEN SQUARE_BRACKET_CLOSE COMMA SEMICOLON COLON DOUBLE_COLON DOT DOUBLE_DOT
%token OTHER

%token <strVal> IDENTIFIER 
%token <strVal> STRING_TOKEN
%token <intVal> INTCONST
%token <floatVal> FLOATCONST

%type <exprVal> expr term assignexpr primary lvalue member call objectdef const
%type <statementVal> stmt stmts forstmt returnstmt whilestmt ifstmt block
%type <strVal> idlist 
%type <callVal> normcall methodcall callsuffix


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
    stmts stmt {printf("stmts stmt: %d\n",yylineno); $$=create_statement();}
    |{printf("Empty stmt: %d\n",yylineno);}
    ;

stmt:
    expr SEMICOLON {printf("expr SEMICOLON: %d\n",yylineno); $$=create_statement();}
    | ifstmt {printf("ifstmt: %d\n",yylineno); $$=$1;}
    | whilestmt {printf("whilestmt: %d\n",yylineno); $$=create_statement();}
    | forstmt {printf("forstmt: %d\n",yylineno); $$=create_statement();}
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
        printf("expr or expr : %d\n", yylineno);
        backpatch($1->falselist, nextquadlabel());
        $$ = newexpr(boolexpr_e);
        $$->truelist = mergelists($1->truelist, $3->truelist);
        $$->falselist = $3->falselist;
    }
  | expr AND expr {
        printf("expr and expr : %d\n", yylineno);
        backpatch($1->truelist, nextquadlabel());
        $$ = newexpr(boolexpr_e);
        $$->truelist = $3->truelist;
        $$->falselist = mergelists($1->falselist, $3->falselist);
    }
  | expr EQUAL expr {
        printf("expr equal expr : %d\n", yylineno);
        $$ = newexpr(boolexpr_e);
        $$->truelist = newlist(nextquadlabel());
        $$->falselist = newlist(nextquadlabel() + 1);
        emit(if_eq, $1, $3, NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
  | expr NOT_EQUAL expr {
        printf("expr not_equal expr : %d\n", yylineno);
        $$ = newexpr(boolexpr_e);
        $$->truelist = newlist(nextquadlabel());
        $$->falselist = newlist(nextquadlabel() + 1);
        emit(if_noteq, $1, $3, NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
  | expr LESS_EQUAL expr {
        printf("expr less_equal expr : %d\n", yylineno);
        $$ = newexpr(boolexpr_e);
        $$->truelist = newlist(nextquadlabel());
        $$->falselist = newlist(nextquadlabel() + 1);
        emit(if_lesseq, $1, $3, NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
  | expr LESS_THAN expr {
        printf("expr less_than expr : %d\n", yylineno);
        $$ = newexpr(boolexpr_e);
        $$->truelist = newlist(nextquadlabel());
        $$->falselist = newlist(nextquadlabel() + 1);
        emit(if_less, $1, $3, NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
  | expr GREATER_EQUAL expr {
        printf("expr greater_equal expr : %d\n", yylineno);
        $$ = newexpr(boolexpr_e);
        $$->truelist = newlist(nextquadlabel());
        $$->falselist = newlist(nextquadlabel() + 1);
        emit(if_greatereq, $1, $3, NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
    }
  | expr GREATER_THAN expr {
        printf("expr greater_than expr : %d\n", yylineno);
        $$ = newexpr(boolexpr_e);
        $$->truelist = newlist(nextquadlabel());
        $$->falselist = newlist(nextquadlabel() + 1);
        emit(if_greater, $1, $3, NULL, 0, yylineno);
        emit(jump, NULL, NULL, NULL, 0, yylineno);
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
    BRACKET_OPEN expr BRACKET_CLOSE { printf("bracket_open expr bracket_close : %d\n", yylineno); }
    | MINUS expr %prec UMINUS       { printf("minus expr : %d\n", yylineno); }
    | NOT expr {
        $$ = newexpr(boolexpr_e);
        $$->truelist = $2->falselist;
        $$->falselist = $2->truelist;
        printf("not expr : %d\n", yylineno);
    }
    | INCREMENT lvalue              { printf("increment lvalue : %d\n", yylineno); }
    | lvalue INCREMENT              { printf("lvalue increment : %d\n", yylineno); }
    | DECREMENT lvalue              { printf("decrement lvalue : %d\n", yylineno); }
    | lvalue DECREMENT              { printf("lvalue decrement : %d\n", yylineno); }
    | primary                       { printf("primary : %d\n", yylineno);  $$ = $1;}
    ;

assignexpr:
    lvalue ASSIGN expr{
        printf("lvalue ASSIGN expr %d\n", yylineno);
        Symbol_t* s = SymTable_lookup($1->sym->name, scope);
        if(s && (s->type==USER_FUNC || s->type==LIB_FUNC) && is_not_member)
            printError("Using %s '%s' as an lvalue", (s->type==LIB_FUNC)?"LibFunc":"ProgramFunc", $1);

        //if ($3->truelist || $3->falselist) {
        //    $3 = make_bool_expr($3);
        //}

        emit(assign, $3, NULL, $1, 0, yylineno);
        $$ = newtemp();
        emit(assign, $1, NULL, $$, 0, yylineno);
    };

primary:
    lvalue                  {printf("lvalue : %d\n",yylineno);}
    | call                  {printf("call : %d\n",yylineno);}
    | objectdef             {printf("objectdef : %d\n",yylineno);}
    | BRACKET_OPEN funcdef BRACKET_CLOSE { $$ = NULL;  printf("bracket_open funcdef bracket_close : %d\n",yylineno);}
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
    lvalue DOT IDENTIFIER { printf("lvalue DOT IDENTIFIER : %d\n", yylineno); }
    | lvalue SQUARE_BRACKET_OPEN expr SQUARE_BRACKET_CLOSE { printf("lvalue [ expr ] : %d\n", yylineno); }
    | call DOT IDENTIFIER {is_not_member = 0; printf("call DOT IDENTIFIER : %d\n", yylineno); }
    | call SQUARE_BRACKET_OPEN expr SQUARE_BRACKET_CLOSE { printf("call [ expr ] : %d\n", yylineno); }
    ;

call:
    call BRACKET_OPEN elist BRACKET_CLOSE { printf("call ( elist ) : %d\n", yylineno); }
    | lvalue callsuffix { printf("lvalue callsuffix : %d\n", yylineno); }
    | BRACKET_OPEN funcdef BRACKET_CLOSE BRACKET_OPEN elist BRACKET_CLOSE { printf("( funcdef )( elist ) : %d\n", yylineno); }
    ;


callsuffix:
    normcall { printf("normcall : %d\n", yylineno); }
    | methodcall { printf("methodcall : %d\n", yylineno); }
    ;

normcall:
    BRACKET_OPEN elist BRACKET_CLOSE { printf("normcall ( elist ) : %d\n", yylineno); }
    ;

methodcall:
    DOUBLE_DOT IDENTIFIER BRACKET_OPEN elist BRACKET_CLOSE { printf("methodcall ..IDENTIFIER( elist ) : %d\n", yylineno); }
    ;

elist:
    expr { printf("elist expr : %d\n", yylineno); }
    | elist COMMA expr { printf("elist , expr : %d\n", yylineno); }
    | /* empty */ { printf("empty elist : %d\n", yylineno); }
    ;

objectdef:
    SQUARE_BRACKET_OPEN elist SQUARE_BRACKET_CLOSE { printf("objectdef [ elist ] : %d\n", yylineno); }
    | SQUARE_BRACKET_OPEN indexed SQUARE_BRACKET_CLOSE { printf("objectdef [ indexed ] : %d\n", yylineno); }
    ;

indexed:
    indexedelem { printf("indexed indexedelem : %d\n", yylineno); }
    | indexed COMMA indexedelem { printf("indexed , indexedelem : %d\n", yylineno); }
    ;

indexedelem:
    CURLY_BRACKET_OPEN expr COLON expr CURLY_BRACKET_CLOSE { printf("indexedelem { expr : expr } : %d\n", yylineno); }
    ;


block:
    CURLY_BRACKET_OPEN { scope++; printf("scope= %d\n", scope);} stmts CURLY_BRACKET_CLOSE { hideScope(scope--); }
    ;

funcdef:
    FUNCTION identifiers BRACKET_OPEN {scope++;} idlist BRACKET_CLOSE {scope--;} 
    block {func_counter--; }
    ;

identifiers:
    IDENTIFIER { printf("IDENTIFIER : %d\n", yylineno);
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
        func_counter++;
        printf("FUNCTION IDENTIFIER BRACKET_OPEN idlist BRACKET_CLOSE block: %d\n",yylineno);}
    |   { printf("EMPTY IDENTIFIER : %d\n", yylineno);
        char anonymous_funcname[10];
        sprintf(anonymous_funcname, "$%d", anonymous_counter);
        func_counter++;
        SymTable_insert(anonymous_funcname, USER_FUNC, scope, yylineno);
        anonymous_counter++;
        }
    ;

const:
    FLOATCONST { printf("FLOATCONST : %d\n", yylineno); $$=newexpr_constnum($1); }
    | INTCONST { printf("INTCONST : %d\n", yylineno); $$=newexpr_constnum($1);  }
    | STRING_TOKEN { printf("STRING_TOKEN : %d\n", yylineno); $$=newexpr_conststring($1); }
    | NIL { printf("NIL : %d\n", yylineno); $$=newexpr_nil(); }
    | TRUE { printf("TRUE : %d\n", yylineno); $$=newexpr_constbool(1); }
    | FALSE { printf("FALSE : %d\n", yylineno); $$=newexpr_constnum(0); }
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

ifstmt:
    IF BRACKET_OPEN expr BRACKET_CLOSE stmt %prec IFX
        { printf("if ( expr ) stmt : %d\n", yylineno); }
    | IF BRACKET_OPEN expr BRACKET_CLOSE stmt ELSE stmt
        { printf("if ( expr ) stmt else stmt : %d\n", yylineno); }
    ;

whilestmt:
    WHILE BRACKET_OPEN expr BRACKET_CLOSE
        { loop_counter++; printf("while loop start : %d\n", yylineno); }
        stmt
        { loop_counter--; printf("while loop end : %d\n", yylineno); }
    ;

forstmt:
    FOR BRACKET_OPEN elist SEMICOLON expr SEMICOLON elist BRACKET_CLOSE
        { loop_counter++; printf("for loop start : %d\n", yylineno); }
        stmt
        { loop_counter--; printf("for loop end : %d\n", yylineno); }
    ;

returnstmt:
    RETURN expr SEMICOLON { if (func_counter==0) printError("Use of 'return' while not in a function"); }
    | RETURN SEMICOLON { if (func_counter==0) printError("Use of 'return' while not in a function"); }  
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
    print_quads();
    write_quads_to_file("quads.txt");
    return 0;
}
