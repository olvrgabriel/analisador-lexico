# Como Testar e Interpretar a Saída

## Roteiro de terminal

Para compilar e executar os testes, siga os passos abaixo no terminal, a partir da raiz do projeto:

```bash
make
make test1
make test2
make test3
./lexer teste2.c
```

* `make` compila o programa `lexer` a partir de `lexer.c`.
* `make test1`, `make test2` e `make test3` compilam (se necessário) e executam o lexer sobre os respectivos arquivos de teste.
* `./lexer teste2.c` executa o lexer diretamente sobre o arquivo `teste2.c`.

## Como ler a saída

A saída do programa é uma tabela com três colunas:

```
TIPO         | LEXEMA               | POSICAO
-------------------------------------------------------
INT          | int                  | [1, 1]
ID           | soma                 | [1, 5]
LPAREN       | (                    | [1, 9]
```

* **TIPO:** A categoria (classe) do token reconhecido pelo scanner. Exemplos: `INT` (palavra reservada int), `ID` (identificador), `NUM_INT` (número inteiro), `STRING` (literal de texto), `ASSIGN` (operador =), `SEMICOL` (ponto e vírgula).
* **LEXEMA:** A sequência exata de caracteres do código-fonte que foi consumida para formar o token. Por exemplo, o lexema `soma` foi classificado como `ID`, e o lexema `int` foi classificado como `INT`.
* **POSICAO:** Um par `[linha, coluna]` indicando onde o lexema começa no arquivo-fonte. A contagem de linhas e colunas inicia em 1. Essa informação é essencial para localizar erros no código original.

## O que significa um erro léxico

Quando o scanner encontra um caractere ou sequência que não corresponde a nenhum padrão válido (identificador, número, operador, delimitador, string ou comentário), ele gera um token do tipo `ERROR`.

Exemplos de erros léxicos:

* **Caractere inesperado:** Símbolos como `$`, `@` ou `#` não fazem parte da linguagem reconhecida. O scanner emite `ERROR` com o caractere como lexema.
* **String não fechada:** Uma string aberta com `"` que não possui o `"` de fechamento antes do fim da linha gera `ERROR` com o lexema `String nao fechada`.
* **Operador incompleto:** O caractere `!` sozinho (sem `=` na sequência) não é um operador válido, gerando `ERROR`.

Na saída, um erro aparece assim:

```
ERROR        | $                    | [10, 5]
ERROR        | String nao fechada   | [13, 18]
ERROR        | !                    | [16, 10]
```

Isso permite ao programador identificar **exatamente** onde está o problema no código-fonte, usando a linha e coluna reportadas.
