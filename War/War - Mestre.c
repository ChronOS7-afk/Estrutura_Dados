#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de Território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ================= FUNÇÕES DE MISSÕES =================

// Sorteia uma missão e copia para o destino
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão do jogador (apenas no início)
void exibirMissao(const char* missao, int jogador) {    
}

// Verifica se a missão foi cumprida (lógica inicial simplificada)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "Conquistar 3 territorios")) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) count++;
        }
        if (count >= 3) return 1;
    }
    if (strstr(missao, "Eliminar exercito Vermelho")) {
        int existeVermelho = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0) {
                existeVermelho = 1;
                break;
            }
        }
        if (!existeVermelho) return 1;
    }
    if (strstr(missao, "Controlar todos os territorios")) {
        char corRef[10];
        strcpy(corRef, mapa[0].cor);
        int todos = 1;
        for (int i = 1; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corRef) != 0) {
                todos = 0;
                break;
            }
        }
        if (todos) return 1;
    }
    if (strstr(missao, "Manter pelo menos 10 tropas")) {
        int total = 0;
        for (int i = 0; i < tamanho; i++) {
            total += mapa[i].tropas;
        }
        if (total >= 10) return 1;
    }
    if (strstr(missao, "Conquistar 2 territorios seguidos")) {
        // Simplificação: se o jogador tiver pelo menos 2 territórios, considera cumprido
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) count++;
        }
        if (count >= 2) return 1;
    }
    return 0;
}

// ================= FUNÇÕES DO JOGO =================

// Cadastro dos territórios
void cadastrarTerritorios(Territorio* mapa, int num_territorios) {
    printf("Cadastro dos %d territorios iniciais:\n\n", num_territorios);
    for (int i = 0; i < num_territorios; i++) {
        printf("--- Territorio %d ---\n", i + 1);
        printf("Nome: ");
        scanf("%29s", mapa[i].nome);
        printf("Cor do Exercito: ");
        scanf("%9s", mapa[i].cor);
        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Exibe o mapa
void exibirMapa(Territorio* mapa, int num_territorios) {
    printf("\n=== MAPA DO MUNDO ===\n");
    for (int i = 0; i < num_territorios; i++) {
        printf("%d. %s (Exercito: %s, Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("=====================\n\n");
}

// Simula ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = rand() % 6 + 1;
    int dado_defensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atacante->nome, dado_atacante, defensor->nome, dado_defensor);

    if (dado_atacante > dado_defensor) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        defensor->tropas--;

        // Se o defensor ficar sem tropas, o território é conquistado
        if (defensor->tropas <= 0) {
            printf("O territorio %s foi conquistado pelo exercito %s!\n",
                   defensor->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor);
            defensor->tropas = 1;   // atacante ocupa com 1 tropa
            atacante->tropas--;     // atacante perde 1 tropa para ocupar
        }
    } else {
        printf("VITORIA DA DEFESA! o atacante perdeu 1 tropa.\n", atacante->nome);
        atacante->tropas--;
    }
    printf("---------------\n");
}

// Libera memória
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int num_jogadores) {
    free(mapa);
    for (int i = 0; i < num_jogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

// ================= MAIN =================
int main() {
    srand(time(NULL));

    const int num_territorios = 5;
    const int num_jogadores = 1; // pode expandir para 2+

    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios",
        "Eliminar exercito Vermelho",
        "Controlar todos os territorios",
        "Manter pelo menos 10 tropas",
        "Conquistar 2 territorios seguidos"
    };
    int totalMissoes = 5;

    // Alocação de territórios
    Territorio* mapa = (Territorio*)calloc(num_territorios, sizeof(Territorio));

    // Alocação dinâmica das missões dos jogadores
    char** missoesJogadores = (char**)malloc(num_jogadores * sizeof(char*));
    for (int i = 0; i < num_jogadores; i++) {
        missoesJogadores[i] = (char*)malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoes, totalMissoes);
        exibirMissao(missoesJogadores[i], i + 1);
    }

    // Cadastro inicial
    cadastrarTerritorios(mapa, num_territorios);

    // Loop do jogo
    int continuar = 1;
    while (continuar) {
        exibirMapa(mapa, num_territorios);

        // Exibe a missão do jogador antes do menu
        printf("--- SUA MISSAO (Jogador 1) ---\n");
        printf("%s\n\n", missoesJogadores[0]);

        printf("--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("3 - Sair\n");
        printf("----------------------\n");
        printf("Escolha sua acao: ");

        int escolha;
        scanf("%d", &escolha);

        if (escolha == 1) {
            int idx_atacante, idx_defensor;
            printf("Escolha o territorio atacante (1-%d): ", num_territorios);
            scanf("%d", &idx_atacante);
            printf("Escolha o territorio defensor (1-%d): ", num_territorios);
            scanf("%d", &idx_defensor);

            if (idx_atacante < 1 || idx_atacante > num_territorios ||
                idx_defensor < 1 || idx_defensor > num_territorios ||
                idx_atacante == idx_defensor) {
                printf("Escolha invalida!\n");
                continue;
            }

            Territorio* atacante = &mapa[idx_atacante - 1];
            Territorio* defensor = &mapa[idx_defensor - 1];

            if (strcmp(atacante->cor, defensor->cor) == 0) {
                printf("Nao pode atacar territorio do mesmo exercito!\n");
                continue;
            }

            atacar(atacante, defensor);

        } else if (escolha == 2) {
            if (verificarMissao(missoesJogadores[0], mapa, num_territorios)) {
                printf("\n*** VOCE CUMPRIU SUA MISSAO! PARABENS! ***\n");
                continuar = 0;
            } else {
                printf("\nVoce ainda nao cumpriu sua missao. Continue a lutar!\n");
            }
            printf("\nPressione Enter para continuar...");
            getchar(); getchar();

        } else if (escolha == 3) {
            continuar = 0;   // encerra o jogo
        } else {
            printf("Opcao invalida!\n");
        }
    }

    liberarMemoria(mapa, missoesJogadores, num_jogadores);
    printf("\nJogo encerrado.\n");
    return 0;
}
