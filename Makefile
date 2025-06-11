# Μεταγλωττιστές και Εργαλεία
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lm
LEX = flex
YACC = bison

# Λίστες Object Files
# Προστέθηκε το generator.o για τον compiler
OBJS = scanner.o parser.o bison_symtable.o alpha_tokens.o icode.o target_code.o generator.o
AVM_OBJS = avm_main.o avm.o

# Κύριοι Στόχοι: Ο compiler (alpha) και η Virtual Machine (avm)
all: alpha avm

# Κανόνας για τη δημιουργία του compiler 'alpha'
alpha: $(OBJS)
	$(CC) $(CFLAGS) -o alpha $(OBJS) $(LDFLAGS)

# Κανόνας για τη δημιουργία της 'avm'
avm: $(AVM_OBJS)
	$(CC) $(CFLAGS) -o avm $(AVM_OBJS) $(LDFLAGS)

# Γενικός κανόνας για τη δημιουργία .o από .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Κανόνες για την παραγωγή του parser και του scanner
parser.c parser.h: parser.y
	$(YACC) --yacc --defines --output=parser.c parser.y

scanner.c: al.l parser.h
	$(LEX) --outfile=scanner.c al.l

# Εξαρτήσεις των object files από τα headers
scanner.o: scanner.c parser.h alpha_tokens.h icode.h
parser.o: parser.c bison_symtable.h alpha_tokens.h icode.h target_code.h generator.h
bison_symtable.o: bison_symtable.c bison_symtable.h
alpha_tokens.o: alpha_tokens.c alpha_tokens.h
icode.o: icode.c icode.h bison_symtable.h
target_code.o: target_code.c target_code.h icode.h
generator.o: generator.c generator.h icode.h target_code.h bison_symtable.h

avm_main.o: avm_main.c avm.h target_code.h
avm.o: avm.c avm.h target_code.h

# Στόχος για αυτόματο έλεγχο με το testing.sh
# Βεβαιωθείτε ότι το testing.sh είναι εκτελέσιμο (chmod +x testing.sh)
test: alpha
	@echo "Running automated tests with testing.sh..."
	@./testing.sh

# Στόχος για γρήγορη μεταγλώττιση και εκτέλεση ενός αρχείου 'input.asc'
run: alpha avm
	@echo "Compiling input.asc..."
	./alpha input.asc
	@echo "Executing alpha.abc with AVM..."
	./avm alpha.abc

# Καθαρισμός των αρχείων που παράγονται
clean:
	rm -f alpha avm *.o scanner.c parser.c parser.h quads.txt alpha.abc alpha.txt

# Πλήρης καθαρισμός (συμπεριλαμβανομένων των test outputs)
cleanall: clean
	rm -rf test/output

.PHONY: all test run clean cleanall

