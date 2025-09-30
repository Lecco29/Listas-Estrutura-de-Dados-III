#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h"
int main(){
    struct aluno al, a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    Lista* li = cria_lista();
    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));

    int i;
    for(i=0; i < 4; i++)
        insere_lista_ordenada(li,a[i]);

    imprime_lista(li);
    printf("\n\n\n\n Tamanho: %d\n",tamanho_lista(li));

    // Teste da função conta_lista_nota
    printf("\nAlunos com nota 9.5: %d\n", conta_lista_nota(li, 9.5));
    
    // Teste da função remove_lista_matricula
    printf("\nRemovendo aluno com matricula 2...\n");
    remove_lista_matricula(li, 2);
    imprime_lista(li);
    printf("\nTamanho apos remocao: %d\n",tamanho_lista(li));

    // Teste das funções circulares
    printf("\n=== TESTE LISTA CIRCULAR ===\n");
    Lista* li_circular = cria_lista();
    
    for(i=0; i < 3; i++)
        insere_lista_inicio_circular(li_circular, a[i]);
    
    printf("Percorrendo lista circular:\n");
    percorre_lista_circular(li_circular);
    
    // Teste da fila
    printf("\n=== TESTE FILA ===\n");
    Lista* fila = cria_lista();
    int elemento;
    
    inicializa_fila(fila);
    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);
    
    printf("Desenfileirando: ");
    while(desenfileirar(fila, &elemento)){
        printf("%d ", elemento);
    }
    printf("\n");
    
    libera_lista(fila);

    libera_lista(li_circular);
    libera_lista(li);
    system("pause");
    return 0;
}

