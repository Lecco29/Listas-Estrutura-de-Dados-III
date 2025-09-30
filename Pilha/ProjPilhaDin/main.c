#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

int main(){
    printf("=== DEMONSTRACAO DAS FUNCOES DA PILHA ===\n\n");
    
    // Cria pilha
    Pilha* pi = cria_Pilha();
    
    // Dados de teste
    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    
    printf("1. TESTE DAS FUNCOES BASICAS:\n");
    printf("Tamanho inicial: %d\n", tamanho_Pilha(pi));
    
    // Empilha elementos
    for(int i = 0; i < 4; i++)
        insere_Pilha(pi, a[i]);
    
    printf("Tamanho apos empilhar: %d\n", tamanho_Pilha(pi));
    printf("Pilha atual:\n");
    imprime_Pilha(pi);
    
    printf("\n2. TESTE DA FUNCAO pop2():\n");
    if(pop2(pi))
        printf("Dois elementos desempilhados com sucesso!\n");
    else
        printf("Erro ao desempilhar dois elementos!\n");
    printf("Tamanho apos pop2: %d\n", tamanho_Pilha(pi));
    
    printf("\n3. TESTE DA FUNCAO push2():\n");
    struct aluno novo1 = {5, "Carlos", 8.0, 7.5, 9.0};
    struct aluno novo2 = {6, "Maria", 6.5, 8.0, 7.5};
    if(push2(pi, novo1, novo2))
        printf("Dois elementos empilhados com sucesso!\n");
    else
        printf("Erro ao empilhar dois elementos!\n");
    printf("Tamanho apos push2: %d\n", tamanho_Pilha(pi));
    
    printf("\n4. TESTE DA FUNCAO popN():\n");
    printf("Desempilhando 3 elementos...\n");
    if(popN(pi, 3))
        printf("Tres elementos desempilhados com sucesso!\n");
    else
        printf("Erro ao desempilhar tres elementos!\n");
    printf("Tamanho apos popN(3): %d\n", tamanho_Pilha(pi));
    
    printf("\n5. TESTE DA FUNCAO pilha_copia():\n");
    // Empilha alguns elementos para testar a cópia
    insere_Pilha(pi, a[0]);
    insere_Pilha(pi, a[1]);
    
    Pilha* copia = pilha_copia(pi);
    if(copia != NULL){
        printf("Copia da pilha criada com sucesso!\n");
        printf("Pilha original:\n");
        imprime_Pilha(pi);
        printf("Pilha copia:\n");
        imprime_Pilha(copia);
        libera_Pilha(copia);
    } else {
        printf("Erro ao criar copia da pilha!\n");
    }
    
    printf("\n6. TESTE DA FUNCAO maior_menor_media():\n");
    int maior, menor;
    float media;
    maior_menor_media(pi, &maior, &menor, &media);
    printf("Maior: %d, Menor: %d, Media: %.2f\n", maior, menor, media);
    
    printf("\n7. TESTE DA FUNCAO conta_pares_impares():\n");
    int pares, impares;
    conta_pares_impares(pi, &pares, &impares);
    printf("Pares: %d, Impares: %d\n", pares, impares);
    
    printf("\n8. TESTE DO TEXTO INVERSO:\n");
    texto_inverso();
    
    printf("\n9. TESTE DO PALINDROMO:\n");
    char texto[] = "A man a plan a canal Panama";
    printf("Testando: '%s'\n", texto);
    if(verifica_palindromo(texto))
        printf("E um palindromo!\n");
    else
        printf("Nao e um palindromo!\n");
    
    printf("\n10. TESTE DA CADEIA xCy:\n");
    char cadeia[] = "ABABBA";
    printf("Testando cadeia: '%s'\n", cadeia);
    if(verifica_cadeia_xCy(cadeia))
        printf("A cadeia segue o padrao xCy!\n");
    else
        printf("A cadeia nao segue o padrao xCy!\n");
    
    printf("\n11. TESTE DE PILHAS IGUAIS:\n");
    Pilha* pi2 = cria_Pilha();
    insere_Pilha(pi2, a[0]);
    insere_Pilha(pi2, a[1]);
    
    if(pilhas_iguais(pi, pi2))
        printf("As pilhas sao iguais!\n");
    else
        printf("As pilhas sao diferentes!\n");
    
    libera_Pilha(pi2);
    
    printf("\n12. MENU PRINCIPAL:\n");
    printf("Deseja executar o menu principal? (1-Sim, 0-Nao): ");
    int escolha;
    scanf("%d", &escolha);
    if(escolha == 1){
        printf("\n=== MENU PRINCIPAL ===\n");
        menu_principal();
    }
    
    libera_Pilha(pi);
    printf("\nPrograma finalizado!\n");
    return 0;
}