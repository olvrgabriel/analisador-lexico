/* ============================================================
   TESTE 3: Casos com erros léxicos
   ============================================================ */
int main() {
    // Testes válidos
    int x = 42;
    float y = 3.14;
    // ERROS LÉXICOS (descomente para testar):
    // 1. Caractere inválido $
    // int $valor = 10;
    // 2. String não fechada
    // char msg[] = "texto incompleto;
    // 3. Operador ! sozinho (sem =)
    // if (x ! 0) { }
    // 4. Comentário de bloco não fechado
    /* Este comentário está ok */
    return 0;
}