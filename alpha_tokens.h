#ifndef ALPHA_TOKENS_H
#define ALPHA_TOKENS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YY_DECL int alpha_yylex (void* yyval)

typedef struct alpha_token {
    int line;
    char* token;
    char* category;
    char* type;
    struct alpha_token* next;
} alpha_token_t;

void add_token(int line, const char* token, const char* category, const char* type);
void print_tokens();
void free_tokens();

char* addEscapeChar(char* string,int* i, char escape_char);


#endif
