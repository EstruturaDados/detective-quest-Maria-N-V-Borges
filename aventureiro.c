#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da sala
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
    char pista[50]; // pista encontrada na sala (opcional)
} Sala;

// Estrutura da árvore de busca (BST) para pistas
typedef struct NodoPista {
    char pista[50];
    struct NodoPista *esquerda;
    struct NodoPista *direita;
} NodoPista;

// Função para criar uma sala
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova != NULL) {
        snprintf(nova->nome, sizeof(nova->nome), "%s", nome);
        if (pista != NULL)
            snprintf(nova->pista, sizeof(nova->pista), "%s", pista);
        else
            nova->pista[0] = '\0'; // sem pista
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

// Função para criar um nodo de pista
NodoPista* criarNodoPista(const char* pista) {
    NodoPista* novo = (NodoPista*) malloc(sizeof(NodoPista));
    if (novo != NULL) {
        snprintf(novo->pista, sizeof(novo->pista), "%s", pista);
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// Inserir pista na BST
NodoPista* inserirPista(NodoPista* raiz, const char* pista) {
    if (raiz == NULL) {
        return criarNodoPista(pista);
    }
    if (strcmp(pista, raiz->pista) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (strcmp(pista, raiz->pista) > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    return raiz;
}

// Impressão em ordem alfabética
void emOrdem(NodoPista* raiz) {
    if (raiz != NULL)  {
        emOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        emOrdem(raiz->direita);
    }
}

// Função para explorar as salas
void explorarSalas(Sala* atual, NodoPista** arvorePistas) {
    char opcao;
    while (atual != NULL) {
        printf("\nVoce esta na sala: %s\n", atual->nome);

        // Se houver pista na sala, adiciona na BST
        if (strlen(atual->pista) > 0) {
            printf("Voce encontrou uma pista: %s\n", atual->pista);
            *arvorePistas = inserirPista(*arvorePistas, atual->pista);
        }

        printf("Escolha o caminho:\n");
        printf("e -> esquerda | d -> direita | p -> listar pistas | s -> sair\n ");
        scanf(" %c", &opcao);

        if (opcao == 'e') {
            if (atual->esquerda != NULL) {
                atual = atual->esquerda;
            } else {
                printf("Fim do caminho a esquerda.\n");
                break;
            }
        } else if (opcao == 'd') {
            if (atual->direita != NULL) {
                atual = atual->direita;
            } else {
                printf("Fim do caminho a direita.\n");
                break;
            }
        } else if (opcao == 'p') {
            printf("\n Pistas coletadas (em ordem alfabetica):\n");
            emOrdem(*arvorePistas);
        } else if (opcao == 's') {
            printf("Exploração encerrada.\n");
            break;
        } else {
            printf("Opcao invalida, teste novamente.\n");
        }
    }
}

int main() {
    // Construção estática da mansão
    Sala* hall = criarSala("Hall de Entrada", NULL);
    Sala* salaEstar = criarSala("Sala de Estar", "Chave dourada");
    Sala* biblioteca = criarSala("Biblioteca", "Livro antigo");
    Sala* cozinha = criarSala("Cozinha", "Receita misteriosa");
    Sala* jardim = criarSala("Jardim", NULL);

    // Estrutura da arvore binaria
    hall->esquerda = salaEstar;
    hall->direita = biblioteca;
    salaEstar->esquerda = cozinha;
    salaEstar->direita = jardim;

    // Árvore de pistas
    NodoPista* arvorePistas = NULL;

    // Inicio da exploração
    explorarSalas(hall, &arvorePistas);

    return 0;
}