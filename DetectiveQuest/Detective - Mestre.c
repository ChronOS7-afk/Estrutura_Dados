#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para um nó da árvore de pistas (BST)
typedef struct PistaNode {
    char* pista;
    struct PistaNode* esquerda;
    struct PistaNode* direita;
} PistaNode;

// Estrutura para um nó da tabela hash (pista -> suspeito)
typedef struct HashNode {
    char* pista;
    char* suspeito;
    struct HashNode* proximo;
} HashNode;

// Estrutura para uma sala na mansão
typedef struct Sala {
    char* nome;
    char* pista;
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Estrutura para a tabela hash
typedef struct {
    HashNode** elementos;
    int tamanho;
} TabelaHash;

// Função hash simples (soma dos caracteres módulo tamanho)
int funcaoHash(const char* chave, int tamanho) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        soma += chave[i];
    }
    return soma % tamanho;
}

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
    if (raiz == NULL) {
        return criarNoPista(pista);
    }
    
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    
    return raiz;
}

// Função para criar a tabela hash
TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    tabela->tamanho = tamanho;
    tabela->elementos = (HashNode**)calloc(tamanho, sizeof(HashNode*));
    return tabela;
}

// Função para inserir na tabela hash
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* suspeito) {
    int indice = funcaoHash(pista, tabela->tamanho);
    
    HashNode* novoNo = (HashNode*)malloc(sizeof(HashNode));
    novoNo->pista = (char*)malloc(strlen(pista) + 1);
    strcpy(novoNo->pista, pista);
    novoNo->suspeito = (char*)malloc(strlen(suspeito) + 1);
    strcpy(novoNo->suspeito, suspeito);
    novoNo->proximo = NULL;
    
    // Inserção no início da lista encadeada
    if (tabela->elementos[indice] == NULL) {
        tabela->elementos[indice] = novoNo;
    } else {
        novoNo->proximo = tabela->elementos[indice];
        tabela->elementos[indice] = novoNo;
    }
}

// Função para buscar um suspeito na tabela hash
char* encontrarSuspeito(TabelaHash* tabela, const char* pista) {
    int indice = funcaoHash(pista, tabela->tamanho);
    HashNode* atual = tabela->elementos[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    
    return NULL; // Pista não encontrada
}

// Função para exibir todas as pistas em ordem alfabética
void exibirPistasEmOrdem(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistasEmOrdem(raiz->esquerda);
        printf("- %s\n", raiz->pista);
        exibirPistasEmOrdem(raiz->direita);
    }
}

// Função para contar quantas pistas apontam para um suspeito
int contarPistasPorSuspeito(PistaNode* raizPistas, TabelaHash* tabelaHash, const char* suspeito) {
    if (raizPistas == NULL) {
        return 0;
    }
    
    int count = 0;
    
    // Conta na subárvore esquerda
    count += contarPistasPorSuspeito(raizPistas->esquerda, tabelaHash, suspeito);
    
    // Conta no nó atual
    char* suspeitoDaPista = encontrarSuspeito(tabelaHash, raizPistas->pista);
    if (suspeitoDaPista != NULL && strcmp(suspeitoDaPista, suspeito) == 0) {
        count++;
    }
    
    // Conta na subárvore direita
    count += contarPistasPorSuspeito(raizPistas->direita, tabelaHash, suspeito);
    
    return count;
}

// Função para verificar a acusação final
void verificarSuspeitoFinal(PistaNode* raizPistas, TabelaHash* tabelaHash) {
    char suspeito[50];
    
    printf("\n🎯 FASE DE ACUSAÇÃO FINAL\n");
    printf("==========================\n");
    printf("Lista de suspeitos:\n");
    printf("- João (o mordomo)\n");
    printf("- Maria (a cozinheira)\n");
    printf("- Pedro (o jardineiro)\n");
    printf("- Ana (a governanta)\n");
    printf("- Carlos (o motorista)\n\n");
    
    printf("Digite o nome do suspeito que você acusa: ");
    scanf(" %[^\n]", suspeito);
    
    int pistasCorrespondentes = contarPistasPorSuspeito(raizPistas, tabelaHash, suspeito);
    
    printf("\n🔍 ANALISANDO ACUSAÇÃO...\n");
    printf("Suspeito acusado: %s\n", suspeito);
    printf("Pistas que apontam para %s: %d\n", suspeito, pistasCorrespondentes);
    
    if (pistasCorrespondentes >= 2) {
        printf("\n✅ PARABÉNS! Você reuniu evidências suficientes!\n");
        printf("%s é o culpado! Caso resolvido!\n", suspeito);
    } else if (pistasCorrespondentes == 1) {
        printf("\n⚠️  CUIDADO! Apenas uma pista aponta para este suspeito.\n");
        printf("Não há evidências suficientes para condenação.\n");
    } else {
        printf("\n❌ INOCENTE! Nenhuma pista coletada aponta para este suspeito.\n");
        printf("Você acusou a pessoa errada!\n");
    }
}

// Função para explorar salas e coletar pistas
void explorarSalas(Sala* inicio, TabelaHash* tabelaHash) {
    Sala* atual = inicio;
    char escolha;
    PistaNode* arvorePistas = NULL;
    
    printf("=== DETECTIVE QUEST - EM BUSCA DO CULPADO ===\n\n");
    
    while (1) {
        printf("📍 Você está na: %s\n", atual->nome);
        
        if (atual->pista != NULL) {
            printf("🔍 Pista encontrada: \"%s\"\n", atual->pista);
            arvorePistas = inserirPista(arvorePistas, atual->pista);
            printf("✅ Pista adicionada ao seu caderno!\n");
        } else {
            printf("🔎 Nenhuma pista encontrada neste cômodo.\n");
        }
        
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
    
    // Exibe relatório das pistas coletadas
    printf("\n📊 RELATÓRIO DE PISTAS COLETADAS\n");
    printf("================================\n");
    
    if (arvorePistas == NULL) {
        printf("Nenhuma pista foi coletada durante a exploração.\n");
    } else {
        printf("Pistas organizadas em ordem alfabética:\n");
        exibirPistasEmOrdem(arvorePistas);
    }
    
    // Verificação final do suspeito
    verificarSuspeitoFinal(arvorePistas, tabelaHash);
}

// Função para liberar memória da BST de pistas
void liberarArvorePistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarArvorePistas(raiz->esquerda);
        liberarArvorePistas(raiz->direita);
        free(raiz->pista);
        free(raiz);
    }
}

// Função para liberar memória da tabela hash
void liberarTabelaHash(TabelaHash* tabela) {
    for (int i = 0; i < tabela->tamanho; i++) {
        HashNode* atual = tabela->elementos[i];
        while (atual != NULL) {
            HashNode* proximo = atual->proximo;
            free(atual->pista);
            free(atual->suspeito);
            free(atual);
            atual = proximo;
        }
    }
    free(tabela->elementos);
    free(tabela);
}

// Função para liberar memória do mapa da mansão
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

int main() {
    printf("Inicializando Detective Quest...\n\n");
    
    // Cria o mapa da mansão com pistas
    Sala* hall = criarSala("Hall de Entrada", "Porta principal arrombada");
    Sala* salaEstar = criarSala("Sala de Estar", "Copo de vinho quebrado no chão");
    Sala* cozinha = criarSala("Cozinha", "Faca desaparecida do bloco");
    Sala* quarto = criarSala("Quarto Principal", "Carta misteriosa na mesa de cabeceira");
    Sala* jardim = criarSala("Jardim", "Pegadas de barro levando ao muro");
    Sala* biblioteca = criarSala("Biblioteca", "Livro raro sobre venenos aberto");
    
    // Conecta as salas
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = quarto;
    cozinha->direita = jardim;
    quarto->direita = biblioteca;
    
    // Cria e preenche a tabela hash com associações pista->suspeito
    TabelaHash* tabelaHash = criarTabelaHash(TAMANHO_HASH);
    
    inserirNaHash(tabelaHash, "Porta principal arrombada", "Carlos");
    inserirNaHash(tabelaHash, "Copo de vinho quebrado no chão", "João");
    inserirNaHash(tabelaHash, "Faca desaparecida do bloco", "Maria");
    inserirNaHash(tabelaHash, "Carta misteriosa na mesa de cabeceira", "Ana");
    inserirNaHash(tabelaHash, "Pegadas de barro levando ao muro", "Pedro");
    inserirNaHash(tabelaHash, "Livro raro sobre venenos aberto", "João");
    
    // Inicia a exploração
    explorarSalas(hall, tabelaHash);
    
    // Libera a memória
    liberarMapa(hall);
    liberarTabelaHash(tabelaHash);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    return 0;
}