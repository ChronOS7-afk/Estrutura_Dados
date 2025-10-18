#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura Sala
typedef struct Sala {
    char* nome;
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    novaSala->nome = (char*)malloc(strlen(nome) + 1);
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função para explorar as salas a partir de uma sala inicial
void explorarSalas(Sala* inicio) {
    Sala* atual = inicio;
    char escolha;

    while (1) {
        printf("Você está na: %s\n", atual->nome);

        // Verifica se é uma sala sem saída
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Chegou a um cômodo sem saídas. Fim da exploração.\n");
            break;
        }

        // Exibe opções de navegação
        printf("Para onde deseja ir?\n");
        if (atual->esquerda != NULL) {
            printf("e - Esquerda: %s\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("d - Direita: %s\n", atual->direita->nome);
        }
        printf("s - Sair\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);

        // Processa a escolha do usuário
        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida ou caminho bloqueado! Tente novamente.\n");
        }
        printf("\n");
    }
}

// Função principal para montar o mapa e iniciar a exploração
int main() {
    // Monta a árvore binária representando o mapa da mansão
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* quarto = criarSala("Quarto");
    Sala* jardim = criarSala("Jardim");
    Sala* biblioteca = criarSala("Biblioteca");

    // Conecta as salas conforme o layout desejado
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = quarto;
    cozinha->direita = jardim;
    quarto->direita = biblioteca;

    // Inicia a exploração a partir do Hall de Entrada
    explorarSalas(hall);

    // Libera a memória alocada (simplificado, sem função recursiva para liberar toda a árvore)
    free(hall->nome);
    free(hall);
    free(salaEstar->nome);
    free(salaEstar);
    free(cozinha->nome);
    free(cozinha);
    free(quarto->nome);
    free(quarto);
    free(jardim->nome);
    free(jardim);
    free(biblioteca->nome);
    free(biblioteca);

    return 0;
}