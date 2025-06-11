#include "avm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include <math.h>

// VM state
avm_memcell stack[AVM_STACKSIZE];
avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top = AVM_STACKSIZE - 1;
unsigned topsp = AVM_STACKSIZE - 1;
unsigned char executionFinished = 0;
unsigned pc = 0;
unsigned currLine = 0;
unsigned totalActuals = 0;

// Program data (loaded from binary)
static instruction* code = NULL;
static unsigned codeSize = 0;
static double* numConsts = NULL;
static unsigned totalNumConsts = 0;
static char** stringConsts = NULL;
static unsigned totalStringConsts = 0;
static char** namedLibfuncs = NULL;
static unsigned totalNamedLibfuncs = 0;
static struct userfunc* userFuncs = NULL;
static unsigned totalUserFuncs = 0;

// Library functions table
typedef struct libfunc_entry {
    char* id;
    library_func_t func;
    struct libfunc_entry* next;
} libfunc_entry;

static libfunc_entry* libfuncs = NULL;

void avm_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Runtime error at line %u: ", currLine);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    executionFinished = 1;
}

void avm_warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void avm_memcellclear(avm_memcell* m) {
    if (m->type == string_m && m->data.strVal) {
        free(m->data.strVal);
        m->data.strVal = NULL;
    } else if (m->type == table_m && m->data.tableVal) {
        avm_tabledecrefcounter(m->data.tableVal);
        m->data.tableVal = NULL;
    }
    m->type = undef_m;
}

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
    if (lv == rv) return;
    
    if (lv->type == table_m && lv->data.tableVal && lv->data.tableVal->refCounter > 0) {
        avm_tabledecrefcounter(lv->data.tableVal);
    }
    
    avm_memcellclear(lv);
    
    lv->type = rv->type;
    switch (rv->type) {
        case string_m:
            lv->data.strVal = strdup(rv->data.strVal);
            break;
        case table_m:
            lv->data.tableVal = rv->data.tableVal;
            avm_tableincrefcounter(lv->data.tableVal);
            break;
        default:
            lv->data = rv->data;
            break;
    }
}

// Table implementation
avm_table* avm_tablenew(void) {
    avm_table* t = (avm_table*)malloc(sizeof(avm_table));
    t->refCounter = 0;
    t->total = 0;
    
    t->strIndexed = (avm_table_bucket**)malloc(AVM_TABLE_HASHSIZE * sizeof(avm_table_bucket*));
    t->numIndexed = (avm_table_bucket**)malloc(AVM_TABLE_HASHSIZE * sizeof(avm_table_bucket*));
    
    for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        t->strIndexed[i] = NULL;
        t->numIndexed[i] = NULL;
    }
    
    return t;
}

void avm_tableincrefcounter(avm_table* t) {
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t) {
    assert(t->refCounter > 0);
    if (--t->refCounter == 0) {
        avm_tablebucketsdestroy(t->strIndexed);
        avm_tablebucketsdestroy(t->numIndexed);
        free(t->strIndexed);
        free(t->numIndexed);
        free(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p) {
    for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        p[i] = NULL;
    }
}

void avm_tablebucketsdestroy(avm_table_bucket** p) {
    for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        avm_table_bucket* b = p[i];
        while (b) {
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = NULL;
    }
}

// Type conversion functions
char* avm_tostring(avm_memcell* m) {
    static char buffer[512];
    
    switch (m->type) {
        case number_m:
            sprintf(buffer, "%.3f", m->data.numVal);
            break;
        case string_m:
            return strdup(m->data.strVal);
        case bool_m:
            strcpy(buffer, m->data.boolVal ? "true" : "false");
            break;
        case table_m:
            return avm_table_tostring(m->data.tableVal);
        case userfunc_m:
            sprintf(buffer, "user function %u", userFuncs[m->data.funcVal].address);
            break;
        case libfunc_m:
            sprintf(buffer, "library function %s", m->data.libfuncVal);
            break;
        case nil_m:
            strcpy(buffer, "nil");
            break;
        case undef_m:
            strcpy(buffer, "undefined");
            break;
        default:
            assert(0);
    }
    return strdup(buffer);
}

// Helper function to convert table to string
char* avm_table_tostring(avm_table* t) {
    char* result = (char*)malloc(4096);  // Start with reasonable size
    strcpy(result, "[ ");
    
    int first = 1;
    
    // Print all entries
    for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        // Number-indexed entries
        avm_table_bucket* b = t->numIndexed[i];
        while (b) {
            if (!first) strcat(result, ", ");
            first = 0;
            
            // Handle numeric keys - don't show key for array-like access
            if (b->key.type == number_m) {
                char* valStr = avm_tostring(&b->value);
                strcat(result, valStr);
                free(valStr);
            }
            b = b->next;
        }
        
        // String-indexed entries
        b = t->strIndexed[i];
        while (b) {
            if (!first) strcat(result, ", ");
            first = 0;
            
            strcat(result, "{ ");
            char* keyStr = avm_tostring(&b->key);
            strcat(result, keyStr);
            free(keyStr);
            strcat(result, " : ");
            char* valStr = avm_tostring(&b->value);
            strcat(result, valStr);
            free(valStr);
            strcat(result, " }");
            
            b = b->next;
        }
    }
    
    strcat(result, " ]");
    return result;
}

double avm_tonumber(avm_memcell* m) {
    switch (m->type) {
        case number_m:
            return m->data.numVal;
        case string_m: {
            char* end;
            double val = strtod(m->data.strVal, &end);
            if (*end != '\0') {
                avm_error("Cannot convert string '%s' to number", m->data.strVal);
                return 0;
            }
            return val;
        }
        case bool_m:
            return m->data.boolVal ? 1.0 : 0.0;
        case nil_m:
            return 0;
        default:
            avm_error("Cannot convert %s to number", avm_tostring(m));
            return 0;
    }
}

unsigned char avm_tobool(avm_memcell* m) {
    switch (m->type) {
        case number_m:
            return m->data.numVal != 0;
        case string_m:
            return strlen(m->data.strVal) > 0;
        case bool_m:
            return m->data.boolVal;
        case table_m:
            return 1;
        case userfunc_m:
        case libfunc_m:
            return 1;
        case nil_m:
            return 0;
        case undef_m:
            avm_error("'undef' has no boolean value");
            return 0;
        default:
            assert(0);
            return 0;
    }
}

// Library function management
void avm_registerlibfunc(const char* id, library_func_t addr) {
    libfunc_entry* entry = (libfunc_entry*)malloc(sizeof(libfunc_entry));
    entry->id = strdup(id);
    entry->func = addr;
    entry->next = libfuncs;
    libfuncs = entry;
}

library_func_t avm_getlibraryfunc(const char* id) {
    libfunc_entry* entry = libfuncs;
    while (entry) {
        if (strcmp(entry->id, id) == 0)
            return entry->func;
        entry = entry->next;
    }
    return NULL;
}

// Library functions implementation
void libfunc_print(void) {
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; i++) {
        char* s = avm_tostring(avm_getactual(i));
        printf("%s", s);
        free(s);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
}

void libfunc_input(void) {
    char buffer[1024];
    avm_memcellclear(&retval);
    
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        retval.type = nil_m;
        return;
    }
    
    // Remove newline
    buffer[strcspn(buffer, "\n")] = 0;
    
    // Check for boolean
    if (strcmp(buffer, "true") == 0) {
        retval.type = bool_m;
        retval.data.boolVal = 1;
        return;
    }
    if (strcmp(buffer, "false") == 0) {
        retval.type = bool_m;
        retval.data.boolVal = 0;
        return;
    }
    
    // Check for nil
    if (strcmp(buffer, "nil") == 0) {
        retval.type = nil_m;
        return;
    }
    
    // Check if it's a quoted string
    if (buffer[0] == '"' && buffer[strlen(buffer)-1] == '"') {
        buffer[strlen(buffer)-1] = '\0';
        retval.type = string_m;
        retval.data.strVal = strdup(buffer + 1);
        return;
    }
    
    // Try to parse as number
    char* endptr;
    double num = strtod(buffer, &endptr);
    if (*endptr == '\0') {
        retval.type = number_m;
        retval.data.numVal = num;
        return;
    }
    
    // Otherwise, it's a string
    retval.type = string_m;
    retval.data.strVal = strdup(buffer);
}

void libfunc_objectmemberkeys(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("objectmemberkeys expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* t = avm_getactual(0);
    if (t->type != table_m) {
        avm_error("objectmemberkeys expects a table argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    retval.type = table_m;
    retval.data.tableVal = avm_tablenew();
    avm_tableincrefcounter(retval.data.tableVal);
    
    unsigned index = 0;
    
    // Iterate through string-indexed entries
    for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        avm_table_bucket* b = t->data.tableVal->strIndexed[i];
        while (b) {
            if (b->key.type == string_m) {
                avm_memcell key;
                key.type = number_m;
                key.data.numVal = index++;
                avm_tablesetelem(retval.data.tableVal, &key, &b->key);
            }
            b = b->next;
        }
    }
}

void libfunc_objecttotalmembers(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("objecttotalmembers expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* t = avm_getactual(0);
    if (t->type != table_m) {
        avm_error("objecttotalmembers expects a table argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = t->data.tableVal->total;
}

void libfunc_objectcopy(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("objectcopy expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* t = avm_getactual(0);
    if (t->type != table_m) {
        avm_error("objectcopy expects a table argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    retval.type = table_m;
    retval.data.tableVal = avm_tablenew();
    avm_tableincrefcounter(retval.data.tableVal);
    
    // Shallow copy - copy all entries
    for (int i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        // Copy string-indexed entries
        avm_table_bucket* b = t->data.tableVal->strIndexed[i];
        while (b) {
            avm_tablesetelem(retval.data.tableVal, &b->key, &b->value);
            b = b->next;
        }
        
        // Copy number-indexed entries
        b = t->data.tableVal->numIndexed[i];
        while (b) {
            avm_tablesetelem(retval.data.tableVal, &b->key, &b->value);
            b = b->next;
        }
    }
}

void libfunc_strtonum(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("strtonum expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* s = avm_getactual(0);
    if (s->type != string_m) {
        avm_error("strtonum expects a string argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    char* endptr;
    double num = strtod(s->data.strVal, &endptr);
    
    if (*endptr == '\0') {
        retval.type = number_m;
        retval.data.numVal = num;
    } else {
        retval.type = nil_m;
    }
}

void libfunc_sqrt(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("sqrt expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* num = avm_getactual(0);
    if (num->type != number_m) {
        avm_error("sqrt expects a number argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    
    if (num->data.numVal < 0) {
        retval.type = nil_m;
    } else {
        retval.type = number_m;
        retval.data.numVal = sqrt(num->data.numVal);
    }
}

void libfunc_cos(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("cos expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* num = avm_getactual(0);
    if (num->type != number_m) {
        avm_error("cos expects a number argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    retval.type = number_m;
    // Convert degrees to radians
    retval.data.numVal = cos(num->data.numVal * M_PI / 180.0);
}

void libfunc_sin(void) {
    unsigned n = avm_totalactuals();
    
    if (n != 1) {
        avm_error("sin expects exactly one argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcell* num = avm_getactual(0);
    if (num->type != number_m) {
        avm_error("sin expects a number argument");
        retval.type = nil_m;
        return;
    }
    
    avm_memcellclear(&retval);
    retval.type = number_m;
    // Convert degrees to radians
    retval.data.numVal = sin(num->data.numVal * M_PI / 180.0);
}

// Initialize VM
void avm_initialize(void) {
    // Clear stack
    for (int i = 0; i < AVM_STACKSIZE; i++) {
        stack[i].type = undef_m;
    }
    
    // Clear registers
    ax.type = bx.type = cx.type = retval.type = undef_m;
    
    // Register library functions
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("totalarguments", libfunc_totalarguments);
    avm_registerlibfunc("argument", libfunc_argument);
    avm_registerlibfunc("input", libfunc_input);
    avm_registerlibfunc("objectmemberkeys", libfunc_objectmemberkeys);
    avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
    avm_registerlibfunc("objectcopy", libfunc_objectcopy);
    avm_registerlibfunc("strtonum", libfunc_strtonum);
    avm_registerlibfunc("sqrt", libfunc_sqrt);
    avm_registerlibfunc("cos", libfunc_cos);
    avm_registerlibfunc("sin", libfunc_sin);
}

// Load program from binary file
void avm_load_program(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Cannot open binary file: %s\n", filename);
        exit(1);
    }
    
    // Read magic number
    unsigned magic;
    fread(&magic, sizeof(unsigned), 1, fp);
    if (magic != 340200501) {
        fprintf(stderr, "Invalid binary file format\n");
        exit(1);
    }
    
    // Read string constants
    fread(&totalStringConsts, sizeof(unsigned), 1, fp);
    stringConsts = (char**)malloc(totalStringConsts * sizeof(char*));
    for (unsigned i = 0; i < totalStringConsts; i++) {
        unsigned len;
        fread(&len, sizeof(unsigned), 1, fp);
        stringConsts[i] = (char*)malloc(len + 1);
        fread(stringConsts[i], sizeof(char), len, fp);
        stringConsts[i][len] = '\0';
    }
    
    // Read number constants
    fread(&totalNumConsts, sizeof(unsigned), 1, fp);
    numConsts = (double*)malloc(totalNumConsts * sizeof(double));
    fread(numConsts, sizeof(double), totalNumConsts, fp);
    
    // Read user functions
    fread(&totalUserFuncs, sizeof(unsigned), 1, fp);
    userFuncs = (struct userfunc*)malloc(totalUserFuncs * sizeof(struct userfunc));
    for (unsigned i = 0; i < totalUserFuncs; i++) {
        fread(&userFuncs[i].address, sizeof(unsigned), 1, fp);
        fread(&userFuncs[i].localSize, sizeof(unsigned), 1, fp);
        unsigned len;
        fread(&len, sizeof(unsigned), 1, fp);
        userFuncs[i].id = (char*)malloc(len + 1);
        fread(userFuncs[i].id, sizeof(char), len, fp);
        userFuncs[i].id[len] = '\0';
    }
    
    // Read library functions
    fread(&totalNamedLibfuncs, sizeof(unsigned), 1, fp);
    namedLibfuncs = (char**)malloc(totalNamedLibfuncs * sizeof(char*));
    for (unsigned i = 0; i < totalNamedLibfuncs; i++) {
        unsigned len;
        fread(&len, sizeof(unsigned), 1, fp);
        namedLibfuncs[i] = (char*)malloc(len + 1);
        fread(namedLibfuncs[i], sizeof(char), len, fp);
        namedLibfuncs[i][len] = '\0';
    }
    
    // Read instructions
    fread(&codeSize, sizeof(unsigned), 1, fp);
    code = (instruction*)malloc(codeSize * sizeof(instruction));
    fread(code, sizeof(instruction), codeSize, fp);
    
    fclose(fp);
}

// Missing helper functions
unsigned avm_totalactuals(void) {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

unsigned avm_get_envvalue(unsigned i) {
    assert(stack[i].type == number_m);
    return (unsigned)stack[i].data.numVal;
}

#define AVM_TABLE_HASHSIZE 211

// Main execution function (implement execute_cycle based on instruction set)
void execute_cycle(void) {
    if (executionFinished)
        return;
    else if (pc >= codeSize) {
        executionFinished = 1;
        return;
    }
    
    instruction* instr = &code[pc];
    currLine = instr->srcLine;
    
    // Execute instruction based on opcode
    // (Implementation of each instruction execution goes here)
    
    pc++;
}

// Add these table operation implementations to avm.c

// Hash function for table keys
static unsigned avm_hash_number(double num) {
    return ((unsigned)num) % AVM_TABLE_HASHSIZE;
}

static unsigned avm_hash_string(const char* str) {
    unsigned hash = 5381;
    while (*str)
        hash = ((hash << 5) + hash) + *(str++);
    return hash % AVM_TABLE_HASHSIZE;
}

avm_memcell* avm_tablegetelem(avm_table* t, avm_memcell* key) {
    assert(t && key);
    
    if (key->type == nil_m || key->type == undef_m) {
        avm_error("invalid table index type: %s", avm_tostring(key));
        return NULL;
    }
    
    avm_table_bucket** buckets = NULL;
    unsigned index = 0;
    
    if (key->type == number_m) {
        buckets = t->numIndexed;
        index = avm_hash_number(key->data.numVal);
    } else if (key->type == string_m) {
        buckets = t->strIndexed;
        index = avm_hash_string(key->data.strVal);
    } else {
        // For project, only number and string keys are mandatory
        avm_error("unsupported table index type: %s", avm_tostring(key));
        return NULL;
    }
    
    avm_table_bucket* b = buckets[index];
    while (b) {
        // Compare keys
        if (key->type == b->key.type) {
            if (key->type == number_m && key->data.numVal == b->key.data.numVal)
                return &b->value;
            else if (key->type == string_m && strcmp(key->data.strVal, b->key.data.strVal) == 0)
                return &b->value;
        }
        b = b->next;
    }
    
    // Key not found - return a static nil cell
    static avm_memcell nil_cell = { .type = nil_m };
    return &nil_cell;
}

void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value) {
    assert(t && key);
    
    if (key->type == nil_m || key->type == undef_m) {
        avm_error("invalid table index type: %s", avm_tostring(key));
        return;
    }
    
    avm_table_bucket** buckets = NULL;
    unsigned index = 0;
    
    if (key->type == number_m) {
        buckets = t->numIndexed;
        index = avm_hash_number(key->data.numVal);
    } else if (key->type == string_m) {
        buckets = t->strIndexed;
        index = avm_hash_string(key->data.strVal);
    } else {
        avm_error("unsupported table index type: %s", avm_tostring(key));
        return;
    }
    
    // Check if key already exists
    avm_table_bucket* b = buckets[index];
    avm_table_bucket* prev = NULL;
    
    while (b) {
        if (key->type == b->key.type) {
            int found = 0;
            if (key->type == number_m && key->data.numVal == b->key.data.numVal)
                found = 1;
            else if (key->type == string_m && strcmp(key->data.strVal, b->key.data.strVal) == 0)
                found = 1;
                
            if (found) {
                // Key exists
                if (value->type == nil_m) {
                    // Delete entry
                    if (prev)
                        prev->next = b->next;
                    else
                        buckets[index] = b->next;
                    
                    avm_memcellclear(&b->key);
                    avm_memcellclear(&b->value);
                    free(b);
                    t->total--;
                    return;
                } else {
                    // Update value
                    avm_memcellclear(&b->value);
                    avm_assign(&b->value, value);
                    return;
                }
            }
        }
        prev = b;
        b = b->next;
    }
    
    // Key doesn't exist and value is nil - nothing to do
    if (value->type == nil_m)
        return;
    
    // Create new entry
    avm_table_bucket* newBucket = (avm_table_bucket*)malloc(sizeof(avm_table_bucket));
    newBucket->key.type = undef_m;
    newBucket->value.type = undef_m;
    
    avm_assign(&newBucket->key, key);
    avm_assign(&newBucket->value, value);
    
    newBucket->next = buckets[index];
    buckets[index] = newBucket;
    t->total++;
}

// Execute table operations
void execute_tablegetelem(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(&instr->result, NULL);
    avm_memcell* t = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &bx);
    
    assert(lv && t && i);
    
    avm_memcellclear(lv);
    
    if (t->type != table_m) {
        avm_error("illegal use of type %s as table", avm_tostring(t));
        executionFinished = 1;
    } else {
        avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
        if (content)
            avm_assign(lv, content);
        else
            lv->type = nil_m;
    }
}

void execute_tablesetelem(instruction* instr) {
    avm_memcell* t = avm_translate_operand(&instr->result, NULL);
    avm_memcell* i = avm_translate_operand(&instr->arg1, &ax);
    avm_memcell* c = avm_translate_operand(&instr->arg2, &bx);
    
    assert(t && i && c);
    
    if (t->type != table_m) {
        avm_error("illegal use of type %s as table", avm_tostring(t));
        executionFinished = 1;
    } else {
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}

// Initialize top and topsp considering globals
void avm_initialize_stack(void) {
    // Count total globals needed (including temps)
    unsigned totalGlobals = 0;
    
    // This should be calculated based on your symbol table
    // For now, let's reserve space for a reasonable number
    totalGlobals = 50;  // Adjust based on your needs
    
    top = AVM_STACKSIZE - 1 - totalGlobals;
    topsp = top;
}