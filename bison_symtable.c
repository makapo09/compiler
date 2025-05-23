#include "bison_symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol_t* hashTable[HASH_SIZE];
Symbol_t* scopeList[HASH_SIZE];
int maxScope;

unsigned int hash(const char* key) {
    unsigned int hash = 5381;
    while (*key)
        hash = ((hash << 5) + hash) + *(key++);
    return hash % HASH_SIZE;
}

void SymTable_init() {
    memset(hashTable, 0, sizeof(hashTable));
    memset(scopeList, 0, sizeof(scopeList));
    maxScope = 0;
    const char* lib_funcs[] = {
        "print", "input", "objectmemberkeys", "objecttotalmembers",
        "objectcopy", "totalarguments", "argument", "typeof",
        "strtonum", "sqrt", "cos", "sin"
    };

    for(int i = 0; i < 12; i++)
        SymTable_insert(lib_funcs[i], LIB_FUNC, 0, 0);
}

Symbol_t* SymTable_insert(const char* name, SymbolType type, unsigned int scope, unsigned int line) {
    Symbol_t* sym = (Symbol_t*)malloc(sizeof(Symbol_t));
    sym->name = strdup(name);
    sym->type = type;
    sym->scope = scope;
    sym->line = line;
    sym->isActive = true;
    sym->next = NULL;
    sym->scope_next = NULL;

    unsigned int index = hash(name);

    if (scope > maxScope) {
        maxScope = scope;
    }

    if(hashTable[index] == NULL) {
        sym->next = hashTable[index];
        hashTable[index] = sym;
    } else {
    Symbol_t* iterator = hashTable[index];

        while(iterator->next != NULL){
        iterator = iterator->next;
        }
        iterator->next = sym;
    }
    
    if(scopeList[scope] == NULL) {
        sym->scope_next = scopeList[scope];
        scopeList[scope] = sym;
    } else {
        Symbol_t* iterator = scopeList[scope];
        while(iterator->scope_next != NULL) {
            iterator = iterator->scope_next;
        }
        iterator->scope_next = sym;
    }

    return sym;
}

Symbol_t* SymTable_lookup(const char* name, unsigned int scope) {
    unsigned int index = hash(name);
    Symbol_t* sym = hashTable[index];

    while(sym) {
        if(strcmp(sym->name, name) == 0 && sym->scope == scope && sym->isActive)
            return sym;
        sym = sym->next;
    }

    return NULL;
}

Symbol_t* SymTable_lookupGlobal(const char* name) {
    return SymTable_lookup(name, 0);
}

int SymTable_lookupGlobalFuncs(const char* name) {
    Symbol_t* temp = SymTable_lookup(name, 0);
    
    if(temp){
        return temp->type==LIB_FUNC;
    }

    return 0;
}

void hideScope(unsigned int scope) {
    Symbol_t* sym = scopeList[scope];
    while(sym) {
        sym->isActive = false;
        sym = sym->scope_next;
    }
}

const char* symbolTypeToString(SymbolType type) {
    switch(type) {
        case GLOBAL_VAR: return "GLOBAL_VAR";
        case LOCAL_VAR: return "LOCAL_VAR";
        case FORMAL_ARG: return "FORMAL_ARG";
        case USER_FUNC: return "USER_FUNC";
        case LIB_FUNC: return "LIB_FUNC";
        default: return "UNKNOWN";
    }
}

void SymTable_print() {
    for (int i = 0; i <= maxScope; i++) {
        Symbol_t* sym = scopeList[i];
        printf("\n-------- Scope #%d --------\n", i);
        while (sym) {
            printf("\"%s\" [%s] (line %u) (scope %u)\n",
                   sym->name,
                   symbolTypeToString(sym->type),
                   sym->line,
                   sym->scope);
            sym = sym->scope_next;
        }
    }
}

Symbol_t* insert_temp(const char* name) {
    return SymTable_insert(name, LOCAL_VAR, 0, 0);
}
