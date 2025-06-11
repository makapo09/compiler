// avm_main.c - Standalone Alpha Virtual Machine
#include "avm.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_file.abc>\n", argv[0]);
        return 1;
    }
    
    printf("Alpha Virtual Machine v1.0\n");
    printf("Loading program: %s\n", argv[1]);
    
    // Initialize VM
    avm_initialize();
    
    // Load binary
    avm_load_program(argv[1]);
    
    printf("Executing...\n");
    printf("====================\n");
    
    // Execute program
    while (!executionFinished) {
        execute_cycle();
    }
    
    printf("====================\n");
    printf("Execution completed.\n");
    
    return 0;
}