CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm

LEX = flex
YACC = bison

# Object files
OBJS = scanner.o parser.o bison_symtable.o alpha_tokens.o icode.o target_code.o
AVM_OBJS = avm_main.o avm.o

# Main targets
all: alpha avm

# Phase 1-4: Compiler
alpha: $(OBJS)
	$(CC) $(CFLAGS) -o alpha $(OBJS) $(LDFLAGS)

# Phase 5: Virtual Machine (standalone)  
avm: $(AVM_OBJS)
	$(CC) $(CFLAGS) -o avm $(AVM_OBJS) $(LDFLAGS)

# Pattern rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Parser generation
parser.c parser.h: parser.y
	$(YACC) --yacc --defines --output=parser.c parser.y

# Scanner generation
scanner.c: al.l parser.h
	$(LEX) --outfile=scanner.c al.l

# Dependencies
scanner.o: scanner.c parser.h alpha_tokens.h
parser.o: parser.c bison_symtable.h alpha_tokens.h icode.h target_code.h
bison_symtable.o: bison_symtable.c bison_symtable.h
alpha_tokens.o: alpha_tokens.c alpha_tokens.h
icode.o: icode.c icode.h bison_symtable.h
target_code.o: target_code.c target_code.h icode.h
avm_main.o: avm_main.c avm.h target_code.h
avm.o: avm.c avm.h target_code.h

# Test with single file
test: alpha
	./alpha input.asc
	@echo "Generated files:"
	@ls -la quads.txt alpha.abc alpha.txt 2>/dev/null || echo "Some files missing"

# Test all files in tests directory
testall: alpha
	@echo "Running all tests..."
	@for test in tests/*.asc; do \
		echo "Testing $test:"; \
		./alpha $test; \
		echo "-------------------"; \
	done

# Run specific test
testfile: alpha
	@if [ -z "$(FILE)" ]; then \
		echo "Usage: make testfile FILE=tests/example.asc"; \
	else \
		./alpha $(FILE); \
	fi

# Run compiler and VM
run: alpha avm
	./alpha input.asc
	./avm alpha.abc

# Clean build files
clean:
	rm -f alpha avm *.o scanner.c parser.c parser.h lex.yy.c quads.txt alpha.abc alpha.txt

# Deep clean (including test outputs)
cleanall: clean
	rm -f tests/*.txt tests/*.abc

.PHONY: all test testall testfile run clean cleanall