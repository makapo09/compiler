%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "icode.h"
    #include "alpha_tokens.h"
    #include "parser.h" 


    extern int alpha_yylex(void *);
    extern FILE *yyin;

    char* string = NULL;
    int i,counter=1;
%}

%option noinput nounput
%option yylineno
%option noyywrap

/* Keywords */
IF "if"
ELSE "else"
WHILE "while"
FOR "for"
FUNCTION "function"
RETURN "return"
BREAK "break"
CONTINUE "continue"
AND "and"
OR "or"
NOT "not"
TRUE "true"
FALSE "false"
NIL "nil"
LOCAL "local"

/* Operators */
ASSIGN "="
PLUS "+"
MINUS "-"
MULTIPLY "*"
DIVIDE "/"
MODULO "%"
EQUAL "=="
NOT_EQUAL "!="
INCREMENT "++"
DECREMENT "--"
GREATER_THAN ">"
LESS_THAN "<"
GREATER_EQUAL ">="
LESS_EQUAL "<="

/* Punctuation */
BRACKET_OPEN "("
BRACKET_CLOSE ")"
CURLY_BRACKET_OPEN "{"
CURLY_BRACKET_CLOSE "}"
SQUARE_BRACKET_OPEN "["
SQUARE_BRACKET_CLOSE "]"
COMMA ","
SEMICOLON ";"
COLON ":"
DOUBLE_COLON "::"
DOT "."
DOUBLE_DOT ".."


INTCONST  [0-9]+
FLOATCONST [0-9]+\.[0-9]+ 
IDENTIFIER      [a-zA-Z_][a-zA-Z0-9_]*
LINE_COMMENT    "//".*  
WHITESPACE      [ \t\r\n]+
OTHER          .

%x STRING 
%x COMMENTS 

%% 
{IF} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return IF;}
{ELSE} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return ELSE;}
{WHILE} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return WHILE;}
{FOR} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return FOR;}
{FUNCTION} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return FUNCTION;}
{RETURN} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return RETURN;}
{BREAK} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return BREAK;}
{CONTINUE} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return CONTINUE;}
{AND} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return AND;}
{OR} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return OR;}
{NOT} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return NOT;}
{TRUE} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return TRUE;}
{FALSE} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return FALSE;}
{NIL} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return NIL;}
{LOCAL} {add_token(yylineno, yytext, "KEYWORD", "enumarated"); return LOCAL;}

{ASSIGN} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return ASSIGN;}
{PLUS} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return PLUS;}
{MINUS} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return MINUS;}
{MULTIPLY} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return MULTIPLY;}
{DIVIDE} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return DIVIDE;}
{MODULO} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return MODULO;}
{EQUAL} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return EQUAL;}
{NOT_EQUAL} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return NOT_EQUAL;}
{INCREMENT} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return INCREMENT;}
{DECREMENT} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return DECREMENT;}
{GREATER_THAN} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return GREATER_THAN;}
{LESS_THAN} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return LESS_THAN;}
{GREATER_EQUAL} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return GREATER_EQUAL;}
{LESS_EQUAL} {add_token(yylineno, yytext, "OPERATOR", "enumarated"); return LESS_EQUAL;}

{BRACKET_OPEN} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return BRACKET_OPEN;}
{BRACKET_CLOSE} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return BRACKET_CLOSE;}
{CURLY_BRACKET_OPEN} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return CURLY_BRACKET_OPEN;}
{CURLY_BRACKET_CLOSE} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return CURLY_BRACKET_CLOSE;}
{SQUARE_BRACKET_OPEN} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return SQUARE_BRACKET_OPEN;}
{SQUARE_BRACKET_CLOSE} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return SQUARE_BRACKET_CLOSE;}
{COMMA} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return COMMA;}
{SEMICOLON} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return SEMICOLON;}
{COLON} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return COLON;}
{DOUBLE_COLON} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return DOUBLE_COLON;}
{DOT} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return DOT;}
{DOUBLE_DOT} {add_token(yylineno, yytext, "PUNCTUATION", "enumarated"); return DOUBLE_DOT;}

{INTCONST} {add_token(yylineno, yytext, "CONSTANT", "int"); yylval.intVal = atoi(yytext); return INTCONST;}
{FLOATCONST} {add_token(yylineno, yytext, "CONSTANT", "float"); yylval.floatVal = atof(yytext); return FLOATCONST;}
{IDENTIFIER} {add_token(yylineno, yytext, "IDENTIFIER", "char*"); yylval.strVal = strdup(yytext);  return IDENTIFIER;}
{LINE_COMMENT} {add_token(yylineno, "Single Line Comment", "COMMENTS", "char*");}


\"  {BEGIN(STRING); i = 0; string = (char*)malloc(sizeof(char));} 
<STRING>\" {
            string[i]='\0';
            i++;
            add_token(yylineno, string, "STRING", "char*");
            BEGIN(INITIAL);
            yylval.strVal = strdup(string);
            free(string);
            i = 0;
            return STRING_TOKEN;}
<STRING>\\n {
    string = addEscapeChar(string,&i,'\n');
    }
<STRING>\\t {
    string = addEscapeChar(string,&i,'\t');
    }
<STRING>\\\" {
    addEscapeChar(string,&i,'\"');
    }
<STRING>\\ {
    string = addEscapeChar(string,&i,'\\');
    }
<STRING>. {
    string = (char*)realloc(string,(i+1)*sizeof(char));
    string[i]=*yytext;
    ++i;
    }
<STRING>\\[a-zA-Z] {printf("Error: Character %s cannot be escaped\n",yytext);}
<STRING><<EOF>> {printf("Error: String not closed\n"); exit(0);}




"/*" {BEGIN(COMMENTS); counter=1;}
<COMMENTS>[^*/\n]+    {}
<COMMENTS>\*          {}
<COMMENTS>"/"         {}
<COMMENTS>\n          {}
<COMMENTS>"/*" {counter++;} 
<COMMENTS>"*/" { 

                counter--;
                if(counter == 0){
                    add_token(yylineno, "Multiline Outer Comment", "COMMENTS", "char*");
                    BEGIN(INITIAL);
                }else{
                    add_token(yylineno, "Multiline Inner comment", "COMMENTS", "char*");
                }} 
<COMMENTS><<EOF>>  {printf("Error: Comment not closed\n"); exit(0);}

{WHITESPACE} {}
{OTHER} {printf("Error: Unknown token %s\n", yytext); return OTHER;}
%%

/*
int main (int argc, char** argv){
    if(argc>1){
        if(!(yyin=fopen(argv[1],"r"))){
            fprintf(stderr,"Cannot read file: %s\n",argv[1]);
            return 1;
        }
    }else{
        yyin=stdin;
    }

    alpha_yylex(NULL); 

    print_tokens();
    return 0;
}
*/
