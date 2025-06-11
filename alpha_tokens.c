#include "alpha_tokens.h"

static alpha_token_t* head = NULL;

void add_token(int line, const char* token, const char* category, const char* type) {
    alpha_token_t* new_token = (alpha_token_t*)malloc(sizeof(alpha_token_t));
    if (!new_token) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_token->line = line;
    new_token->token = strdup(token);
    new_token->category = strdup(category);
    new_token->type = strdup(type);
    new_token->next = NULL;

    if (!head) {
        head = new_token;
    } else {
        alpha_token_t* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_token;
    }
}

void print_tokens() {
    alpha_token_t* temp = head;
    while (temp) {
        printf("Line: %d Token: %s Category: %s Type: %s\n", temp->line, temp->token, temp->category, temp->type);
        temp = temp->next;
    }
}

void free_tokens() {
    alpha_token_t* temp = head;
    while (temp) {
        alpha_token_t* next = temp->next;
        free(temp->token);
        free(temp->category);
        free(temp->type);
        free(temp);
        temp = next;
    }
    head = NULL;
}

char* addEscapeChar(char* string,int* i, char escape_char){
    char* temp = (char*)realloc(string,(*i+1)*sizeof(char));
    temp[*i]= escape_char;
    *i = *i + 1;
    return temp;
}