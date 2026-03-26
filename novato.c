#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore (sala)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criar uma sala
Sala* criarSala(const char* nome) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (nova != NULL) {
        snprintf(nova->nome, sizeof(nova->nome), "%s", nome);
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

// Função para explorar as salas
void explorarSalas(Sala* atual) {
    char opcao;
    while (atual != NULL) {
        printf("\nVoce esta na sala: %s\n", atual->nome);
        printf("Escolha o caminho:\n");
        printf("e -> esquerda | d -> direita | s -> sair\n ");
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
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardim = criarSala("Jardim");

    // Estrutura da arvore binaria
    hall->esquerda = salaEstar;
    hall->direita = biblioteca;
    salaEstar->esquerda = cozinha;
    salaEstar->direita = jardim;

    // Inicio da exploração
    explorarSalas(hall);

    return 0;
}