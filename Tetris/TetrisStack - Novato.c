#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome;
    int id;
} Peca;

Peca fila[MAX];
int inicio = 0;
int fim = 0;
int tamanho = 0;
int proximo_id = 5;

void inicializarFila() {
    Peca pecas_iniciais[] = {
        {'T', 0},
        {'O', 1},
        {'L', 2},
        {'I', 3},
        {'I', 4}
    };
    for (int i = 0; i < MAX; i++) {
        fila[i] = pecas_iniciais[i];
    }
    inicio = 0;
    fim = 0;
    tamanho = 5;
}

Peca gerarPeca() {
    Peca nova_peca;
    nova_peca.id = proximo_id++;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;
    nova_peca.nome = tipos[indice];
    return nova_peca;
}

void enqueue(Peca peca) {
    if (tamanho == MAX) {
        printf("Fila cheia! Não é possível inserir mais peças.\n");
        return;
    }
    fila[fim] = peca;
    fim = (fim + 1) % MAX;
    tamanho++;
}

Peca dequeue() {
    if (tamanho == 0) {
        printf("Fila vazia! Não é possível remover peças.\n");
        Peca vazia = {' ', -1};
        return vazia;
    }
    Peca peca_removida = fila[inicio];
    inicio = (inicio + 1) % MAX;
    tamanho--;
    return peca_removida;
}

void exibirFila() {
    printf("Fila de Pecas: ");
    for (int i = 0; i < tamanho; i++) {
        int pos = (inicio + i) % MAX;
        printf("[%c %d] ", fila[pos].nome, fila[pos].id);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    inicializarFila();
    int opcao;
    do {
        exibirFila();
        printf("\n1 - Jogar Peca (dequeue)\n");
        printf("2 - Inserir Nova Peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca removida = dequeue();
                if (removida.id != -1) {
                    printf("Peca [%c %d] removida.\n", removida.nome, removida.id);
                }
                break;
            }
            case 2: {
                Peca nova = gerarPeca();
                enqueue(nova);
                printf("Nova peca [%c %d] inserida.\n", nova.nome, nova.id);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}