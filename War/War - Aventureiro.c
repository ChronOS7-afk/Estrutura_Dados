#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para cadastrar os territórios
void cadastrarTerritorios(struct Territorio *mapa, int num_territorios) {
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n\n", num_territorios);

    for (int i = 0; i < num_territorios; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        scanf("%29s", mapa[i].nome);

        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%9s", mapa[i].cor);

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// Função para exibir o mapa atual
void exibirMapa(struct Territorio *mapa, int num_territorios) {
    printf("# MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("---\n");

    for (int i = 0; i < num_territorios; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    printf("---\n\n");
}

// Função para simular um ataque entre territórios
void atacar(struct Territorio *atacante, struct Territorio *defensor) {
    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, dado_atacante);
    printf("O defensor %s rolou um dado e tirou: %d\n", defensor->nome, dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("VITORIA DO ATAQUE! ");

        if (defensor->tropas <= 1) {
            printf("O territorio %s foi conquistado!\n", defensor->nome);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = (atacante->tropas + 1) / 2;
            atacante->tropas -= defensor->tropas;
        } else {
            defensor->tropas--;
            printf("O defensor perdeu 1 tropa.\n");
        }
    } else {
        printf("DERROTA DO ATAQUE! ");
        atacante->tropas--;
        printf("O atacante perdeu 1 tropa.\n");
    }
    printf("-----------------------------\n");
}

int main() {
    srand(time(NULL));

    const int num_territorios = 5;
    struct Territorio *mapa = (struct Territorio*)calloc(num_territorios, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, num_territorios);

    // Loop principal do jogo
    int continuar = 1;
    while (continuar) {
        exibirMapa(mapa, num_territorios);

        printf("--- FASE DE ATAQUE ---\n");

        int idx_atacante, idx_defensor;

        printf("Escolha o territorio atacante (1 a %d, ou 0 para sair): ", num_territorios);
        scanf("%d", &idx_atacante);

        if (idx_atacante == 0) {
            continuar = 0;
            break;
        }

        printf("Escolha o territorio defensor (1 a %d): ", num_territorios);
        scanf("%d", &idx_defensor);

        if (idx_atacante < 1 || idx_atacante > num_territorios ||
            idx_defensor < 1 || idx_defensor > num_territorios) {
            printf("Escolha invalida! Tente novamente.\n\n");
            continue;
        }

        if (idx_atacante == idx_defensor) {
            printf("Nao pode atacar o proprio territorio! Tente novamente.\n\n");
            continue;
        }

        struct Territorio *atacante = &mapa[idx_atacante - 1];
        struct Territorio *defensor = &mapa[idx_defensor - 1];

        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Nao pode atacar territorio do mesmo exercito! Tente novamente.\n\n");
            continue;
        }

        atacar(atacante, defensor);

        printf("\nPressione Enter para continuar para o proximo turno...");
        getchar(); // limpa buffer
        getchar(); // espera Enter
        printf("\n");
    }

    printf("\n=== MAPA FINAL ===\n");
    exibirMapa(mapa, num_territorios);

    free(mapa);
    printf("Jogo encerrado. Ate a proxima!\n");

    return 0;
}