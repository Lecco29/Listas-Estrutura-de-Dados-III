//Arquivo PilhaDin.h

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct elemento* Pilha;

// Funções básicas da pilha
Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int consulta_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int tamanho_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);
int Pilha_cheia(Pilha* pi);
void imprime_Pilha(Pilha* pi);

// Questão 1: pop2() e push2()
int pop2(Pilha* pi);
int push2(Pilha* pi, struct aluno al1, struct aluno al2);

// Questão 2: popN()
int popN(Pilha* pi, int n);

// Questão 3: pilha_copia()
Pilha* pilha_copia(Pilha* p);

// Questão 4: maior, menor e média
void maior_menor_media(Pilha* pi, int* maior, int* menor, float* media);

// Questão 5: pilhas iguais
int pilhas_iguais(Pilha* p1, Pilha* p2);

// Questão 6: texto inverso e palíndromo
void texto_inverso();
int verifica_palindromo(char* texto);

// Questão 7: elementos pares e ímpares
void conta_pares_impares(Pilha* pi, int* pares, int* impares);

// Questão 8: cadeia xCy
int verifica_cadeia_xCy(char* texto);

// Questão 9: menu
void menu();
void menu_principal();
