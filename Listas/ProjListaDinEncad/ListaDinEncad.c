#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elemento;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elemento* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        *li = no;
    }else{
        Elemento *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento* no;
    no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elemento *no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    no->dados = al;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elemento *ant, *atual = *li;
        while(atual != NULL && atual->dados.matricula < al.matricula){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere in�cio
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elemento *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//n�o encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elemento *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li))//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elemento* no = *li;
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
    Elemento* no = *li;
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

// Questão 1a: Consulta aluno por matrícula
struct aluno consulta_lista_matricula(Lista* li, int mat){
    struct aluno aluno_vazio = {0, "", 0.0, 0.0, 0.0};
    
    if(li == NULL || (*li) == NULL)
        return aluno_vazio;
    
    Elemento* no = *li;
    while(no != NULL){
        if(no->dados.matricula == mat)
            return no->dados;
        no = no->prox;
    }
    
    return aluno_vazio;
}

// Questão 1b: Consulta aluno por posição
struct aluno consulta_lista_posicao(Lista* li, int pos){
    struct aluno aluno_vazio = {0, "", 0.0, 0.0, 0.0};
    
    if(li == NULL || (*li) == NULL || pos < 0)
        return aluno_vazio;
    
    Elemento* no = *li;
    int cont = 0;
    
    while(no != NULL && cont < pos){
        no = no->prox;
        cont++;
    }
    
    if(no == NULL)
        return aluno_vazio;
    
    return no->dados;
}

// Questão 2a: Remove nó recursivamente por valor
int remove_lista_recursiva(Lista* li, int valor){
    if(li == NULL || (*li) == NULL)
        return 0;
    
    Elemento* no = *li;
    
    if(no->dados.matricula == valor){
        *li = no->prox;
        free(no);
        return 1;
    }
    
    return remove_lista_recursiva(&(no->prox), valor);
}

// Questão 2b: Verifica se duas listas são iguais recursivamente
int listas_iguais_recursiva(Lista* li1, Lista* li2){
    if(li1 == NULL && li2 == NULL)
        return 1;
    if(li1 == NULL || li2 == NULL)
        return 0;
    if((*li1) == NULL && (*li2) == NULL)
        return 1;
    if((*li1) == NULL || (*li2) == NULL)
        return 0;
    
    Elemento* no1 = *li1;
    Elemento* no2 = *li2;
    
    if(no1->dados.matricula != no2->dados.matricula)
        return 0;
    
    return listas_iguais_recursiva(&(no1->prox), &(no2->prox));
}

// Questão 3: Insere em posição qualquer
int insere_lista_posicao(Lista* li, struct aluno al, int pos){
    if(li == NULL || pos < 0)
        return 0;
    
    if(pos == 0){
        return insere_lista_inicio(li, al);
    }
    
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(no == NULL)
        return 0;
    
    no->dados = al;
    
    Elemento* atual = *li;
    int cont = 0;
    
    while(atual != NULL && cont < pos - 1){
        atual = atual->prox;
        cont++;
    }
    
    if(atual == NULL)
        return 0;
    
    no->prox = atual->prox;
    atual->prox = no;
    
    return 1;
}

// Questão 4: Constrói lista a partir de vetor float
Lista* constroi_lista_vetor(float* vetor, int tamanho){
    Lista* li = cria_lista();
    if(li == NULL)
        return NULL;
    
    int i;
    for(i = 0; i < tamanho; i++){
        struct aluno al;
        al.matricula = i + 1;
        sprintf(al.nome, "Aluno_%d", i + 1);
        al.n1 = vetor[i];
        al.n2 = 0.0;
        al.n3 = 0.0;
        
        insere_lista_final(li, al);
    }
    
    return li;
}

// Questão 5: Remove todos os nós com valor específico
int remove_todos_valor(Lista* li, int valor){
    if(li == NULL || (*li) == NULL)
        return 0;
    
    int removidos = 0;
    Elemento* ant = NULL;
    Elemento* atual = *li;
    
    while(atual != NULL){
        if(atual->dados.matricula == valor){
            if(ant == NULL){
                *li = atual->prox;
                free(atual);
                atual = *li;
            } else {
                ant->prox = atual->prox;
                free(atual);
                atual = ant->prox;
            }
            removidos++;
        } else {
            ant = atual;
            atual = atual->prox;
        }
    }
    
    return removidos;
}

// Questão 6: Concatena duas listas
int concatena_listas(Lista* li1, Lista* li2){
    if(li1 == NULL || li2 == NULL)
        return 0;
    
    if((*li1) == NULL){
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }
    
    Elemento* no = *li1;
    while(no->prox != NULL){
        no = no->prox;
    }
    
    no->prox = *li2;
    *li2 = NULL;
    
    return 1;
}

// Questão 7: Remove elementos repetidos
int remove_repetidos(Lista* li){
    if(li == NULL || (*li) == NULL)
        return 0;
    
    int removidos = 0;
    Elemento* atual = *li;
    
    while(atual != NULL && atual->prox != NULL){
        Elemento* ant = atual;
        Elemento* prox = atual->prox;
        
        while(prox != NULL){
            if(atual->dados.matricula == prox->dados.matricula){
                ant->prox = prox->prox;
                free(prox);
                prox = ant->prox;
                removidos++;
            } else {
                ant = prox;
                prox = prox->prox;
            }
        }
        
        atual = atual->prox;
    }
    
    return removidos;
}

// Questão 8: Fusão de listas ordenadas
int fusao_listas_ordenadas(Lista* li1, Lista* li2){
    if(li1 == NULL || li2 == NULL)
        return 0;
    
    if((*li2) == NULL)
        return 1;
    
    if((*li1) == NULL){
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }
    
    Elemento* no1 = *li1;
    Elemento* no2 = *li2;
    Elemento* ant = NULL;
    
    while(no1 != NULL && no2 != NULL){
        if(no1->dados.matricula <= no2->dados.matricula){
            ant = no1;
            no1 = no1->prox;
        } else {
            if(ant == NULL){
                *li1 = no2;
                no2 = no2->prox;
                (*li1)->prox = no1;
                ant = *li1;
            } else {
                ant->prox = no2;
                no2 = no2->prox;
                ant->prox->prox = no1;
                ant = ant->prox;
            }
        }
    }
    
    if(no2 != NULL){
        if(ant == NULL)
            *li1 = no2;
        else
            ant->prox = no2;
    }
    
    *li2 = NULL;
    return 1;
}

// Questão 9: Troca células adjacentes
int troca_celulas(Lista* li, struct elemento* p){
    if(li == NULL || p == NULL || p->prox == NULL)
        return 0;
    
    Elemento* proximo = p->prox;
    
    if(p == *li){
        *li = proximo;
        p->prox = proximo->prox;
        proximo->prox = p;
    } else {
        Elemento* ant = *li;
        while(ant != NULL && ant->prox != p){
            ant = ant->prox;
        }
        
        if(ant == NULL)
            return 0;
        
        ant->prox = proximo;
        p->prox = proximo->prox;
        proximo->prox = p;
    }
    
    return 1;
}