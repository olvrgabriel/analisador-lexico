CC = gcc
CFLAGS = -Wall -Wextra -std=c99

lexer: lexer.c
	$(CC) $(CFLAGS) lexer.c -o lexer

test1: lexer
	./lexer teste1.c

test2: lexer
	./lexer teste2.c

test3: lexer
	./lexer teste3_erros.c

test-autoral: lexer
	./lexer teste_autoral_Andrade_Oliveira.c

test-all: lexer test1 test2 test3 test-autoral

demo: lexer
	bash demo.sh

clean:
	rm -f lexer *.o *.exe