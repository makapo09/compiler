#ifndef GENERATOR_H
#define GENERATOR_H

#include "icode.h"
#include "target_code.h"

// Πρωτότυπα για τις βασικές συναρτήσεις του generator
void generate_instructions(void);
void write_binary_target_code(const char* filename);
void write_text_target_code(const char* filename);

// Πίνακες για τις σταθερές που θα γραφτούν στο binary
extern double* numConsts_get();
extern unsigned totalNumConsts_get();
extern char** stringConsts_get();
extern unsigned totalStringConsts_get();
extern Symbol_t** userFuncs_get();
extern unsigned totalUserFuncs_get();
extern char** namedLibfuncs_get();
extern unsigned totalNamedLibfuncs_get();


#endif // GENERATOR_H