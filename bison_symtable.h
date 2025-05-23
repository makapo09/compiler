#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdbool.h>

#define HASH_SIZE 509

typedef enum {
    GLOBAL_VAR,
    LOCAL_VAR,
    FORMAL_ARG,
    USER_FUNC,
    LIB_FUNC
} SymbolType;

typedef struct Symbol {
    char* name;
    SymbolType type;
    unsigned int scope;
    unsigned int line;
    bool isActive;
    struct Symbol* next;
    struct Symbol* scope_next;
} Symbol_t;

void SymTable_init();
Symbol_t* SymTable_insert(const char* name, SymbolType type, unsigned int scope, unsigned int line);
Symbol_t* SymTable_lookup(const char* name, unsigned int scope);
Symbol_t* SymTable_lookupGlobal(const char* name);
int SymTable_lookupGlobalFuncs(const char* name);
void hideScope(unsigned int scope);
void SymTable_print();
Symbol_t* insert_temp(const char* name);

#endif
