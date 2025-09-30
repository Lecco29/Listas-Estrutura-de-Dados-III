#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista n�o vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e �nico
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}

// 1) Função para remover aluno por matrícula
int remove_lista_matricula(Lista* li, int matricula){
    if(li == NULL)
        return 0;
    if(*li == NULL) // lista vazia
        return 0;
    
    Elem *no = *li;
    
    // Procura o elemento com a matrícula
    while(no != NULL && no->dados.matricula != matricula){
        no = no->prox;
    }
    
    if(no == NULL)
        return 0; // Não encontrou
    
    // Se é o primeiro elemento
    if(no->ant == NULL){
        *li = no->prox;
        if(no->prox != NULL)
            no->prox->ant = NULL;
    }
    // Se é o último elemento
    else if(no->prox == NULL){
        no->ant->prox = NULL;
    }
    // Se é um elemento do meio
    else{
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
    }
    
    free(no);
    return 1;
}

// 2) Função para inserir de forma ordenada
int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    
    no->dados = al;
    
    // Se a lista está vazia
    if(*li == NULL){
        no->ant = NULL;
        no->prox = NULL;
        *li = no;
        return 1;
    }
    
    Elem *atual = *li;
    Elem *anterior = NULL;
    
    // Procura a posição correta (ordenado por matrícula)
    while(atual != NULL && atual->dados.matricula < al.matricula){
        anterior = atual;
        atual = atual->prox;
    }
    
    // Se deve inserir no início
    if(anterior == NULL){
        no->ant = NULL;
        no->prox = *li;
        if(*li != NULL)
            (*li)->ant = no;
        *li = no;
    }
    // Se deve inserir no meio ou fim
    else{
        no->ant = anterior;
        no->prox = atual;
        anterior->prox = no;
        if(atual != NULL)
            atual->ant = no;
    }
    
    return 1;
}

// 3) Função para contar alunos com nota específica
int conta_lista_nota(Lista* li, int n1){
    if(li == NULL)
        return 0;
    
    int contador = 0;
    Elem *no = *li;
    
    while(no != NULL){
        if(no->dados.n1 == n1){
            contador++;
        }
        no = no->prox;
    }
    
    // O ponteiro li já está apontando para a primeira célula "cabeça" da lista
    return contador;
}

// 4) Funções para lista circular
int insere_lista_inicio_circular(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    
    no->dados = al;
    
    if(*li == NULL){
        // Lista vazia - elemento aponta para si mesmo
        no->ant = no;
        no->prox = no;
        *li = no;
    }
    else{
        // Lista não vazia - encontra o último elemento
        Elem *ultimo = *li;
        while(ultimo->prox != *li){
            ultimo = ultimo->prox;
        }
        
        no->ant = ultimo;
        no->prox = *li;
        (*li)->ant = no;
        ultimo->prox = no;
        *li = no;
    }
    
    return 1;
}

int insere_lista_final_circular(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    
    no->dados = al;
    
    if(*li == NULL){
        // Lista vazia
        no->ant = no;
        no->prox = no;
        *li = no;
    }
    else{
        // Lista não vazia - encontra o último elemento
        Elem *ultimo = *li;
        while(ultimo->prox != *li){
            ultimo = ultimo->prox;
        }
        
        no->ant = ultimo;
        no->prox = *li;
        ultimo->prox = no;
        (*li)->ant = no;
    }
    
    return 1;
}

int remove_lista_inicio_circular(Lista* li){
    if(li == NULL)
        return 0;
    if(*li == NULL) // lista vazia
        return 0;
    
    Elem *no = *li;
    
    if(no->prox == no){
        // Só tem um elemento
        *li = NULL;
    }
    else{
        // Tem mais de um elemento - encontra o último
        Elem *ultimo = *li;
        while(ultimo->prox != *li){
            ultimo = ultimo->prox;
        }
        
        Elem *proximo = no->prox;
        ultimo->prox = proximo;
        proximo->ant = ultimo;
        *li = proximo;
    }
    
    free(no);
    return 1;
}

int remove_lista_final_circular(Lista* li){
    if(li == NULL)
        return 0;
    if(*li == NULL) // lista vazia
        return 0;
    
    Elem *ultimo = *li;
    while(ultimo->prox != *li){
        ultimo = ultimo->prox;
    }
    
    if(ultimo == *li){
        // Só tem um elemento
        *li = NULL;
    }
    else{
        // Tem mais de um elemento
        Elem *penultimo = ultimo->ant;
        penultimo->prox = *li;
        (*li)->ant = penultimo;
    }
    
    free(ultimo);
    return 1;
}

void percorre_lista_circular(Lista* li){
    if(li == NULL)
        return;
    if(*li == NULL) // lista vazia
        return;
    
    Elem *p = *li;
    
    do{
        printf("Matricula: %d\n", p->dados.matricula);
        printf("Nome: %s\n", p->dados.nome);
        printf("Notas: %f %f %f\n", p->dados.n1, p->dados.n2, p->dados.n3);
        printf("-------------------------------\n");
        
        p = p->prox;
    } while(p != *li);
}

// 5) Funções da fila usando ponteiros puros
int inicializa_fila(Lista* li){
    if(li == NULL)
        return 0;
    *li = NULL;
    return 1;
}

int enfileirar(Lista* li, int elem){
    if(li == NULL)
        return 0;
    
    Elem *novo = (Elem*)malloc(sizeof(Elem));
    if(novo == NULL)
        return 0;
    
    // Usa o campo matricula para armazenar o elemento da fila
    novo->dados.matricula = elem;
    novo->prox = NULL;
    novo->ant = NULL;
    
    if(*li == NULL){
        // Fila vazia
        *li = novo;
    }
    else{
        // Fila não vazia - insere no fim
        Elem *aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
    
    return 1;
}

int desenfileirar(Lista* li, int *elem){
    if(li == NULL)
        return 0;
    if(*li == NULL) // fila vazia
        return 0;
    
    Elem *aux = *li;
    *elem = aux->dados.matricula;
    
    if(aux->prox == NULL){
        // Só tem um elemento
        *li = NULL;
    }
    else{
        // Tem mais de um elemento
        *li = aux->prox;
        (*li)->ant = NULL;
    }
    
    free(aux);
    return 1;
}

