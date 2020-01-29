# Ian Braudaway
# makefile for emblem

EMBLEM_OBJS = types.o lexeme.o lexer.o recognizer.o environment.o evaluator.o main.o
OPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g
CC = gcc

all : emblem

emblem : $(EMBLEM_OBJS)
	$(CC) $(LOPTS) $(EMBLEM_OBJS) -o emblem -lm

types.o : types.c types.h
	$(CC) $(OPTS) types.c

lexeme.o : lexeme.c lexeme.h
	$(CC) $(OPTS) lexeme.c

lexer.o : lexer.c lexer.h
	$(CC) $(OPTS) lexer.c

recognizer.o : recognizer.c recognizer.h
	$(CC) $(OPTS) recognizer.c

environment.o : environment.c environment.h
	$(CC) $(OPTS) environment.c

evaluator.o : evaluator.c evaluator.h
	$(CC) $(OPTS) evaluator.c

main.o : main.c
	$(CC) $(OPTS) main.c

clean : 
	rm -f $(EMBLEM_OBJS) ./types ./lexeme ./lexer ./recognizer ./environment ./evaluator ./emblem

error1 : 
	@echo ""
	@cat error1.e
	@echo ""
	@echo ""

error1x : emblem
	@echo ""
	@./emblem error1.e
	@echo ""
	@echo ""

error2 : 
	@echo ""
	@cat error2.e
	@echo ""
	@echo ""

error2x : emblem
	@echo ""
	@./emblem error2.e
	@echo ""
	@echo ""

error3 : 
	@echo ""
	@cat error3.e
	@echo ""
	@echo ""

error3x : emblem
	@echo ""
	@./emblem error3.e
	@echo ""
	@echo ""

error4 : 
	@echo ""
	@cat error4.e
	@echo ""
	@echo ""

error4x : emblem
	@echo ""
	@./emblem error4.e
	@echo ""
	@echo ""

error5 : 
	@echo ""
	@cat error5.e
	@echo ""
	@echo ""

error5x : emblem
	@echo ""
	@./emblem error5.e
	@echo ""
	@echo ""

problem : 
	@echo ""
	@cat problem.e
	@echo ""
	@echo ""

problemx : emblem
	@echo ""
	@./emblem ./problem.e ./integers
	@echo ""
	@echo ""

arrays : 
	@echo ""
	@cat arrays.e
	@echo ""
	@echo ""

arraysx : emblem
	@echo ""
	@./emblem arrays.e
	@echo ""
	@echo ""

conditionals :
	@echo ""
	@cat conditionals.e
	@echo ""
	@echo ""

conditionalsx : emblem
	@echo ""
	@./emblem conditionals.e
	@echo ""
	@echo ""

recursion :
	@echo ""
	@cat recursion.e
	@echo ""
	@echo ""

recursionx : emblem
	@echo ""
	@./emblem recursion.e
	@echo ""
	@echo ""

iteration :
	@echo ""
	@cat iteration.e
	@echo ""
	@echo ""

iterationx : emblem
	@echo ""
	@./emblem iteration.e
	@echo ""
	@echo ""

functions :
	@echo ""
	@cat functions.e
	@echo ""
	@echo ""

functionsx: emblem
	@echo ""
	@./emblem functions.e
	@echo ""
	@echo ""

lambda :
	@echo ""
	@cat lambda.e
	@echo ""
	@echo ""

lambdax : emblem
	@echo ""
	@./emblem lambda.e
	@echo ""
	@echo ""

objects :
	@echo ""
	@cat objects.e
	@echo ""
	@echo ""

objectsx : emblem
	@echo ""
	@./emblem objects.e
	@echo ""
	@echo ""

run : emblem
	@echo ""
	@cat error1.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error1.e
	@echo ""
	@echo ""
	@echo ""
	@cat error2.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error2.e
	@echo ""
	@echo ""
	@echo ""
	@cat error3.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error3.e
	@echo ""
	@echo ""
	@echo ""
	@cat error4.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error4.e
	@echo ""
	@echo ""
	@echo ""
	@cat error5.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error5.e
	@echo ""
	@echo ""
	@echo ""
	@cat problem.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem problem.e integers
	@echo ""
	@echo ""
	@echo ""
	@cat arrays.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem arrays.e
	@echo ""
	@echo ""
	@echo ""
	@cat conditionals.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem conditionals.e
	@echo ""
	@echo ""
	@echo ""
	@cat recursion.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem recursion.e
	@echo ""
	@echo ""
	@echo ""
	@cat iteration.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem iteration.e
	@echo ""
	@echo ""
	@echo ""
	@cat functions.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem functions.e
	@echo ""
	@echo ""
	@echo ""
	@cat lambda.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem lambda.e
	@echo ""
	@echo ""
	@echo ""
	@cat objects.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem objects.e
	@echo ""
	@echo ""

test : emblem
	@echo ""
	@cat error1.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error1.e
	@echo ""
	@echo ""
	@echo ""
	@cat error2.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error2.e
	@echo ""
	@echo ""
	@echo ""
	@cat error3.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error3.e
	@echo ""
	@echo ""
	@echo ""
	@cat error4.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error4.e
	@echo ""
	@echo ""
	@echo ""
	@cat error5.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem error5.e
	@echo ""
	@echo ""
	@echo ""
	@cat problem.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem problem.e integers
	@echo ""
	@echo ""
	@echo ""
	@cat arrays.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem arrays.e
	@echo ""
	@echo ""
	@echo ""
	@cat conditionals.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem conditionals.e
	@echo ""
	@echo ""
	@echo ""
	@cat recursion.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem recursion.e
	@echo ""
	@echo ""
	@echo ""
	@cat iteration.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem iteration.e
	@echo ""
	@echo ""
	@echo ""
	@cat functions.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem functions.e
	@echo ""
	@echo ""
	@echo ""
	@cat lambda.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem lambda.e
	@echo ""
	@echo ""
	@echo ""
	@cat objects.e
	@echo ""
	@echo ""
	@echo ""
	@-./emblem objects.e
	@echo ""
	@echo ""