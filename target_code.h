#ifndef TARGET_CODE_H
#define TARGET_CODE_H

#include <stdio.h>

// Τύποι ορισμάτων VM εντολών
typedef enum {
    LABEL_A = 0,
    GLOBAL_A,
    FORMAL_A,
    LOCAL_A,
    NUMBER_A,
    STRING_A,
    BOOL_A,
    NIL_A,
    USERFUNC_A,
    LIBFUNC_A,
    RETVAL_A
} vmarg_t;

// Δομή ορίσματος VM εντολής
typedef struct {
    vmarg_t type;
    int val;
} vmarg;

// Τύποι VM εντολών (opcodes)
typedef enum {
    ASSIGN_V,
    ADD_V,
    SUB_V,
    MUL_V,
    DIV_V,
    MOD_V,
    JUMP_V,
    JEQ_V,
    JNE_V,
    JLE_V,
    JGE_V,
    JLT_V,
    JGT_V,
    CALL_V,
    PUSHARG_V,
    FUNCENTER_V,
    FUNCEXIT_V,
    NEWTABLE_V,
    TABLEGETELEM_V,
    TABLESETELEM_V,
    NOP_V
} vmopcode;

// Δομή εντολής VM
typedef struct {
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
} instruction;

// Πίνακας εντολών
extern instruction* instructions;
extern unsigned totalInstr;
extern unsigned currInstr;

// Συναρτήσεις που παρέχονται
void emit_instruction(vmopcode op, vmarg* result, vmarg* arg1, vmarg* arg2, unsigned srcLine);
void expand_instructions(void);
void print_vmarg_to_file(vmarg* arg, FILE* f);
void print_instructions(FILE* f);
const char* opcode_to_string(vmopcode op);

#endif // TARGET_CODE_H