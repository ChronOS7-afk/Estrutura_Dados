#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração do vetor para armazenar 5 territórios
    struct Territorio territorios[5];
    
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n\n");
    
    // Loop para cadastrar os 5 territórios
    for(int i = 0; i < 5; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);
        
        // Entrada do nome do território
        printf("Nome do Territorio: ");
        scanf("%29s", territorios[i].nome);
        
        // Entrada da cor do exército
        printf("Cor do Exercito (ex: Azul, Verde): ");
        scanf("%9s", territorios[i].cor);
        
        // Entrada do número de tropas
        printf("Numero de Tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n");
    }
    
    // Exibição dos dados cadastrados
    printf("=== TERRITORIOS CADASTRADOS ===\n");
    for(int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }
    
    return 0;
}