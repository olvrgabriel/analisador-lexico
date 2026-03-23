#!/bin/bash

echo "Verificando compilacao..."
if [ ! -f lexer ]; then
    echo "Compilando lexer..."
    gcc -Wall -Wextra -std=c99 lexer.c -o lexer
fi

echo -e "\n=== MODO EMBUTIDO ==="
./lexer

echo -e "\n=== TESTE 1 ==="
./lexer teste1.c

echo -e "\n=== TESTE 2 ==="
./lexer teste2.c

echo -e "\n=== RESUMO ==="
echo "O analisador lexico e capaz de reconhecer palavras reservadas, identificadores,"
echo "numeros (inteiros e float), strings, operadores compostos via lookahead e delimitadores."
echo "Tudo implementado conforme a teoria de automatos do Slide 8 e codigos dos Slides 9-11 da disciplina."