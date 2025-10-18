#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Estrutura do Componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais
Componente mochila[20];
int totalComponentes = 0;
int ordenadoPorNome = 0; // 0 = não ordenado, 1 = ordenado
int comparacoes = 0;

// Protótipos das funções
void menu_principal();
void adicionar_componente();
void descartar_componente();
void listar_componentes();
void organizar_mochila();
void bubble_sort_nome(Componente arr[], int n);
void insertion_sort_tipo(Componente arr[], int n);
void selection_sort_prioridade(Componente arr[], int n);
void busca_binaria_componente();
int busca_binaria(Componente arr[], int n, char nome[]);
void ativar_torre_fuga();
void limpar_tela();
void pausar();
void converter_minusculo(char *str);
int validar_tipo(char *tipo);
void medir_tempo_ordenacao(void (*algoritmo)(Componente[], int), Componente arr[], int n, char *nomeAlgoritmo);

int main() {
    menu_principal();
    return 0;
}

void menu_principal() {
    int opcao;
    
    do {
        limpar_tela();
        printf("========================================\n");
        printf("  PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("========================================\n\n");
        
        printf("Itens na Mochila: %d/20\n", totalComponentes);
        printf("Status da Ordenacao por Nome: %s\n\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("6. ATIVAR TORRE DE FUGA (Sair)\n\n");
        
        printf("========================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: adicionar_componente(); break;
            case 2: descartar_componente(); break;
            case 3: listar_componentes(); break;
            case 4: organizar_mochila(); break;
            case 5: busca_binaria_componente(); break;
            case 6: ativar_torre_fuga(); break;
            default: 
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
    } while(opcao != 6);
}

void adicionar_componente() {
    if(totalComponentes >= 20) {
        printf("\n** Capacidade maxima atingida! Nao e possivel adicionar mais componentes. **\n");
        pausar();
        return;
    }

    Componente novoComp;
    
    printf("\n--- Adicionar Componente ---\n");
    printf("Nome do componente: ");
    fgets(novoComp.nome, 30, stdin);
    novoComp.nome[strcspn(novoComp.nome, "\n")] = '\0';

    // Validação do tipo
    int tipoValido = 0;
    char tipoInput[20];
    
    while(!tipoValido) {
        printf("Tipo do componente (controle/suporte/propulsao): ");
        fgets(tipoInput, 20, stdin);
        tipoInput[strcspn(tipoInput, "\n")] = '\0';
        converter_minusculo(tipoInput);
        
        if(validar_tipo(tipoInput)) {
            tipoValido = 1;
            strcpy(novoComp.tipo, tipoInput);
        } else {
            printf("** Tipo invalido! Use: controle, suporte ou propulsao **\n");
        }
    }

    // Validação da prioridade
    int prioridadeValida = 0;
    while(!prioridadeValida) {
        printf("Prioridade (1-10, onde 10 e mais importante): ");
        scanf("%d", &novoComp.prioridade);
        getchar();
        
        if(novoComp.prioridade >= 1 && novoComp.prioridade <= 10) {
            prioridadeValida = 1;
        } else {
            printf("** Prioridade invalida! Use valores entre 1 e 10. **\n");
        }
    }

    mochila[totalComponentes] = novoComp;
    totalComponentes++;
    ordenadoPorNome = 0; // Marca como não ordenado após adição
    
    printf("\n** Componente '%s' adicionado com sucesso! **\n", novoComp.nome);
    pausar();
}

void descartar_componente() {
    if(totalComponentes == 0) {
        printf("\n** Mochila vazia! Nao ha componentes para descartar. **\n");
        pausar();
        return;
    }

    char nomeRemover[30];
    printf("\n--- Descartar Componente ---\n");
    printf("Nome do componente a ser descartado: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for(int i = 0; i < totalComponentes; i++) {
        if(strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            // Desloca componentes posteriores
            for(int j = i; j < totalComponentes - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalComponentes--;
            ordenadoPorNome = 0; // Marca como não ordenado após remoção
            printf("\n** Componente '%s' descartado com sucesso! **\n", nomeRemover);
            break;
        }
    }

    if(!encontrado) {
        printf("\n** Componente '%s' nao encontrado na mochila. **\n", nomeRemover);
    }
    
    pausar();
}

void listar_componentes() {
    printf("\n--- Componentes na Mochila (%d/20) ---\n\n", totalComponentes);
    
    if(totalComponentes == 0) {
        printf("** Nenhum componente na mochila. **\n");
    } else {
        printf("%-3s %-25s %-15s %-10s\n", "No", "Nome", "Tipo", "Prioridade");
        printf("------------------------------------------------------------\n");
        
        for(int i = 0; i < totalComponentes; i++) {
            printf("%-3d %-25s %-15s %-10d\n", 
                   i+1, mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
        }
    }
    pausar();
}

void organizar_mochila() {
    if(totalComponentes == 0) {
        printf("\n** Mochila vazia! Nao ha componentes para ordenar. **\n");
        pausar();
        return;
    }

    int opcao;
    
    printf("\n--- Organizar Mochila ---\n");
    printf("Escolha o criterio de ordenacao:\n");
    printf("1. Ordenar por NOME (Bubble Sort)\n");
    printf("2. Ordenar por TIPO (Insertion Sort)\n");
    printf("3. Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("4. Voltar\n\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
        case 1:
            medir_tempo_ordenacao(bubble_sort_nome, mochila, totalComponentes, "Bubble Sort (Nome)");
            ordenadoPorNome = 1;
            break;
        case 2:
            medir_tempo_ordenacao(insertion_sort_tipo, mochila, totalComponentes, "Insertion Sort (Tipo)");
            ordenadoPorNome = 0;
            break;
        case 3:
            medir_tempo_ordenacao(selection_sort_prioridade, mochila, totalComponentes, "Selection Sort (Prioridade)");
            ordenadoPorNome = 0;
            break;
        case 4:
            return;
        default:
            printf("Opcao invalida!\n");
            pausar();
            return;
    }
    
    printf("\n** Organizacao concluida! **\n");
    listar_componentes();
}

// Algoritmo Bubble Sort para ordenar por nome
void bubble_sort_nome(Componente arr[], int n) {
    comparacoes = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if(strcmp(arr[j].nome, arr[j + 1].nome) > 0) {
                // Troca os componentes
                Componente temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Algoritmo Insertion Sort para ordenar por tipo
void insertion_sort_tipo(Componente arr[], int n) {
    comparacoes = 0;
    for(int i = 1; i < n; i++) {
        Componente chave = arr[i];
        int j = i - 1;
        
        comparacoes++;
        while(j >= 0 && strcmp(arr[j].tipo, chave.tipo) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparacoes++;
        }
        arr[j + 1] = chave;
    }
}

// Algoritmo Selection Sort para ordenar por prioridade
void selection_sort_prioridade(Componente arr[], int n) {
    comparacoes = 0;
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            comparacoes++;
            if(arr[j].prioridade > arr[min_idx].prioridade) { // Maior prioridade primeiro
                min_idx = j;
            }
        }
        // Troca o componente encontrado com o primeiro
        Componente temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void medir_tempo_ordenacao(void (*algoritmo)(Componente[], int), Componente arr[], int n, char *nomeAlgoritmo) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    printf("\nExecutando %s...\n", nomeAlgoritmo);
    
    inicio = clock();
    algoritmo(arr, n);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n--- METRICAS DE DESEMPENHO ---\n");
    printf("Algoritmo: %s\n", nomeAlgoritmo);
    printf("Numero de comparacoes: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo_gasto);
}

void busca_binaria_componente() {
    if(totalComponentes == 0) {
        printf("\n** Mochila vazia! Nao ha componentes para buscar. **\n");
        pausar();
        return;
    }
    
    if(!ordenadoPorNome) {
        printf("\n** ATENCAO: A mochila nao esta ordenada por nome! **\n");
        printf("Para usar busca binaria, ordene primeiro por nome.\n");
        pausar();
        return;
    }

    char nomeBuscar[30];
    printf("\n--- Busca Binaria por Componente-Chave ---\n");
    printf("Nome do componente a ser buscado: ");
    fgets(nomeBuscar, 30, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    clock_t inicio, fim;
    double tempo_gasto;
    
    inicio = clock();
    int posicao = busca_binaria(mochila, totalComponentes, nomeBuscar);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if(posicao != -1) {
        printf("\n*** COMPONENTE-CHAVE ENCONTRADO! ***\n");
        printf("Nome: %s\n", mochila[posicao].nome);
        printf("Tipo: %s\n", mochila[posicao].tipo);
        printf("Prioridade: %d\n", mochila[posicao].prioridade);
        printf("Posicao na mochila: %d\n", posicao + 1);
    } else {
        printf("\n** Componente '%s' nao encontrado na mochila. **\n", nomeBuscar);
    }
    
    printf("\n--- METRICAS DE BUSCA ---\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempo_gasto);
    
    pausar();
}

int busca_binaria(Componente arr[], int n, char nome[]) {
    comparacoes = 0;
    int inicio = 0;
    int fim = n - 1;

    while(inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        
        int comparacao = strcmp(arr[meio].nome, nome);
        
        if(comparacao == 0) {
            return meio; // Encontrado
        } else if(comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    return -1; // Não encontrado
}

void ativar_torre_fuga() {
    limpar_tela();
    printf("========================================\n");
    printf("       ATIVACAO DA TORRE DE FUGA\n");
    printf("========================================\n\n");
    
    if(totalComponentes == 0) {
        printf("** ALERTA: Mochila vazia! **\n");
        printf("Nao ha componentes para ativar a torre.\n");
    } else if(!ordenadoPorNome) {
        printf("** ALERTA: Componentes nao organizados! **\n");
        printf("Recomenda-se ordenar por nome antes da ativacao.\n");
    } else {
        printf("*** TORRE ATIVADA COM SUCESSO! ***\n\n");
        printf("Componentes disponiveis para a fuga:\n");
        listar_componentes();
    }
    
    printf("\nObrigado por jogar CODIGO DA ILHA!\n");
    printf("Executando sequencia de fuga...\n\n");
    pausar();
}

// Funções auxiliares
int validar_tipo(char *tipo) {
    return (strcmp(tipo, "controle") == 0 || 
            strcmp(tipo, "suporte") == 0 || 
            strcmp(tipo, "propulsao") == 0);
}

void converter_minusculo(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
}