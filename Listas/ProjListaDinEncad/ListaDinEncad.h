//Arquivo ListaDinEncad.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int insere_lista_inicio(Lista* li, struct aluno al);
int insere_lista_ordenada(Lista* li, struct aluno al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li);

// Novas funções solicitadas
struct aluno consulta_lista_matricula(Lista* li, int mat);
struct aluno consulta_lista_posicao(Lista* li, int pos);
int remove_lista_recursiva(Lista* li, int valor);
int listas_iguais_recursiva(Lista* li1, Lista* li2);
int insere_lista_posicao(Lista* li, struct aluno al, int pos);
Lista* constroi_lista_vetor(float* vetor, int tamanho);
int remove_todos_valor(Lista* li, int valor);
int concatena_listas(Lista* li1, Lista* li2);
int remove_repetidos(Lista* li);
int fusao_listas_ordenadas(Lista* li1, Lista* li2);
int troca_celulas(Lista* li, struct elemento* p);

