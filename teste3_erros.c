/* ============================================================
   TESTE 3: Casos com erros léxicos
   ============================================================ */
int main() {
    // Testes válidos
    int x = 42;
    float y = 3.14;

    // ERRO 1: Caractere inválido $
    int $valor = 10;

    // ERRO 2: String não fechada
    char msg[] = "texto incompleto;

    // ERRO 3: Operador ! sozinho (sem =)
    if (x ! 0) { }

    /* Este comentário está ok */
    return 0;
}
