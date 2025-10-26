#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

// Exercício 1
// testa funções insere_Arvore e remove_Arvore
void exercicio1() {
    printf("=== EXERCICIO 1 ===\n\n");
    
    printf("Testando insere_ArvBin:\n");
    printf("A funcao insere_ArvBin opera da seguinte forma:\n");
    printf("1. Cria um novo no com o valor\n");
    printf("2. Se a arvore esta vazia, o novo no vira a raiz\n");
    printf("3. Se nao esta vazia, percorre a arvore comparando valores\n");
    printf("4. Se valor > no atual, vai para direita\n");
    printf("5. Se valor < no atual, vai para esquerda\n");
    printf("6. Se valor = no atual, nao insere (elemento ja existe)\n");
    printf("7. Quando encontra posicao vazia, insere o novo no\n\n");
    
    ArvBin* raiz = cria_ArvBin();
    
    printf("Inserindo valores: 50, 30, 70, 20, 40, 60, 80\n");
    insere_ArvBin(raiz, 50);
    insere_ArvBin(raiz, 30);
    insere_ArvBin(raiz, 70);
    insere_ArvBin(raiz, 20);
    insere_ArvBin(raiz, 40);
    insere_ArvBin(raiz, 60);
    insere_ArvBin(raiz, 80);
    
    printf("Arvore apos insercao (pre-ordem):\n");
    preOrdem_ArvBin(raiz);
    
    printf("\nTestando remove_ArvBin:\n");
    printf("A funcao remove_ArvBin opera da seguinte forma:\n");
    printf("1. Procura o no com o valor a ser removido\n");
    printf("2. Se nao encontra, retorna 0\n");
    printf("3. Se encontra, chama remove_atual para remover o no\n");
    printf("4. remove_atual tem 3 casos:\n");
    printf("   - No sem filhos: apenas remove\n");
    printf("   - No com 1 filho: substitui pelo filho\n");
    printf("   - No com 2 filhos: substitui pelo maior da subarvore esquerda\n\n");
    
    printf("Removendo valor 30:\n");
    if(remove_ArvBin(raiz, 30)) {
        printf("Valor removido com sucesso!\n");
        printf("Arvore apos remocao (pre-ordem):\n");
        preOrdem_ArvBin(raiz);
    } else {
        printf("Valor nao encontrado!\n");
    }
    
    libera_ArvBin(raiz);
    printf("\n");
}

// Exercício 2
// implementa EMOrdem_Arvore e POSOrdem_ArvBin
void emOrdem_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL) {
        emOrdem_ArvBin(&((*raiz)->esq));  // visita subarvore esquerda
        printf("%d\n", (*raiz)->info);    // visita raiz
        emOrdem_ArvBin(&((*raiz)->dir));  // visita subarvore direita
    }
}

void posOrdem_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL) {
        posOrdem_ArvBin(&((*raiz)->esq)); // visita subarvore esquerda
        posOrdem_ArvBin(&((*raiz)->dir)); // visita subarvore direita
        printf("%d\n", (*raiz)->info);    // visita raiz
    }
}

void exercicio2() {
    printf("=== EXERCICIO 2 ===\n\n");
    
    printf("Implementando EMOrdem_Arvore e POSOrdem_ArvBin:\n");
    printf("EMOrdem: esquerda -> raiz -> direita\n");
    printf("POSOrdem: esquerda -> direita -> raiz\n\n");
    
    ArvBin* raiz = cria_ArvBin();
    
    // insere alguns valores para teste
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = 7;
    
    printf("Inserindo valores: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");
    
    printf("PRE-ORDEM (raiz -> esquerda -> direita):\n");
    preOrdem_ArvBin(raiz);
    printf("\n");
    
    printf("EM-ORDEM (esquerda -> raiz -> direita):\n");
    emOrdem_ArvBin(raiz);
    printf("\n");
    
    printf("POS-ORDEM (esquerda -> direita -> raiz):\n");
    posOrdem_ArvBin(raiz);
    printf("\n");
    
    libera_ArvBin(raiz);
}

// Exercício 3
// conta quantidade de nós na árvore
int TotalNO_Arvore(ArvBin *raiz) {
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    
    // conta raiz + nós da esquerda + nós da direita
    return 1 + TotalNO_Arvore(&((*raiz)->esq)) + TotalNO_Arvore(&((*raiz)->dir));
}

void exercicio3() {
    printf("=== EXERCICIO 3 ===\n\n");
    
    printf("Funcao TotalNO_Arvore: conta quantidade de nos na arvore\n");
    printf("Operacao recursiva:\n");
    printf("1. Se arvore vazia, retorna 0\n");
    printf("2. Senao, retorna 1 (raiz) + nos da esquerda + nos da direita\n\n");
    
    ArvBin* raiz = cria_ArvBin();
    
    // insere valores para teste
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = 11;
    
    printf("Inserindo %d valores: ", n);
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");
    
    printf("Arvore (pre-ordem):\n");
    preOrdem_ArvBin(raiz);
    printf("\n");
    
    int total = TotalNO_Arvore(raiz);
    printf("Total de nos na arvore: %d\n", total);
    
    libera_ArvBin(raiz);
    printf("\n");
}

// Exercício 4
// consulta se um valor existe na árvore
int Cons_Arvore(ArvBin *raiz, int valor) {
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    
    if((*raiz)->info == valor)
        return 1;  // encontrou o valor
    
    // busca recursivamente nas subarvores
    if(valor < (*raiz)->info)
        return Cons_Arvore(&((*raiz)->esq), valor);
    else
        return Cons_Arvore(&((*raiz)->dir), valor);
}

void exercicio4() {
    printf("=== EXERCICIO 4 ===\n\n");
    
    printf("Funcao Cons_Arvore: consulta se um valor existe na arvore\n");
    printf("Operacao recursiva:\n");
    printf("1. Se arvore vazia, retorna 0\n");
    printf("2. Se valor = raiz, retorna 1 (encontrou)\n");
    printf("3. Se valor < raiz, busca na subarvore esquerda\n");
    printf("4. Se valor > raiz, busca na subarvore direita\n\n");
    
    ArvBin* raiz = cria_ArvBin();
    
    // insere valores para teste
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = 11;
    
    printf("Inserindo valores: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");
    
    // testa consultas
    int consultas[] = {50, 25, 100, 35, 5, 80};
    int m = 6;
    
    printf("Testando consultas:\n");
    for(int i = 0; i < m; i++) {
        int valor = consultas[i];
        if(Cons_Arvore(raiz, valor))
            printf("Valor %d: ENCONTRADO\n", valor);
        else
            printf("Valor %d: NAO ENCONTRADO\n", valor);
    }
    
    libera_ArvBin(raiz);
    printf("\n");
}

// Exercício 5
// remove um nó específico da árvore
struct NO* Remove_ArvoreAtual(struct NO* atual) {
    if(atual == NULL)
        return NULL;
    
    // caso 1: nó sem filhos
    if(atual->esq == NULL && atual->dir == NULL) {
        free(atual);
        return NULL;
    }
    
    // caso 2: nó com apenas um filho
    if(atual->esq == NULL) {
        struct NO* temp = atual->dir;
        free(atual);
        return temp;
    }
    if(atual->dir == NULL) {
        struct NO* temp = atual->esq;
        free(atual);
        return temp;
    }
    
    // caso 3: nó com dois filhos
    // encontra o maior valor da subárvore esquerda
    struct NO* pai = atual;
    struct NO* maior = atual->esq;
    
    while(maior->dir != NULL) {
        pai = maior;
        maior = maior->dir;
    }
    
    // se o maior não é filho direto da raiz
    if(pai != atual) {
        pai->dir = maior->esq;
        maior->esq = atual->esq;
    }
    
    maior->dir = atual->dir;
    free(atual);
    return maior;
}

void exercicio5() {
    printf("=== EXERCICIO 5 ===\n\n");
    
    printf("Funcao Remove_ArvoreAtual: remove um no especifico da arvore\n");
    printf("Trata 3 casos:\n");
    printf("1. No sem filhos: apenas remove\n");
    printf("2. No com 1 filho: substitui pelo filho\n");
    printf("3. No com 2 filhos: substitui pelo maior da subarvore esquerda\n\n");
    
    ArvBin* raiz = cria_ArvBin();
    
    // insere valores para teste
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    int n = 11;
    
    printf("Inserindo valores: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", valores[i]);
        insere_ArvBin(raiz, valores[i]);
    }
    printf("\n\n");
    
    printf("Arvore original (pre-ordem):\n");
    preOrdem_ArvBin(raiz);
    printf("\n");
    
    // testa remoção de diferentes tipos de nós
    printf("Removendo no 10 (sem filhos):\n");
    if(remove_ArvBin(raiz, 10)) {
        printf("Removido com sucesso!\n");
        printf("Arvore apos remocao:\n");
        preOrdem_ArvBin(raiz);
    }
    printf("\n");
    
    printf("Removendo no 20 (com 1 filho):\n");
    if(remove_ArvBin(raiz, 20)) {
        printf("Removido com sucesso!\n");
        printf("Arvore apos remocao:\n");
        preOrdem_ArvBin(raiz);
    }
    printf("\n");
    
    printf("Removendo no 30 (com 2 filhos):\n");
    if(remove_ArvBin(raiz, 30)) {
        printf("Removido com sucesso!\n");
        printf("Arvore apos remocao:\n");
        preOrdem_ArvBin(raiz);
    }
    
    libera_ArvBin(raiz);
    printf("\n");
}

// Menu principal
void menu() {
    printf("EXERCICIOS DE ARVORE BINARIA\n\n");
    printf("1. Testar insere_Arvore e remove_Arvore\n");
    printf("2. Implementar EMOrdem e POSOrdem\n");
    printf("3. Contar nos da arvore\n");
    printf("4. Consultar valor na arvore\n");
    printf("5. Remover no especifico\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao;
    
    do {
        menu();
        scanf("%d", &opcao);
        printf("\n");
        
        switch(opcao) {
            case 1: exercicio1(); break;
            case 2: exercicio2(); break;
            case 3: exercicio3(); break;
            case 4: exercicio4(); break;
            case 5: exercicio5(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n"); break;
        }
        
        if(opcao != 0) {
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
            printf("\n");
        }
        
    } while(opcao != 0);
    
    return 0;
}
