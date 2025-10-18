#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Definição da estrutura do item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Variáveis globais
struct Item mochila[10];
int totalItens = 0;

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void menu();
void converterParaMinusculo(char *str);
void limparTela();
void pausar();

int main() {
    menu();
    return 0;
}

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    printf("\n# Pressione Enter para continuar...");
    getchar();
}

void converterParaMinusculo(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void menu() {
    int opcao;
    while(1) {
        limparTela();
        printf("----------------------------------------\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("----------------------------------------\n\n");
        
        printf("** Itens na Mochila: %d/10 **\n\n", totalItens);
        
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n\n");
        
        printf("----------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: 
                inserirItem(); 
                break;
            case 2: 
                removerItem(); 
                break;
            case 3: 
                listarItens(); 
                pausar();
                break;
            case 4: 
                buscarItem(); 
                pausar();
                break;
            case 5: 
                printf("\nSaindo do sistema...\n");
                exit(0);
            default: 
                printf("\nOpcao invalida! Tente novamente.\n");
                pausar();
        }
    }
}

void inserirItem() {
    if(totalItens >= 10) {
        limparTela();
        printf("----------------------------------------\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("----------------------------------------\n\n");
        printf("** Mochila cheia! Nao e possivel adicionar mais itens. **\n");
        pausar();
        return;
    }

    struct Item novoItem;
    
    limparTela();
    printf("----------------------------------------\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("----------------------------------------\n\n");
    printf("--- Adicionar Novo Item ---\n\n");
    
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    // Validação do tipo com loop até obter resposta válida
    int tipoValido = 0;
    char tipoInput[20];
    
    while(!tipoValido) {
        printf("Tipo do item (arma, municao, cura): ");
        fgets(tipoInput, 20, stdin);
        tipoInput[strcspn(tipoInput, "\n")] = '\0';
        
        // Converte para minúsculo para facilitar comparação
        converterParaMinusculo(tipoInput);
        
        // Verifica se o tipo é válido
        if(strcmp(tipoInput, "arma") == 0 || 
           strcmp(tipoInput, "municao") == 0 || 
           strcmp(tipoInput, "cura") == 0) {
            tipoValido = 1;
            strcpy(novoItem.tipo, tipoInput);
        } else {
            printf("** Tipo invalido! Use: arma, municao ou cura **\n\n");
        }
    }

    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar();

    // Adiciona item na mochila
    mochila[totalItens] = novoItem;
    totalItens++;
    
    printf("\n** Item '%s' adicionado com sucesso! **\n", novoItem.nome);
    pausar();
}

void removerItem() {
    if(totalItens == 0) {
        limparTela();
        printf("----------------------------------------\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("----------------------------------------\n\n");
        printf("** Mochila vazia! Nao ha itens para remover. **\n");
        pausar();
        return;
    }

    char nomeRemover[30];
    limparTela();
    printf("----------------------------------------\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("----------------------------------------\n\n");
    printf("--- Remover Item ---\n\n");
    
    printf("Nome do item a ser removido: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            // Desloca itens posteriores
            for(int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n** Item '%s' removido com sucesso! **\n", nomeRemover);
            break;
        }
    }

    if(!encontrado) {
        printf("\n** Item '%s' nao encontrado na mochila. **\n", nomeRemover);
    }
    
    pausar();
}

void listarItens() {
    limparTela();
    printf("----------------------------------------\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("----------------------------------------\n\n");
    
    printf("--- Itens na Mochila (%d/10) ---\n\n", totalItens);
    
    if(totalItens == 0) {
        printf("** Mochila vazia. **\n");
        return;
    }

    for(int i = 0; i < totalItens; i++) {
        printf("%d. %s | Tipo: %s | Quantidade: %d\n", 
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void buscarItem() {
    if(totalItens == 0) {
        limparTela();
        printf("----------------------------------------\n");
        printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("----------------------------------------\n\n");
        printf("** Mochila vazia! Nao ha itens para buscar. **\n");
        return;
    }

    char nomeBuscar[30];
    limparTela();
    printf("----------------------------------------\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("----------------------------------------\n\n");
    printf("--- Buscar Item ---\n\n");
    
    printf("Nome do item a ser buscado: ");
    fgets(nomeBuscar, 30, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    int encontrado = 0;
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\n** Item encontrado: **\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if(!encontrado) {
        printf("\n** Item '%s' nao encontrado na mochila. **\n", nomeBuscar);
    }
}