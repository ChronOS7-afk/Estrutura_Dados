#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILA_TAM 5
#define PILHA_TAM 3

typedef struct {
    char nome;
    int id;
} Peca;

Peca fila[FILA_TAM];
Peca pilha[PILHA_TAM];
int inicio_fila = 0;
int fim_fila = 0;
int tamanho_fila = 0;
int topo_pilha = -1;
int proximo_id = 5;

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
void trocarPecaFilaPilha();
void trocarBloco3Pecas();

int main() {
    srand(time(NULL));
    inicializarSistema();
    
    int opcao;
    
    do {
        exibirEstado();
        printf("\n=== OPCOES ===\n");
        printf("1 - Jogar peca da frente da fila\n");
        printf("2 - Enviar peca da fila para reserva (pilha)\n");
        printf("3 - Usar peca da reserva (pilha)\n");
        printf("4 - Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
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
            case 4:
                trocarPecaFilaPilha();
                break;
            case 5:
                trocarBloco3Pecas();
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

void inicializarSistema() {
    Peca pecas_iniciais[] = {
        {'I', 0},
        {'L', 1},
        {'T', 2},
        {'O', 3},
        {'I', 4}
    };
    
    for (int i = 0; i < FILA_TAM; i++) {
        enfileirar(pecas_iniciais[i]);
    }
    
    topo_pilha = -1;
}

Peca gerarPeca() {
    Peca nova_peca;
    nova_peca.id = proximo_id++;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;
    nova_peca.nome = tipos[indice];
    return nova_peca;
}

void enfileirar(Peca peca) {
    if (tamanho_fila == FILA_TAM) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    fila[fim_fila] = peca;
    fim_fila = (fim_fila + 1) % FILA_TAM;
    tamanho_fila++;
}

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

void empilhar(Peca peca) {
    if (topo_pilha == PILHA_TAM - 1) {
        printf("Erro: Pilha de reserva cheia!\n");
        return;
    }
    topo_pilha++;
    pilha[topo_pilha] = peca;
}

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

void exibirEstado() {
    printf("\n=== Estado Atual ===\n");
    
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

void jogarPeca() {
    if (tamanho_fila == 0) {
        printf("Nao ha pecas na fila para jogar!\n");
        return;
    }
    
    Peca peca_jogada = desenfileirar();
    printf("Peca [%c %d] jogada!\n", peca_jogada.nome, peca_jogada.id);
    
    Peca nova_peca = gerarPeca();
    enfileirar(nova_peca);
    printf("Nova peca [%c %d] adicionada a fila.\n", nova_peca.nome, nova_peca.id);
}

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
    
    Peca nova_peca = gerarPeca();
    enfileirar(nova_peca);
    printf("Nova peca [%c %d] adicionada a fila.\n", nova_peca.nome, nova_peca.id);
}

void usarPecaReservada() {
    if (topo_pilha == -1) {
        printf("Nao ha pecas na reserva para usar!\n");
        return;
    }
    
    Peca peca_usada = desempilhar();
    printf("Peca reservada [%c %d] usada!\n", peca_usada.nome, peca_usada.id);
}

void trocarPecaFilaPilha() {
    if (tamanho_fila == 0) {
        printf("Nao ha pecas na fila para trocar!\n");
        return;
    }
    
    if (topo_pilha == -1) {
        printf("Nao ha pecas na reserva para trocar!\n");
        return;
    }
    
    Peca peca_fila = desenfileirar();
    Peca peca_pilha = desempilhar();
    
    enfileirar(peca_pilha);
    empilhar(peca_fila);
    
    printf("Troca realizada: [%c %d] da fila com [%c %d] da pilha.\n", 
           peca_fila.nome, peca_fila.id, peca_pilha.nome, peca_pilha.id);
}

void trocarBloco3Pecas() {
    if (tamanho_fila < 3) {
        printf("A fila precisa ter pelo menos 3 pecas para a troca em bloco!\n");
        return;
    }
    
    if (topo_pilha < 2) {
        printf("A pilha precisa ter 3 pecas para a troca em bloco!\n");
        return;
    }
    
    Peca temp_fila[3];
    Peca temp_pilha[3];
    
    for (int i = 0; i < 3; i++) {
        temp_fila[i] = desenfileirar();
    }
    
    for (int i = 0; i < 3; i++) {
        temp_pilha[i] = desempilhar();
    }
    
    for (int i = 2; i >= 0; i--) {
        enfileirar(temp_pilha[i]);
    }
    
    for (int i = 2; i >= 0; i--) {
        empilhar(temp_fila[i]);
    }
    
    printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
}