CC = gcc
CFLAGS = -Wall -g

LEX = flex
YACC = bison

all: alpha

alpha: scanner.c parser.c bison_symtable.c alpha_tokens.c icode.c backpatch.c
	$(CC) $(CFLAGS) -o alpha scanner.c parser.c bison_symtable.c alpha_tokens.c icode.c backpatch.c

parser.c: parser.y
	$(YACC) --yacc --defines --output=parser.c parser.y

scanner.c: al.l
	$(LEX) --outfile=scanner.c al.l

run: alpha
	./alpha < input.asc

clean:
	rm -f alpha scanner.c parser.c parser.h lex.yy.c *.o quads.txt

.PHONY: all run clean
