//Arquivo FilaDin.h
struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct fila Fila;

// Funções básicas da fila
Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int tamanho_Fila(Fila* fi);
int Fila_vazia(Fila* fi);
int Fila_cheia(Fila* fi);
void imprime_Fila(Fila* fi);

// Questão 1 - Função separa
int separa(Fila* f1, Fila* f2, int matricula);

// Questão 3 - Inverter fila com pilha
void inverte_Fila(Fila* fi);

// Questão 4 - Fura fila
int FuraFila(Fila* fi, struct aluno al);

// Questão 5 - Controle de aeroporto
void adiciona_Aviao(Fila* fi, int id, char modelo[], char companhia[]);
void autoriza_Decolagem(Fila* fi);
void lista_Avioes(Fila* fi);
void lista_PrimeiroAviao(Fila* fi);

// Questão 6 - Mesclar filas ordenadas
void mescla_FilasOrdenadas(Fila* f1, Fila* f2, Fila* f3);

// Questão 7 - Reverso
void reverso(Fila* fi);

// Questão 8 - Menu
void menu();
void executa_Menu();


