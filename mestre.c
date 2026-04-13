#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

// Estrutura para armazenar pares pistas -> suspeito
typedef struct NodoHash {
    char pista[50];
    char suspeito[50];
    struct NodoHash* proximo;
} NodoHash;

// Função de espalhamento simples (baseada na soma ASCII)
int funcaoHash(const char* chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % TAM_HASH;
}

// Inserir pista -> suspeito na tabela hash
void inserirNaHash(NodoHash* tabela[], const char* pista, const char* suspeito) {
    int indice = funcaoHash(pista);
    NodoHash* novo = (NodoHash*) malloc(sizeof(NodoHash));
    snprintf(novo->pista, sizeof(novo->pista), "%s", pista);
    snprintf(novo->suspeito, sizeof(novo->suspeito), "%s", suspeito);
    novo->proximo = tabela[indice];
    tabela[indice] = novo;
}

// Mostrar todas as associações pistas -> suspeito
void mostrarAssociacoes(NodoHash* tabela[]) {
    printf("\n Relacoes pista -> suspeito:\n");
    for (int i = 0; i < TAM_HASH; i++) {
        NodoHash* atual = tabela[i];
        while (atual != NULL) {
            printf("- %s -> %s\n", atual->pista, atual->suspeito);
            atual = atual->proximo;
        }
        
    }
    
}

// Contar quantas vezes cada suspeito aparece
void suspeitoMaisCitado(NodoHash* tabela[]) {
    char suspeitos[50][50];
    int contagem[50] = {0};
    int total = 0;

    for (int i = 0; i < TAM_HASH; i++) {
        NodoHash* atual = tabela[i];
        while (atual != NULL) {
            int encontrado = 0;
            for (int j = 0; j < total; j++) {
                if (strcmp(suspeitos[j], atual->suspeito) == 0) {
                    contagem[j]++;
                    encontrado = 1;
                    break;
                }
                
            }
            if (!encontrado) {
                snprintf(suspeitos[total], sizeof(suspeitos[total]), "%s", atual->suspeito);
                contagem[total] = 1;
                total++;
            }
            atual = atual->proximo;
             
        }
        
    }

    // Encontrar o suspeito mais citado
    int max = 0;
    int indiceMax = 0;
    for (int i = 0; i < total; i++) {
        if (contagem[i] > max) {
        max = contagem[i];
        indiceMax = i;
        }
    }

    printf("\n Suspeito mais citado: %s (%d pistas)\n", suspeitos[indiceMax], max);
    
}

int main() {
    NodoHash* tabela[TAM_HASH] = {NULL};

    // Inserções automáticas (exemplo)
    inserirNaHash(tabela, "Chave dourada", "Sr. Black");
    inserirNaHash(tabela, "Livro antigo", "Srta. White");
    inserirNaHash(tabela, "Receita misteriosa", "Srta. Green");
    inserirNaHash(tabela, "Chave dourada", "Sr. Black"); // repetição para contagem

    mostrarAssociacoes(tabela);
    suspeitoMaisCitado(tabela);

    return 0;
}

