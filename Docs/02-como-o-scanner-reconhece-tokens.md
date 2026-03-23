# Como o Scanner Reconhece Tokens

1. **Identificadores e Palavras Reservadas**
   * **Passo a passo:** O scanner lê um caractere. Se for letra ou `_`, ele entra em um laço usando `espiar()` consumindo caracteres enquanto forem alfanuméricos ou `_`.
   * **Lookahead:** A função `espiar()` prevê se o próximo char pertence à palavra sem tirá-lo do buffer. Se não pertencer, o laço quebra. Após coletar, ele passa por `checar_reservada()`.
   * **Exemplo:** Lexema `while` -> Token `TOK_WHILE`. Lexema `valor1` -> Token `TOK_ID`.

2. **Operadores de dois caracteres (ex: `<=`, `==`)**
   * **Passo a passo:** Ao ler o caractere `<`, o scanner precisa saber se é um operador "menor que" ou "menor ou igual".
   * **Lookahead:** Ele usa o lookahead (espiar) para ver o próximo. Se o próximo for `=`, ele avança e consome, gerando `<=` . Caso contrário, gera apenas `<`.
   * **Exemplo:** Entrada `<=` produz token `TOK_LE`. Entrada `< ` produz `TOK_LT`.

3. **Strings Literais**
   * **Passo a passo:** Ao identificar o caractere `"`, o scanner consome caracteres até encontrar outro `"` (ou até o fim de arquivo/linha).
   * **Lookahead:** Não depende fortemente de lookahead, mas usa `espiar()` para validar se o caractere atual de fechamento é realmente `"`.
   * **Exemplo:** Entrada `"Olá"` produz token `TOK_STRING` e lexema `Olá`.