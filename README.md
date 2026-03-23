# ANALISADOR LÉXICO EM C

Este projeto implementa um analisador léxico (scanner) didático em linguagem C, desenvolvido para a disciplina de Compiladores. O objetivo principal é transformar um arquivo de código-fonte (ou string embutida) em um fluxo contínuo de tokens válidos.

---

## Descrição do Projeto
O scanner funciona como a primeira etapa de um compilador, realizando a leitura caractere por caractere e agrupando-os em unidades sintáticas chamadas Tokens, utilizando um Autômato Finito Determinístico (AFD).

## Tokens Reconhecidos
* Identificadores e Palavras-chave: if, else, while, int, float, return.
* Literais: Números inteiros, números de ponto flutuante e strings.
* Operadores: +, -, *, /, =, ==, !=, <, <=, >, >=.
* Delimitadores e Sinais: ;, ,, (, ), {, }, [, ].
* Comentários: Ignorados pelo scanner (tanto // quanto /* */).

---

## Instruções de Compilação
Para compilar manualmente, utilize:
gcc -Wall -Wextra -std=c99 lexer.c -o lexer

(Ou utilize apenas o comando make caso possua o Makefile incluso).

## Execução
* Modo 1 (código embutido): Executar apenas ./lexer sem parâmetros.
* Modo 2 (arquivo externo): Executar ./lexer nome_do_arquivo.c.

---

## Estrutura e Testes

### Testes Fornecidos
* teste1.c: Funções matemáticas básicas.
* teste2.c: Strings, laços de repetição, arrays e comentários.
* teste3_erros.c: Casos com erros léxicos propositais.

### Como entender a saída
A saída é gerada em formato de tabela para facilitar o debug:
* TIPO: Categoria do token reconhecido.
* LEXEMA: O texto original encontrado no código.
* POSICAO: Linha e coluna onde o lexema inicia.

---

## Implementação Técnica
* Coração do Projeto: A função proximo_token() implementa o AFD usando simulação imperativa (condicionais e laços).
* Lookahead: Uso de funções como espiar() para resolver ambiguidades (ex: distinguir = de ==) sem consumir o caractere precocemente.



Nota: O scanner não trata macros de pré-processador (#include, #define), avaliando-os como erro léxico se encontrados.

---

## Alteracoes do Aluno

* Assinatura: Adição da impressão identificadora logo na primeira linha de execução do main: 
  Autor(a): Gabriel Andrade Dutra de Oliveira | Turma 41E7 | Repositorio: analisador-lexico
* Melhoria Técnica (Opcao A): Implementação do suporte aos delimitadores de colchete [ e ]. Foram adicionados os tokens TOK_LBRACKET e TOK_RBRACKET, com as devidas alterações no enum, array de nomes de tokens e lógica do AFD na função proximo_token().

### Teste Autoral
Para rodar: ./lexer teste_autoral_Andrade_Oliveira.c

Saída obtida (Exemplo):
Autor(a): Gabriel Andrade Dutra de Oliveira | Turma 41E7 | Repositorio: analisador-lexico

| TIPO | LEXEMA | POSIÇÃO |
| :--- | :--- | :--- |
| **INT** | `int` | `[6, 1]` |
| **ID** | `main` | `[6, 5]` |
| **LPAREN** | `(` | `[6, 9]` |
| **RPAREN** | `)` | `[6, 10]` |
| **LBRACE** | `{` | `[6, 12]` |
| **INT** | `int` | `[8, 5]` |
| **ID** | `meus_dados` | `[8, 9]` |
| **LBRACKET** | `[` | `[8, 19]` |
| **NUM_INT** | `5` | `[8, 20]` |
| **RBRACKET** | `]` | `[8, 21]` |
| **SEMICOL** | `;` | `[8, 22]` |
...

---
