#ifndef AVM_H
#define AVM_H
#include "target_code.h"
#include <stdbool.h>

#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4
#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1
#define AVM_TABLE_HASHSIZE 211
#define M_PI 3.14159265358979323846

// Memory cell types
typedef enum avm_memcell_t {
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
} avm_memcell_t;

// User function structure
typedef struct userfunc {
    unsigned address;
    unsigned localSize;
    char* id;
} userfunc;

// Table structure
typedef struct avm_table {
    unsigned refCounter;
    struct avm_table_bucket** strIndexed;
    struct avm_table_bucket** numIndexed;
    unsigned total;
} avm_table;

// Memory cell
typedef struct avm_memcell {
    avm_memcell_t type;
    union {
        double numVal;
        char* strVal;
        unsigned char boolVal;
        avm_table* tableVal;
        unsigned funcVal;
        char* libfuncVal;
    } data;
} avm_memcell;

// Table bucket for hash table
typedef struct avm_table_bucket {
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket* next;
} avm_table_bucket;

// VM registers and stack
extern avm_memcell stack[AVM_STACKSIZE];
extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern unsigned char executionFinished;
extern unsigned pc;
extern unsigned currLine;
extern unsigned totalActuals;

// User functions array
extern struct userfunc* userFuncs;
extern unsigned totalUserFuncs;

// Execution functions
void avm_initialize(void);
void avm_load_program(const char* filename);
void execute_cycle(void);
void avm_error(const char* format, ...);
void avm_warning(const char* format, ...);

// Operand translation function
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

// Memory cell operations
void avm_memcellclear(avm_memcell* m);
void avm_assign(avm_memcell* lv, avm_memcell* rv);

// Table operations
avm_table* avm_tablenew(void);
void avm_tableincrefcounter(avm_table* t);
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p);
void avm_tablebucketsdestroy(avm_table_bucket** p);
avm_memcell* avm_tablegetelem(avm_table* t, avm_memcell* key);
void avm_tablesetelem(avm_table* t, avm_memcell* key, avm_memcell* value);
char* avm_table_tostring(avm_table* t);

// Type conversions
char* avm_tostring(avm_memcell* m);
double avm_tonumber(avm_memcell* m);
unsigned char avm_tobool(avm_memcell* m);

// Library function type
typedef void (*library_func_t)(void);

// Library functions
void libfunc_print(void);
void libfunc_typeof(void);
void libfunc_totalarguments(void);
void libfunc_argument(void);
void libfunc_input(void);
void libfunc_objectmemberkeys(void);
void libfunc_objecttotalmembers(void);
void libfunc_objectcopy(void);
void libfunc_strtonum(void);
void libfunc_sqrt(void);
void libfunc_cos(void);
void libfunc_sin(void);

// Register library functions
void avm_registerlibfunc(const char* id, library_func_t addr);
library_func_t avm_getlibraryfunc(const char* id);

// Helper functions
unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned i);
unsigned avm_get_envvalue(unsigned i);
void avm_dec_top(void);

#endif