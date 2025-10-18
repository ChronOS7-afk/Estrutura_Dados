#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um nó da árvore de pistas (BST)
typedef struct PistaNode {
    char* pista;
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// Estrutura para uma sala na mansão
typedef struct Sala {
    char* nome;
    char* pista;  // Pista encontrada nesta sala (NULL se não houver)
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* nome, const char* pista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    novaSala->nome = (char*)malloc(strlen(nome) + 1);
    strcpy(novaSala->nome, nome);
    
    if (pista != NULL) {
        novaSala->pista = (char*)malloc(strlen(pista) + 1);
        strcpy(novaSala->pista, pista);
    } else {
        novaSala->pista = NULL;
    }
    
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função para criar um novo nó de pista na BST
PistaNode* criarNoPista(const char* pista) {
    PistaNode* novoNo = (PistaNode*)malloc(sizeof(PistaNode));
    novoNo->pista = (char*)malloc(strlen(pista) + 1);
    strcpy(novoNo->pista, pista);
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir uma pista na BST (ordem alfabética)
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    // Se a árvore está vazia, cria um novo nó
    if (raiz == NULL) {
        return criarNoPista(pista);
    }
    
    // Compara as pistas para decidir a posição na BST
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao < 0) {
        // Pista menor, insere na subárvore esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        // Pista maior, insere na subárvore direita
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    // Se a pista for igual, não insere duplicata
    
    return raiz;
}

// Função para exibir todas as pistas em ordem alfabética
void exibirPistasEmOrdem(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistasEmOrdem(raiz->direita);
    }
}

// Função para liberar a memória da árvore de pistas
void liberarArvorePistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarArvorePistas(raiz->esquerda);
        liberarArvorePistas(raiz->direita);
        free(raiz->pista);
        free(raiz);
    }
}

// Função para explorar salas e coletar pistas
void explorarSalasComPistas(Sala* inicio) {
    Sala* atual = inicio;
    char escolha;
    PistaNode* arvorePistas = NULL;  // BST para armazenar pistas coletadas
    
    printf("=== DETECTIVE QUEST - EM BUSCA DA VERDADE ===\n\n");
    
    while (1) {
        // Exibe informações da sala atual
        printf("📍 Você está na: %s\n", atual->nome);
        
        // Verifica se há pista na sala e coleta
        if (atual->pista != NULL) {
            printf("🔍 Pista encontrada: \"%s\"\n", atual->pista);
            arvorePistas = inserirPista(arvorePistas, atual->pista);
            printf("✅ Pista adicionada ao seu caderno!\n");
        } else {
            printf("🔎 Nenhuma pista encontrada neste cômodo.\n");
        }
        
        // Verifica opções de navegação
        int temEsquerda = (atual->esquerda != NULL);
        int temDireita = (atual->direita != NULL);
        
        if (!temEsquerda && !temDireita) {
            printf("\n🚫 Este é um cômodo sem saída.\n");
            printf("Deseja continuar explorando? (s - Sim, n - Não): ");
            scanf(" %c", &escolha);
            if (escolha == 'n' || escolha == 'N') {
                break;
            }
        } else {
            printf("\n🛣️  Caminhos disponíveis:\n");
            if (temEsquerda) {
                printf("⬅️  e - Esquerda: %s\n", atual->esquerda->nome);
            }
            if (temDireita) {
                printf("➡️  d - Direita: %s\n", atual->direita->nome);
            }
            printf("🚪 s - Sair da exploração\n");
            
            printf("\n🎯 Sua escolha: ");
            scanf(" %c", &escolha);
            
            // Processa a escolha do usuário
            if ((escolha == 'e' || escolha == 'E') && temEsquerda) {
                atual = atual->esquerda;
            } else if ((escolha == 'd' || escolha == 'D') && temDireita) {
                atual = atual->direita;
            } else if (escolha == 's' || escolha == 'S') {
                break;
            } else {
                printf("\n❌ Opção inválida ou caminho bloqueado! Tente novamente.\n");
            }
        }
        printf("\n==================================================\n\n");
    }
    
    // Exibe relatório final das pistas coletadas
    printf("\n📊 RELATÓRIO FINAL - PISTAS COLETADAS\n");
    printf("========================================\n");
    
    if (arvorePistas == NULL) {
        printf("Nenhuma pista foi coletada durante a exploração.\n");
    } else {
        printf("Pistas organizadas em ordem alfabética:\n");
        exibirPistasEmOrdem(arvorePistas);
    }
    
    // Libera a memória da árvore de pistas
    liberarArvorePistas(arvorePistas);
}

// Função para liberar a memória do mapa da mansão
void liberarMapa(Sala* raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz->nome);
        if (raiz->pista != NULL) {
            free(raiz->pista);
        }
        free(raiz);
    }
}

// Função principal
int main() {
    printf("Inicializando Detective Quest...\n\n");
    
    // Cria o mapa da mansão com pistas
    Sala* hall = criarSala("Hall de Entrada", "Porta principal arrombada");
    Sala* salaEstar = criarSala("Sala de Estar", "Copo de vinho quebrado no chão");
    Sala* cozinha = criarSala("Cozinha", "Faca desaparecida do bloco");
    Sala* quarto = criarSala("Quarto Principal", "Carta misteriosa na mesa de cabeceira");
    Sala* jardim = criarSala("Jardim", "Pegadas de barro levando ao muro");
    Sala* biblioteca = criarSala("Biblioteca", "Livro raro sobre venenos aberto");
    Sala* escritorio = criarSala("Escritório", "Computador com e-mail não lido");
    Sala* porao = criarSala("Porão", "Manchas escuras no chão de cimento");
    
    // Conecta as salas conforme o layout da mansão
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    
    salaEstar->esquerda = quarto;
    salaEstar->direita = biblioteca;
    
    cozinha->esquerda = escritorio;
    cozinha->direita = jardim;
    
    quarto->direita = porao;
    // biblioteca, jardim, escritorio e porao são folhas (sem saídas)
    
    // Inicia a exploração
    explorarSalasComPistas(hall);
    
    // Libera a memória do mapa
    liberarMapa(hall);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}