#include <stdio.h>
#include <stdlib.h>
#include "FilaDin.h" //inclui os Prot�tipos
//Defini��o do tipo Fila
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;
//Defini��o do N� Descritor da Fila
struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

Fila* cria_Fila(){
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if(fi != NULL){
        fi->final = NULL;
        fi->inicio = NULL;
        fi->qtd = 0;
    }
    return fi;
}

void libera_Fila(Fila* fi){
    if(fi != NULL){
        Elem* no;
        while(fi->inicio != NULL){
            no = fi->inicio;
            fi->inicio = fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int consulta_Fila(Fila* fi, struct aluno *al){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    *al = fi->inicio->dados;
    return 1;
}

int insere_Fila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if(fi->final == NULL)//fila vazia
        fi->inicio = no;
    else
        fi->final->prox = no;
    fi->final = no;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    if(fi->inicio == NULL)//fila vazia
        return 0;
    Elem *no = fi->inicio;
    fi->inicio = fi->inicio->prox;
    if(fi->inicio == NULL)//fila ficou vazia
        fi->final = NULL;
    free(no);
    fi->qtd--;
    return 1;
}

int tamanho_Fila(Fila* fi){
    if(fi == NULL)
        return 0;
    return fi->qtd;
}

int Fila_vazia(Fila* fi){
    if(fi == NULL)
        return 1;
    if(fi->inicio == NULL)
        return 1;
    return 0;
}

int Fila_cheia(Fila* fi){
    return 0;
}

void imprime_Fila(Fila* fi){
    if(fi == NULL)
        return;
    Elem* no = fi->inicio;
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

// QUESTÃO 1 - Função separa
// Essa função divide uma fila em duas baseada na primeira ocorrência de uma matrícula
// A ideia é: se eu tenho uma fila [A, B, C, D] e quero separar no elemento C,
// fico com f1=[A, B] e f2=[C, D]
int separa(Fila* f1, Fila* f2, int matricula){
    // Primeiro verifico se as filas existem
    if(f1 == NULL || f2 == NULL)
        return 0;
    
    // Vou percorrer a fila procurando a matrícula
    Elem* no = f1->inicio;
    Elem* anterior = NULL; // Preciso guardar o nó anterior para poder "cortar" a fila
    int encontrou = 0;
    
    // Procura a primeira ocorrência da matrícula
    while(no != NULL && !encontrou){
        if(no->dados.matricula == matricula){
            encontrou = 1; // Achei!
        } else {
            anterior = no; // Guardo o nó anterior
            no = no->prox; // Vou para o próximo
        }
    }
    
    // Se não encontrou a matrícula, retorna 0
    if(!encontrou)
        return 0;
    
    // Agora preciso "cortar" a fila no ponto encontrado
    if(anterior == NULL){
        // Se anterior é NULL, significa que a matrícula está no primeiro elemento
        // Então toda a fila f1 vai para f2, e f1 fica vazia
        f2->inicio = f1->inicio;
        f2->final = f1->final;
        f2->qtd = f1->qtd;
        f1->inicio = NULL;
        f1->final = NULL;
        f1->qtd = 0;
    } else {
        // A matrícula está no meio ou final da fila
        // f2 vai receber do ponto encontrado até o final
        f2->inicio = no;
        f2->final = f1->final;
        f2->qtd = 0;
        
        // Conto quantos elementos vão para f2
        Elem* temp = no;
        while(temp != NULL){
            f2->qtd++;
            temp = temp->prox;
        }
        
        // Atualizo f1: corto a ligação e atualizo o final
        anterior->prox = NULL; // Aqui eu "corto" a fila
        f1->final = anterior; // O novo final de f1 é o anterior
        f1->qtd -= f2->qtd; // Atualizo a quantidade
    }
    
    return 1; // Sucesso!
}

// QUESTÃO 3 - Inverter fila com pilha
// A ideia aqui é usar uma pilha como intermediária para inverter a fila
// Fila: [A, B, C] -> Pilha: [C, B, A] -> Fila: [C, B, A]
// A pilha inverte automaticamente a ordem!
void inverte_Fila(Fila* fi){
    if(fi == NULL || fi->inicio == NULL)
        return;
    
    // Vou usar a mesma estrutura Elem para criar uma pilha temporária
    // Pilha é LIFO (Last In, First Out), então vai inverter a ordem
    Elem* pilha = NULL; // Topo da pilha
    struct aluno al;
    
    // Primeiro passo: desenfileira todos os elementos e empilha
    // Se a fila tem [A, B, C], vou empilhar A, depois B, depois C
    // Na pilha fica: C (topo), B, A (base)
    while(!Fila_vazia(fi)){
        consulta_Fila(fi, &al); // Pego o primeiro da fila
        remove_Fila(fi); // Removo da fila
        
        // Empilho na pilha temporária
        Elem* novo = (Elem*) malloc(sizeof(Elem));
        novo->dados = al;
        novo->prox = pilha; // O novo elemento aponta para o topo atual
        pilha = novo; // Atualizo o topo da pilha
    }
    
    // Segundo passo: desempilha todos os elementos e enfileira
    // Agora vou tirar da pilha na ordem C, B, A e colocar na fila
    // Resultado: fila fica [C, B, A] - invertida!
    while(pilha != NULL){
        al = pilha->dados; // Pego o topo da pilha
        insere_Fila(fi, al); // Coloco na fila
        
        // Removo da pilha
        Elem* temp = pilha;
        pilha = pilha->prox;
        free(temp);
    }
}

// QUESTÃO 4 - Fura fila
// Essa função "fura" a fila, ou seja, coloca um elemento no início
// Isso quebra a regra FIFO (First In, First Out) da fila
// Mas às vezes é necessário, tipo quando alguém tem prioridade
int FuraFila(Fila* fi, struct aluno al){
    if(fi == NULL)
        return 0;
    
    // Crio um novo nó com o elemento
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    if(novo == NULL)
        return 0;
    
    novo->dados = al;
    // O novo nó vai apontar para o atual início da fila
    novo->prox = fi->inicio;
    // O novo nó se torna o novo início
    fi->inicio = novo;
    
    // Se a fila estava vazia, o novo nó também é o final
    if(fi->final == NULL)
        fi->final = novo;
    
    fi->qtd++; // Incremento a quantidade
    return 1;
}

// QUESTÃO 5 - Controle de aeroporto
// Aqui simulo um sistema de controle de aeroporto usando a fila
// Cada avião entra na fila e sai na ordem de chegada (FIFO)
void adiciona_Aviao(Fila* fi, int id, char modelo[], char companhia[]){
    // Como não tenho uma estrutura específica para avião,
    // vou adaptar a estrutura aluno existente
    struct aluno al;
    al.matricula = id; // ID do avião
    strcpy(al.nome, modelo); // Modelo do avião
    al.n1 = 0; al.n2 = 0; al.n3 = 0; // Limpo as notas
    al.n1 = 1; // Uso n1 como prioridade (1 = normal)
    
    // Simplesmente enfileiro o avião
    insere_Fila(fi, al);
}

void autoriza_Decolagem(Fila* fi){
    // O primeiro avião da fila pode decolar
    if(!Fila_vazia(fi)){
        remove_Fila(fi); // Remove o primeiro da fila
        printf("Decolagem autorizada!\n");
    } else {
        printf("Nenhum aviao na fila.\n");
    }
}

void lista_Avioes(Fila* fi){
    // Lista todos os aviões na fila de espera
    if(Fila_vazia(fi)){
        printf("Nenhum aviao na fila.\n");
        return;
    }
    
    Elem* no = fi->inicio;
    int cont = 1;
    while(no != NULL){
        printf("Aviao %d: ID %d - %s (%s)\n", cont, no->dados.matricula, 
               no->dados.nome, "Companhia");
        no = no->prox;
        cont++;
    }
}

void lista_PrimeiroAviao(Fila* fi){
    // Mostra apenas o primeiro avião da fila (próximo a decolar)
    if(Fila_vazia(fi)){
        printf("Nenhum aviao na fila.\n");
        return;
    }
    
    struct aluno al;
    consulta_Fila(fi, &al); // Consulta sem remover
    printf("Primeiro aviao: ID %d - %s\n", al.matricula, al.nome);
}

// QUESTÃO 6 - Mesclar filas ordenadas
// Essa função pega duas filas já ordenadas e mescla em uma terceira fila
// É tipo o merge do merge sort, mas com filas
// Exemplo: f1=[1,3,5] e f2=[2,4,6] -> f3=[1,2,3,4,5,6]
void mescla_FilasOrdenadas(Fila* f1, Fila* f2, Fila* f3){
    if(f1 == NULL || f2 == NULL || f3 == NULL)
        return;
    
    struct aluno al1, al2;
    // Vou consultar o primeiro elemento de cada fila sem remover
    int tem1 = consulta_Fila(f1, &al1);
    int tem2 = consulta_Fila(f2, &al2);
    
    // Enquanto tiver elementos em pelo menos uma das filas
    while(tem1 || tem2){
        if(tem1 && tem2){
            // Ambas as filas têm elementos, comparo qual é menor
            if(al1.matricula <= al2.matricula){
                // f1 tem o menor, coloco ele na f3
                remove_Fila(f1);
                insere_Fila(f3, al1);
                tem1 = consulta_Fila(f1, &al1); // Consulto o próximo de f1
            } else {
                // f2 tem o menor, coloco ele na f3
                remove_Fila(f2);
                insere_Fila(f3, al2);
                tem2 = consulta_Fila(f2, &al2); // Consulto o próximo de f2
            }
        } else if(tem1){
            // Só f1 tem elementos, coloco todos na f3
            remove_Fila(f1);
            insere_Fila(f3, al1);
            tem1 = consulta_Fila(f1, &al1);
        } else {
            // Só f2 tem elementos, coloco todos na f3
            remove_Fila(f2);
            insere_Fila(f3, al2);
            tem2 = consulta_Fila(f2, &al2);
        }
    }
}

// QUESTÃO 7 - Reverso
// Aqui eu vou inverter a fila diretamente, sem usar pilha
// A ideia é inverter os ponteiros: o que apontava para frente, agora aponta para trás
// É tipo virar uma lista de cabeça para baixo
void reverso(Fila* fi){
    if(fi == NULL || fi->inicio == NULL)
        return;
    
    // Vou usar três ponteiros para inverter a lista
    Elem* anterior = NULL; // Começo com NULL
    Elem* atual = fi->inicio; // Começo do primeiro elemento
    Elem* proximo = NULL; // Vou descobrir o próximo
    
    // Percorro a lista invertendo os ponteiros
    while(atual != NULL){
        proximo = atual->prox; // Guardo o próximo antes de inverter
        atual->prox = anterior; // Inverto: agora aponta para o anterior
        anterior = atual; // O atual vira o anterior
        atual = proximo; // Vou para o próximo
    }
    
    // Agora preciso atualizar os ponteiros da fila
    fi->final = fi->inicio; // O que era início vira final
    fi->inicio = anterior; // O último elemento vira início
}

// QUESTÃO 8 - Menu
// Menu interativo para testar todas as funcionalidades da fila
void menu(){
    printf("1-Inicializa fila.\n");
    printf("2-Verifica se a fila e vazia.\n");
    printf("3-Verifica se a fila e cheia.\n");
    printf("4-Enfileira o elemento na fila.\n");
    printf("5-Desefileira elemento da fila.\n");
    printf("6-Le o numero no inicio da fila.\n");
    printf("7-Testar qual fila possui mais elementos .\n");
    printf("8-Furar a fila .\n");
    printf("9-Sair.\n");
}

void executa_Menu(){
    Fila* fi = NULL;
    Fila* fi2 = NULL;
    int opcao;
    struct aluno al;
    
    do{
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                if(fi != NULL)
                    libera_Fila(fi);
                fi = cria_Fila();
                printf("Fila inicializada.\n");
                break;
                
            case 2:
                if(fi == NULL)
                    printf("Fila nao foi inicializada.\n");
                else if(Fila_vazia(fi))
                    printf("Fila esta vazia.\n");
                else
                    printf("Fila nao esta vazia.\n");
                break;
                
            case 3:
                if(fi == NULL)
                    printf("Fila nao foi inicializada.\n");
                else if(Fila_cheia(fi))
                    printf("Fila esta cheia.\n");
                else
                    printf("Fila nao esta cheia.\n");
                break;
                
            case 4:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                printf("Digite a matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite o nome: ");
                scanf("%s", al.nome);
                printf("Digite as 3 notas: ");
                scanf("%f %f %f", &al.n1, &al.n2, &al.n3);
                
                if(insere_Fila(fi, al))
                    printf("Elemento inserido com sucesso.\n");
                else
                    printf("Erro ao inserir elemento.\n");
                break;
                
            case 5:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                if(remove_Fila(fi))
                    printf("Elemento removido com sucesso.\n");
                else
                    printf("Erro ao remover elemento.\n");
                break;
                
            case 6:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                if(consulta_Fila(fi, &al))
                    printf("Primeiro elemento: Matricula %d, Nome %s\n", al.matricula, al.nome);
                else
                    printf("Fila vazia.\n");
                break;
                
            case 7:
                if(fi == NULL){
                    printf("Primeira fila nao foi inicializada.\n");
                    break;
                }
                if(fi2 == NULL){
                    fi2 = cria_Fila();
                    printf("Segunda fila criada. Adicione elementos a ela.\n");
                }
                printf("Fila 1 tem %d elementos.\n", tamanho_Fila(fi));
                printf("Fila 2 tem %d elementos.\n", tamanho_Fila(fi2));
                if(tamanho_Fila(fi) > tamanho_Fila(fi2))
                    printf("Fila 1 tem mais elementos.\n");
                else if(tamanho_Fila(fi2) > tamanho_Fila(fi))
                    printf("Fila 2 tem mais elementos.\n");
                else
                    printf("As filas tem o mesmo numero de elementos.\n");
                break;
                
            case 8:
                if(fi == NULL){
                    printf("Fila nao foi inicializada.\n");
                    break;
                }
                printf("Digite a matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite o nome: ");
                scanf("%s", al.nome);
                printf("Digite as 3 notas: ");
                scanf("%f %f %f", &al.n1, &al.n2, &al.n3);
                
                if(FuraFila(fi, al))
                    printf("Elemento inserido no inicio da fila.\n");
                else
                    printf("Erro ao inserir elemento.\n");
                break;
                
            case 9:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opcao invalida.\n");
        }
        
        if(opcao != 9){
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while(opcao != 9);
    
    if(fi != NULL)
        libera_Fila(fi);
    if(fi2 != NULL)
        libera_Fila(fi2);
}