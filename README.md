# Fasi 3 - Endiamesos Kodikas 

Auti einai i triti fasi tou project mas. Se afti tin fasi ftiaxnoume ton endiameso kodika (quads) kai ton sundiazoume me ton parser.

## Prosthika arxeia

### `icode.h` / `icode.c`

* Ftiaxnoume tin domi gia ta **quads** kai diaxirizomaste tis **ekfraseis (expr)**.
* Exoume typous opws: `var_e`, `constnum_e`, `boolexpr_e`, `call`, `jump`, `assign`, `add`, k.t.l.
* Vgazoume quads me tin `emit`.
* Exoume kai sinartiseis gia na ektypwsoume ta quads se arxeio (`write_quads_to_file`) i stin othoni (`print_quads`).

### `backpatch.h` / `backpatch.c`

* Ftiaxnoume lista me labels gia `true`, `false`, `break`, `continue`.
* Me to `backpatch` kanoume update ta quads otan katalavoume pou tha pigenoun oi jumps.

## Allages ston `parser.y`

* O parser tora ftiaxnei **expr** kai **quads** gia:

  * prakseis (add, sub, k.t.l.)
  * if / while / for me `backpatch`
  * break / continue me `breaklist` kai `continuelist`
* Xrisimopoioume tis nees sinartiseis pou exoume sto `icode.c`.




