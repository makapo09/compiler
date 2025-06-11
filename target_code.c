// target_code.c 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "target_code.h"
#include "icode.h"

instruction* instructions = NULL;
unsigned totalInstr = 0;
unsigned currInstr = 0;

void expand_instructions(void) {
    assert(totalInstr == currInstr);
    unsigned newTotal = totalInstr + 1024;
    instruction* newInstructions = malloc(newTotal * sizeof(instruction));
    if (instructions) {
        memcpy(newInstructions, instructions, totalInstr * sizeof(instruction));
        free(instructions);
    }
    instructions = newInstructions;
    totalInstr = newTotal;
}

void emit_instruction(vmopcode op, vmarg* result, vmarg* arg1, vmarg* arg2, unsigned srcLine) {
    if (currInstr >= totalInstr)
        expand_instructions();

    instruction* instr = &instructions[currInstr++];
    instr->opcode = op;
    instr->result = result ? *result : (vmarg){.type = NIL_A, .val = -1};
    instr->arg1   = arg1   ? *arg1   : (vmarg){.type = NIL_A, .val = -1};
    instr->arg2   = arg2   ? *arg2   : (vmarg){.type = NIL_A, .val = -1};
    instr->srcLine = srcLine;
}

void print_vmarg_to_file(vmarg* arg, FILE* f) {
    switch (arg->type) {
        case LABEL_A:       fprintf(f, "label:%d", arg->val); break;
        case GLOBAL_A:      fprintf(f, "global:%d", arg->val); break;
        case FORMAL_A:      fprintf(f, "formal:%d", arg->val); break;
        case LOCAL_A:       fprintf(f, "local:%d", arg->val); break;
        case NUMBER_A:      fprintf(f, "number:%d", arg->val); break;
        case STRING_A:      fprintf(f, "string:%d", arg->val); break;
        case BOOL_A:        fprintf(f, "bool:%d", arg->val); break;
        case NIL_A:         fprintf(f, "nil"); break;
        case USERFUNC_A:    fprintf(f, "userfunc:%d", arg->val); break;
        case LIBFUNC_A:     fprintf(f, "libfunc:%d", arg->val); break;
        case RETVAL_A:      fprintf(f, "retval"); break;
        default:            fprintf(f, "UNKNOWN"); break;
    }
}

void print_instructions(FILE* f) {
    for (unsigned i = 0; i < currInstr; i++) {
        fprintf(f, "%3u: ", i);
        fprintf(f, "%s ", opcode_to_string(instructions[i].opcode));
        print_vmarg_to_file(&instructions[i].result, f);
        fprintf(f, ", ");
        print_vmarg_to_file(&instructions[i].arg1, f);
        fprintf(f, ", ");
        print_vmarg_to_file(&instructions[i].arg2, f);
        fprintf(f, "\n");
    }
}

const char* opcode_to_string(vmopcode op) {
    switch (op) {
        case ASSIGN_V: return "assign";
        case ADD_V: return "add";
        case SUB_V: return "sub";
        case MUL_V: return "mul";
        case DIV_V: return "div";
        case MOD_V: return "mod";
        case JUMP_V: return "jump";
        case JEQ_V: return "jeq";
        case JNE_V: return "jne";
        case JLE_V: return "jle";
        case JGE_V: return "jge";
        case JLT_V: return "jlt";
        case JGT_V: return "jgt";
        case CALL_V: return "call";
        case PUSHARG_V: return "pusharg";
        case FUNCENTER_V: return "funcenter";
        case FUNCEXIT_V: return "funcexit";
        case NEWTABLE_V: return "newtable";
        case TABLEGETELEM_V: return "tablegetelem";
        case TABLESETELEM_V: return "tablesetelem";
        case NOP_V: return "nop";
        default: return "invalid_op";
    }
}
