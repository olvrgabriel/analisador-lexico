**Nome completo:** Gabriel Andrade Dutra de Oliveira  
**Matrícula:** 72200782  
**Turma:** 41E7  

Ao construir este repositório, compreendi na prática o papel do **scanner** como a primeira fase do compilador. Foi possível observar a diferença entre **padrão** (a regra teórica, como `[0-9]+`), **lexema** (a string real consumida, ex: `42`) e **token** (a classificação final, `TOK_NUM_INT`). A implementação em C demonstrou a importância do **lookahead** (espiar o próximo caractere sem consumi-lo) para resolver ambiguidades, como entre `=` e `==`.
Essa experiência consolidou o elo entre a teoria dos autômatos finitos determinísticos e o código real que precede a fase do **parser** no front-end de um compilador.