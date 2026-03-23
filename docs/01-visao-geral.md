# Visão Geral do Scanner

No front-end de um compilador, o **scanner** (ou analisador léxico) é o primeiro passo. Seu papel é ler o código-fonte caractere por caractere e agrupá-los em unidades lógicas com significado, rejeitando espaços em branco e comentários.

Segundo o Slide 3 da disciplina, precisamos diferenciar três conceitos:
* **Token:** O símbolo terminal (a "categoria") devolvido ao parser (ex: `TOK_ID`, `TOK_NUM_INT`).
* **Lexema:** A sequência exata de caracteres lida do código-fonte (ex: `contador`, `42`).
* **Padrão:** A regra que descreve quais lexemas pertencem a qual token (ex: letras seguidas de letras ou números).

**Exemplo curto:**
Linha em C: `int x = 10;`
Tokens esperados: 
1. `TOK_INT` (lexema: "int")
2. `TOK_ID` (lexema: "x")
3. `TOK_ASSIGN` (lexema: "=")
4. `TOK_NUM_INT` (lexema: "10")
5. `TOK_SEMICOL` (lexema: ";")