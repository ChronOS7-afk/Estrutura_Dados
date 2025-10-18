#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILA_TAM 5
#define PILHA_TAM 3

// Estrutura para representar uma peça do jogo
typedef struct {
    char nome;
    int id;
} Peca;

// Variáveis globais para a fila e pilha
Peca fila[FILA_TAM];
Peca pilha[PILHA_TAM];
int inicio_fila = 0;
int fim_fila = 0;
int tamanho_fila = 0;
int topo_pilha = -1;
int proximo_id = 5;

// Protótipos das funções
void inicializarSistema();
Peca gerarPeca();
void enfileirar(Peca peca);
Peca desenfileirar();
void empilhar(Peca peca);
Peca desempilhar();
void exibirEstado();
void jogarPeca();
void reservarPeca();
void usarPecaReservada();

int main() {
    srand(time(NULL));
    inicializarSistema();
    
    int opcao;
    
    do {
        exibirEstado();
        printf("\n1 - Jogar Peca\n");
        printf("2 - Reservar Peca\n");
        printf("3 - Usar Peca Reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                reservarPeca();
                break;
            case 3:
                usarPecaReservada();
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// Inicializa o sistema com peças iniciais
void inicializarSistema() {
    // Inicializa a fila com peças pré-definidas
    Peca pecas_iniciais[] = {
        {'T', 0},
        {'O', 1},
        {'L', 2},
        {'I', 3},
        {'I', 4}
    };
    
    for (int i = 0; i < FILA_TAM; i++) {
        enfileirar(pecas_iniciais[i]);
    }
    
    // A pilha começa vazia
    topo_pilha = -1;
}

// Gera uma nova peça com ID único e tipo aleatório
Peca gerarPeca() {
    Peca nova_peca;
    nova_peca.id = proximo_id++;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;
    nova_peca.nome = tipos[indice];
    return nova_peca;
}

// Adiciona uma peça ao final da fila
void enfileirar(Peca peca) {
    if (tamanho_fila == FILA_TAM) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    fila[fim_fila] = peca;
    fim_fila = (fim_fila + 1) % FILA_TAM;
    tamanho_fila++;
}

// Remove e retorna a peça do início da fila
Peca desenfileirar() {
    if (tamanho_fila == 0) {
        printf("Erro: Fila vazia!\n");
        Peca vazia = {' ', -1};
        return vazia;
    }
    Peca peca_removida = fila[inicio_fila];
    inicio_fila = (inicio_fila + 1) % FILA_TAM;
    tamanho_fila--;
    return peca_removida;
}

// Adiciona uma peça ao topo da pilha
void empilhar(Peca peca) {
    if (topo_pilha == PILHA_TAM - 1) {
        printf("Erro: Pilha de reserva cheia!\n");
        return;
    }
    topo_pilha++;
    pilha[topo_pilha] = peca;
}

// Remove e retorna a peça do topo da pilha
Peca desempilhar() {
    if (topo_pilha == -1) {
        printf("Erro: Pilha de reserva vazia!\n");
        Peca vazia = {' ', -1};
        return vazia;
    }
    Peca peca_removida = pilha[topo_pilha];
    topo_pilha--;
    return peca_removida;
}

// Exibe o estado atual da fila e pilha
void exibirEstado() {
    printf("\n=== ESTADO ATUAL ===\n");
    
    // Exibe a fila de peças
    printf("Fila de Pecas: ");
    if (tamanho_fila == 0) {
        printf("Vazia");
    } else {
        for (int i = 0; i < tamanho_fila; i++) {
            int pos = (inicio_fila + i) % FILA_TAM;
            printf("[%c %d] ", fila[pos].nome, fila[pos].id);
        }
    }
    printf("\n");
    
    // Exibe a pilha de reserva
    printf("Pilha de Reserva (Topo -> Base): ");
    if (topo_pilha == -1) {
        printf("Vazia");
    } else {
        for (int i = topo_pilha; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
    }
    printf("\n");
}

// Opção 1: Jogar a peça da frente da fila
void jogarPeca() {
    if (tamanho_fila == 0) {
        printf("Nao ha pecas na fila para jogar!\n");
        return;
    }
    
    Peca peca_jogada = desenfileirar();
    printf("Peca [%c %d] jogada!\n", peca_jogada.nome, peca_jogada.id);
    
    // Gera nova peça para manter a fila cheia
    Peca nova_peca = gerarPeca();
    enfileirar(nova_peca);
    printf("Nova peca [%c %d] adicionada a fila.\n", nova_peca.nome, nova_peca.id);
}

// Opção 2: Reservar a peça da frente da fila
void reservarPeca() {
    if (tamanho_fila == 0) {
        printf("Nao ha pecas na fila para reservar!\n");
        return;
    }
    
    if (topo_pilha == PILHA_TAM - 1) {
        printf("Pilha de reserva cheia! Nao e possivel reservar mais pecas.\n");
        return;
    }
    
    Peca peca_reservada = desenfileirar();
    empilhar(peca_reservada);
    printf("Peca [%c %d] movida para a reserva.\n", peca_reservada.nome, peca_reservada.id);
    
    // Gera nova peça para manter a fila cheia
    Peca nova_peca = gerarPeca();
    enfileirar(nova_peca);
    printf("Nova peca [%c %d] adicionada a fila.\n", nova_peca.nome, nova_peca.id);
}

// Opção 3: Usar peça da reserva
void usarPecaReservada() {
    if (topo_pilha == -1) {
        printf("Nao ha pecas na reserva para usar!\n");
        return;
    }
    
    Peca peca_usada = desempilhar();
    printf("Peca reservada [%c %d] usada!\n", peca_usada.nome, peca_usada.id);
}