#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaDin.h"

void demonstra_Questao1(){
    printf("=== QUESTAO 1 - Funcao separa ===\n");
    // Crio alguns alunos para testar
    struct aluno a[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};
    
    Fila* f1 = cria_Fila();
    Fila* f2 = cria_Fila();
    
    // Insere todos os alunos na fila f1
    for(int i = 0; i < 4; i++){
        insere_Fila(f1, a[i]);
    }
    
    printf("Fila original:\n");
    imprime_Fila(f1);
    
    // Agora vou separar a fila na primeira ocorrência da matrícula 1
    // A fila fica: [Andre, Ricardo, Bianca, Ana]
    // Vou separar no Bianca (matrícula 1)
    // Resultado esperado: f1=[Andre, Ricardo] e f2=[Bianca, Ana]
    if(separa(f1, f2, 1)){
        printf("\nFila f1 apos separacao:\n");
        imprime_Fila(f1);
        printf("\nFila f2 apos separacao:\n");
        imprime_Fila(f2);
    }
    
    libera_Fila(f1);
    libera_Fila(f2);
}

void demonstra_Questao3(){
    printf("\n=== QUESTAO 3 - Inverter fila com pilha ===\n");
    // Vou testar a inversão usando uma pilha como intermediária
    struct aluno a[3] = {{1,"Ana",5.7,6.1,7.4},
                         {2,"Bruno",8.5,7.2,9.1},
                         {3,"Carlos",6.8,8.3,7.5}};
    
    Fila* fi = cria_Fila();
    
    // Insere os elementos na ordem: Ana, Bruno, Carlos
    for(int i = 0; i < 3; i++){
        insere_Fila(fi, a[i]);
    }
    
    printf("Fila antes da inversao:\n");
    imprime_Fila(fi);
    
    // A função inverte_Fila usa uma pilha internamente
    // A pilha inverte automaticamente a ordem (LIFO)
    inverte_Fila(fi);
    
    printf("\nFila apos inversao:\n");
    imprime_Fila(fi);
    
    libera_Fila(fi);
}

void demonstra_Questao4(){
    printf("\n=== QUESTAO 4 - Fura fila ===\n");
    // Vou testar a função FuraFila que coloca um elemento no início da fila
    struct aluno a[3] = {{1,"Ana",5.7,6.1,7.4},
                         {2,"Bruno",8.5,7.2,9.1},
                         {3,"Carlos",6.8,8.3,7.5}};
    
    Fila* fi = cria_Fila();
    
    // Primeiro insiro Ana e Bruno normalmente (no final da fila)
    for(int i = 0; i < 2; i++){
        insere_Fila(fi, a[i]);
    }
    
    printf("Fila apos insercao normal:\n");
    imprime_Fila(fi);
    
    // Agora vou "furar" a fila colocando Carlos no início
    // Isso quebra a regra FIFO, mas às vezes é necessário
    printf("\nFurando a fila com Carlos:\n");
    FuraFila(fi, a[2]);
    imprime_Fila(fi);
    
    libera_Fila(fi);
}

void demonstra_Questao5(){
    printf("\n=== QUESTAO 5 - Controle de aeroporto ===\n");
    // Simulo um sistema de controle de aeroporto
    // Os aviões entram na fila e saem na ordem de chegada (FIFO)
    Fila* fa = cria_Fila();
    
    // Adiciono alguns aviões na fila de decolagem
    adiciona_Aviao(fa, 101, "Boeing 737", "GOL");
    adiciona_Aviao(fa, 102, "Airbus A320", "LATAM");
    adiciona_Aviao(fa, 103, "Boeing 777", "Azul");
    
    printf("Numero de avioes aguardando: %d\n", tamanho_Fila(fa));
    printf("\nTodos os avioes na fila:\n");
    lista_Avioes(fa);
    
    printf("\nPrimeiro aviao da fila:\n");
    lista_PrimeiroAviao(fa);
    
    // O primeiro avião da fila pode decolar
    printf("\nAutorizando decolagem do primeiro aviao...\n");
    autoriza_Decolagem(fa);
    
    printf("Aviões restantes:\n");
    lista_Avioes(fa);
    
    libera_Fila(fa);
}

void demonstra_Questao6(){
    printf("\n=== QUESTAO 6 - Mesclar filas ordenadas ===\n");
    // Vou testar a mesclagem de duas filas já ordenadas
    // É tipo o merge do merge sort, mas com filas
    struct aluno a1[2] = {{1,"Ana",5.7,6.1,7.4},
                          {3,"Carlos",6.8,8.3,7.5}};
    struct aluno a2[2] = {{2,"Bruno",8.5,7.2,9.1},
                          {4,"Diana",7.2,8.1,6.9}};
    
    Fila* f1 = cria_Fila();
    Fila* f2 = cria_Fila();
    Fila* f3 = cria_Fila();
    
    // Insere elementos já ordenados por matrícula
    // f1 terá: Ana(1), Carlos(3)
    // f2 terá: Bruno(2), Diana(4)
    for(int i = 0; i < 2; i++){
        insere_Fila(f1, a1[i]);
        insere_Fila(f2, a2[i]);
    }
    
    printf("Fila 1 (ordenada):\n");
    imprime_Fila(f1);
    printf("\nFila 2 (ordenada):\n");
    imprime_Fila(f2);
    
    // A mesclagem deve resultar em: Ana(1), Bruno(2), Carlos(3), Diana(4)
    mescla_FilasOrdenadas(f1, f2, f3);
    
    printf("\nFila 3 (mesclada):\n");
    imprime_Fila(f3);
    
    libera_Fila(f1);
    libera_Fila(f2);
    libera_Fila(f3);
}

void demonstra_Questao7(){
    printf("\n=== QUESTAO 7 - Funcao reverso ===\n");
    // Vou testar a inversão direta da fila (sem usar pilha)
    struct aluno a[3] = {{1,"Ana",5.7,6.1,7.4},
                         {2,"Bruno",8.5,7.2,9.1},
                         {3,"Carlos",6.8,8.3,7.5}};
    
    Fila* fi = cria_Fila();
    
    // Insere os elementos na ordem: Ana, Bruno, Carlos
    for(int i = 0; i < 3; i++){
        insere_Fila(fi, a[i]);
    }
    
    printf("Fila antes do reverso:\n");
    imprime_Fila(fi);
    
    // A função reverso inverte os ponteiros diretamente
    // Resultado esperado: Carlos, Bruno, Ana
    reverso(fi);
    
    printf("\nFila apos reverso:\n");
    imprime_Fila(fi);
    
    libera_Fila(fi);
}

int main(){
    printf("=== DEMONSTRACAO DAS FUNCOES IMPLEMENTADAS ===\n\n");
    
    // Vou demonstrar cada questão implementada
    // Cada função mostra como usar as operações da fila
    demonstra_Questao1(); // Separa fila baseada em matrícula
    demonstra_Questao3(); // Inverte fila usando pilha
    demonstra_Questao4(); // Fura fila (insere no início)
    demonstra_Questao5(); // Simulação de aeroporto
    demonstra_Questao6(); // Mescla filas ordenadas
    demonstra_Questao7(); // Inverte fila diretamente
    
    printf("\n=== EXECUTANDO MENU INTERATIVO ===\n");
    // Menu para testar todas as funcionalidades interativamente
    executa_Menu();
    
    return 0;
}


