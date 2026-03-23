#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Enum de Tokens (Incluindo Melhoria A: TOK_LBRACKET, TOK_RBRACKET) */
typedef enum {
    TOK_ID, TOK_NUM_INT, TOK_NUM_FLOAT, TOK_STRING, TOK_IF, TOK_ELSE, TOK_WHILE,
    TOK_INT, TOK_FLOAT, TOK_RETURN, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_EQ, TOK_ASSIGN, TOK_NEQ, TOK_LT, TOK_LE, TOK_GT, TOK_GE, TOK_SEMICOL,
    TOK_COMMA, TOK_LPAREN, TOK_RPAREN, TOK_LBRACE, TOK_RBRACE,
    TOK_LBRACKET, TOK_RBRACKET, /* Melhoria A */
    TOK_EOF, TOK_ERROR
} TokenType;

const char* nomes_tokens[] = {
    "ID", "NUM_INT", "NUM_FLOAT", "STRING", "IF", "ELSE", "WHILE",
    "INT", "FLOAT", "RETURN", "PLUS", "MINUS", "STAR", "SLASH",
    "EQ", "ASSIGN", "NEQ", "LT", "LE", "GT", "GE", "SEMICOL",
    "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
    "LBRACKET", "RBRACKET", /* Melhoria A */
    "EOF", "ERROR"
};

typedef struct {
    TokenType tipo;
    char lexema[256];
    int linha;
    int coluna;
} Token;

struct { const char* palavra; TokenType tipo; } reservadas[] = {
    {"if", TOK_IF}, {"else", TOK_ELSE}, {"while", TOK_WHILE},
    {"int", TOK_INT}, {"float", TOK_FLOAT}, {"return", TOK_RETURN},
    {NULL, TOK_ID}
};

const char* src;
int linha_atual = 1;
int coluna_atual = 1;

int fim_de_arquivo() { return *src == '\0'; }
char espiar() { return *src; }
char espiar_proximo() { return fim_de_arquivo() ? '\0' : *(src + 1); }

char avancar() {
    char c = *src++;
    if (c == '\n') {
        linha_atual++;
        coluna_atual = 1;
    } else {
        coluna_atual++;
    }
    return c;
}

void pular_brancos() {
    while (!fim_de_arquivo()) {
        char c = espiar();
        if (isspace(c)) {
            avancar();
        } else if (c == '/' && espiar_proximo() == '/') {
            // Comentário de linha
            while (!fim_de_arquivo() && espiar() != '\n') avancar();
        } else if (c == '/' && espiar_proximo() == '*') {
            // Comentário de bloco
            avancar(); avancar(); // consome /*
            while (!fim_de_arquivo()) {
                if (espiar() == '*' && espiar_proximo() == '/') {
                    avancar(); avancar(); // consome */
                    break;
                }
                avancar();
            }
        } else {
            break;
        }
    }
}

Token criar_token(TokenType tipo, const char* lexema, int linha, int coluna) {
    Token tok;
    tok.tipo = tipo;
    strncpy(tok.lexema, lexema, 255);
    tok.lexema[255] = '\0';
    tok.linha = linha;
    tok.coluna = coluna;
    return tok;
}

TokenType checar_reservada(const char* lexema) {
    for (int i = 0; reservadas[i].palavra != NULL; i++) {
        if (strcmp(lexema, reservadas[i].palavra) == 0) return reservadas[i].tipo;
    }
    return TOK_ID;
}

Token proximo_token() {
    pular_brancos();
    if (fim_de_arquivo()) return criar_token(TOK_EOF, "EOF", linha_atual, coluna_atual);

    int linha_tok = linha_atual;
    int col_tok = coluna_atual;
    char c = avancar();
    char buf[256];
    int pos = 0;

    // Identificadores e Palavras Reservadas: [a-zA-Z_][a-zA-Z0-9_]*
    if (isalpha(c) || c == '_') {
        buf[pos++] = c;
        while (isalnum(espiar()) || espiar() == '_') {
            if (pos < 255) buf[pos++] = avancar();
            else avancar();
        }
        buf[pos] = '\0';
        return criar_token(checar_reservada(buf), buf, linha_tok, col_tok);
    }

    // Números Inteiros e Reais: [0-9]+ e [0-9]+\.[0-9]+
    if (isdigit(c)) {
        buf[pos++] = c;
        int is_float = 0;
        while (isdigit(espiar())) {
            if (pos < 255) buf[pos++] = avancar();
            else avancar();
        }
        if (espiar() == '.') {
            is_float = 1;
            if (pos < 255) buf[pos++] = avancar(); // consome '.'
            while (isdigit(espiar())) {
                if (pos < 255) buf[pos++] = avancar();
                else avancar();
            }
        }
        buf[pos] = '\0';
        return criar_token(is_float ? TOK_NUM_FLOAT : TOK_NUM_INT, buf, linha_tok, col_tok);
    }

    // Strings literais: "..."
    if (c == '"') {
        while (!fim_de_arquivo() && espiar() != '"' && espiar() != '\n') {
            if (pos < 255) buf[pos++] = avancar();
            else avancar();
        }
        if (espiar() == '"') {
            avancar(); // consome fechamento
            buf[pos] = '\0';
            return criar_token(TOK_STRING, buf, linha_tok, col_tok);
        } else {
            return criar_token(TOK_ERROR, "String nao fechada", linha_tok, col_tok);
        }
    }

    // Operadores com lookahead
    if (c == '=') {
        if (espiar() == '=') { avancar(); return criar_token(TOK_EQ, "==", linha_tok, col_tok); }
        return criar_token(TOK_ASSIGN, "=", linha_tok, col_tok);
    }
    if (c == '!') {
        if (espiar() == '=') { avancar(); return criar_token(TOK_NEQ, "!=", linha_tok, col_tok); }
        buf[0] = c; buf[1] = '\0'; return criar_token(TOK_ERROR, buf, linha_tok, col_tok); // ! sozinho
    }
    if (c == '<') {
        if (espiar() == '=') { avancar(); return criar_token(TOK_LE, "<=", linha_tok, col_tok); }
        return criar_token(TOK_LT, "<", linha_tok, col_tok);
    }
    if (c == '>') {
        if (espiar() == '=') { avancar(); return criar_token(TOK_GE, ">=", linha_tok, col_tok); }
        return criar_token(TOK_GT, ">", linha_tok, col_tok);
    }

    // Operadores simples
    if (c == '+') return criar_token(TOK_PLUS, "+", linha_tok, col_tok);
    if (c == '-') return criar_token(TOK_MINUS, "-", linha_tok, col_tok);
    if (c == '*') return criar_token(TOK_STAR, "*", linha_tok, col_tok);
    if (c == '/') return criar_token(TOK_SLASH, "/", linha_tok, col_tok);

    // Delimitadores
    if (c == ';') return criar_token(TOK_SEMICOL, ";", linha_tok, col_tok);
    if (c == ',') return criar_token(TOK_COMMA, ",", linha_tok, col_tok);
    if (c == '(') return criar_token(TOK_LPAREN, "(", linha_tok, col_tok);
    if (c == ')') return criar_token(TOK_RPAREN, ")", linha_tok, col_tok);
    if (c == '{') return criar_token(TOK_LBRACE, "{", linha_tok, col_tok);
    if (c == '}') return criar_token(TOK_RBRACE, "}", linha_tok, col_tok);
    
    // Melhoria Técnica A: Delimitadores [ e ]
    if (c == '[') return criar_token(TOK_LBRACKET, "[", linha_tok, col_tok);
    if (c == ']') return criar_token(TOK_RBRACKET, "]", linha_tok, col_tok);

    // Erro léxico
    buf[0] = c; buf[1] = '\0';
    return criar_token(TOK_ERROR, buf, linha_tok, col_tok);
}

void imprimir_token(Token tok) {
    printf("%-12s | %-20s | [%d, %d]\n", nomes_tokens[tok.tipo], tok.lexema, tok.linha, tok.coluna);
}

void ler_arquivo(const char* nome_arquivo, char** buffer) {
    FILE* f = fopen(nome_arquivo, "r");
    if (!f) { perror("Erro ao abrir arquivo"); exit(1); }
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    *buffer = malloc(length + 1);
    if (*buffer) fread(*buffer, 1, length, f);
    (*buffer)[length] = '\0';
    fclose(f);
}

int main(int argc, char** argv) {
    // MODIFICAÇÃO 1 — Assinatura obrigatória
    printf("Autor(a): Gabriel Andrade Dutra de Oliveira | Turma 41E7 | Repositorio: analisador-lexico\n\n");

    char* buffer = NULL;

    if (argc > 1) {
        ler_arquivo(argv[1], &buffer);
        src = buffer;
    } else {
        src = "int fatorial(int n) {\n"
              "    if (n <= 1) return 1;\n"
              "    else return n * fatorial(n - 1);\n"
              "}\n"
              "int main() {\n"
              "    float preco = 10.5;\n"
              "    char str[] = \"calculo\";\n"
              "    return fatorial(5);\n"
              "}\n";
    }

    printf("%-12s | %-20s | %s\n", "TIPO", "LEXEMA", "POSICAO");
    printf("-------------------------------------------------------\n");

    Token tok;
    do {
        tok = proximo_token();
        imprimir_token(tok);
    } while (tok.tipo != TOK_EOF);

    if (buffer) free(buffer);
    return 0;
}