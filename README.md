# ANALISADOR LÉXICO EM C

## Descrição do projeto
Este projeto implementa um analisador léxico (scanner) didático em linguagem C, desenvolvido para a disciplina de Compiladores. O objetivo principal é transformar um arquivo de código-fonte (ou string embutida) em um fluxo contínuo de tokens válidos.

## Tokens reconhecidos
* **Identificadores e Palavras-chave:** if, else, while, int, float, return.
* **Literais:** Números inteiros, números de ponto flutuante e strings.
* **Operadores:** +, -, *, /, =, ==, !=, <, <=, >, >=.
* **Delimitadores e Sinais:** ;, ,, (, ), {, }, [, ].
* **Comentários:** Ignorados pelo scanner (tanto `//` quanto `/* */`).

## Instruções de compilação
Para compilar manualmente, utilize:
`gcc -Wall -Wextra -std=c99 lexer.c -o lexer`
(Ou utilize apenas o comando `make` caso possua o Makefile incluso).

## Execução
* **Modo 1 (código embutido):** Executar apenas `./lexer` sem parâmetros.
* **Modo 2 (arquivo externo):** Executar `./lexer nome_do_arquivo.c`.

## Testes fornecidos
* `teste1.c`: Funções matemáticas básicas.
* `teste2.c`: Strings, laços de repetição, arrays e comentários.
* `teste3_erros.c`: Casos com erros léxicos propositais.

## Como criar seus próprios testes
Basta criar um arquivo de texto/c com código (válido ou não), salvá-lo e passá-lo como parâmetro para o programa via terminal.

## Como entender a saída
A saída é feita em formato de tabela (TIPO | LEXEMA | POSIÇÃO). A posição descreve exatamente a linha e a coluna onde o lexema começou, essencial para debug.

## Detecção de erros
Tokens não reconhecidos geram o tipo `ERROR`. Isso inclui strings não fechadas ou símbolos desconhecidos, como `@` ou `$`.

## Estrutura do código e fluxo de execução
A função `proximo_token()` é o coração do programa e implementa o AFD usando simulação imperativa (condicionais e laços). A leitura dos caracteres utiliza funções de lookahead (`espiar()`) para resolver colisões, como entre `=` e `==`.

## Correspondência com os Slides
* **Slide 8:** Implementação do Autômato Finito Determinístico (AFD).
* **Slides 9-11:** Código comentado e controle de estados e transições.

## Exercícios sugeridos
* Adicionar suporte para o operador módulo (`%`).
* Adicionar suporte para números hexadecimais (`0x...`).
* Implementar o loop `for`.

## Referências bibliográficas
* Aho, Lam, Sethi, Ullman (Compiladores: Princípios, Técnicas e Ferramentas).
* Appel (Modern Compiler Implementation in C).
* Cooper & Torczon (Engineering a Compiler).

## Limitações conhecidas
Não trata macros de pré-processador (`#include`, `#define`), avaliando-os como erro léxico se encontrados.

## Solução de problemas
* Se não compilar, verifique se seu GCC suporta C99 (`-std=c99`).
* Erro de permissão em `demo.sh`: Execute `chmod +x demo.sh`.

---

## Alterações do aluno
* **Assinatura:** Adição da impressão `Autor(a): Gabriel Andrade Dutra de Oliveira | Turma 41E7 | Repositorio: analisador-lexico` logo na primeira linha de execução do `main`.
* **Melhoria Técnica:** Foi implementada a **Opção A**. O lexer agora reconhece os delimitadores de colchete `[` e `]`, categorizando-os nos tokens `TOK_LBRACKET` e `TOK_RBRACKET` respectivamente, graças às alterações no enum, lista de nomes de tokens, e aos condicionais incluídos na função `proximo_token()`.

## Teste autoral
Para rodar: `./lexer teste_autoral_Andrade_Oliveira.c`

**Saída obtida:**
```text
Autor(a): Gabriel Andrade Dutra de Oliveira | Turma 41E7 | Repositorio: analisador-lexico

TIPO         | LEXEMA               | POSICAO
-------------------------------------------------------
INT          | int                  | [6, 1]
ID           | main                 | [6, 5]
LPAREN       | (                    | [6, 9]
RPAREN       | )                    | [6, 10]
LBRACE       | {                    | [6, 12]
INT          | int                  | [8, 5]
ID           | meus_dados           | [8, 9]
LBRACKET     | [                    | [8, 19]
NUM_INT      | 5                    | [8, 20]
RBRACKET     | ]                    | [8, 21]
SEMICOL      | ;                    | [8, 22]
ID           | char                 | [9, 5]
ID           | disciplina           | [9, 10]
LBRACKET     | [                    | [9, 20]
RBRACKET     | ]                    | [9, 21]
ASSIGN       | =                    | [9, 23]
STRING       | Compiladores         | [9, 26]
SEMICOL      | ;                    | [9, 40]
IF           | if                   | [12, 5]
LPAREN       | (                    | [12, 8]
ID           | meus_dados           | [12, 9]
LBRACKET     | [                    | [12, 19]
NUM_INT      | 0                    | [12, 20]
RBRACKET     | ]                    | [12, 21]
GE           | >=                   | [12, 23]
NUM_INT      | 10                   | [12, 26]
EQ           | ==                   | [12, 29]
NUM_INT      | 1                    | [12, 32]
RPAREN       | )                    | [12, 33]
LBRACE       | {                    | [12, 35]
RETURN       | return               | [13, 9]
NUM_INT      | 1                    | [13, 16]
SEMICOL      | ;                    | [13, 17]
RBRACE       | }                    | [14, 5]
NEQ          | !=                   | [14, 7]
RETURN       | return               | [16, 5]
NUM_INT      | 0                    | [16, 12]
SEMICOL      | ;                    | [16, 13]
RBRACE       | }                    | [17, 1]
EOF          | EOF                  | [18, 1]
```
