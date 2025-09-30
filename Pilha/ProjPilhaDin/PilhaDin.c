#include <stdio.h>
#include <stdlib.h>
#include "PilhaDin.h"

//Definição do tipo Pilha
// Cada elemento da pilha tem os dados do aluno e um ponteiro para o próximo
struct elemento{
    struct aluno dados;        // Os dados que queremos guardar
    struct elemento *prox;     // Ponteiro para o próximo elemento da pilha
};
typedef struct elemento Elem;  // Criamos um "apelido" para não escrever struct elemento toda hora

// Função para criar uma nova pilha vazia
Pilha* cria_Pilha(){
    // Aloca memória para o ponteiro que vai apontar para o topo da pilha
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)        // Se conseguiu alocar memória
        *pi = NULL;       // Inicializa como NULL (pilha vazia)
    return pi;            // Retorna o ponteiro para a pilha criada
}

// Função para liberar toda a memória da pilha
void libera_Pilha(Pilha* pi){
    if(pi != NULL){           // Se a pilha existe
        Elem* no;             // Variável auxiliar para guardar o elemento atual
        while((*pi) != NULL){ // Enquanto ainda tem elementos na pilha
            no = *pi;         // Guarda o elemento do topo
            *pi = (*pi)->prox; // Move o topo para o próximo elemento
            free(no);         // Libera a memória do elemento removido
        }
        free(pi);            // Libera a memória do ponteiro da pilha
    }
}

// Função para ver os dados do elemento que está no topo da pilha
int consulta_topo_Pilha(Pilha* pi, struct aluno *al){
    if(pi == NULL)        // Se a pilha não existe
        return 0;          // Retorna erro
    if((*pi) == NULL)      // Se a pilha está vazia
        return 0;          // Retorna erro
    *al = (*pi)->dados;    // Copia os dados do topo para a variável al
    return 1;              // Retorna sucesso
}

// Função para empilhar (adicionar) um elemento no topo da pilha
int insere_Pilha(Pilha* pi, struct aluno al){
    if(pi == NULL)                    // Se a pilha não existe
        return 0;                     // Retorna erro
    Elem* no;                         // Variável para o novo elemento
    no = (Elem*) malloc(sizeof(Elem)); // Aloca memória para o novo elemento
    if(no == NULL)                    // Se não conseguiu alocar memória
        return 0;                     // Retorna erro
    no->dados = al;                   // Coloca os dados do aluno no novo elemento
    no->prox = (*pi);                 // O novo elemento aponta para o antigo topo
    *pi = no;                         // O topo da pilha agora é o novo elemento
    return 1;                         // Retorna sucesso
}

// Função para desempilhar (remover) o elemento do topo da pilha
int remove_Pilha(Pilha* pi){
    if(pi == NULL)           // Se a pilha não existe
        return 0;            // Retorna erro
    if((*pi) == NULL)        // Se a pilha está vazia
        return 0;            // Retorna erro
    Elem *no = *pi;          // Guarda o elemento do topo
    *pi = no->prox;          // Move o topo para o próximo elemento
    free(no);                // Libera a memória do elemento removido
    return 1;                // Retorna sucesso
}

// Função para contar quantos elementos tem na pilha
int tamanho_Pilha(Pilha* pi){
    if(pi == NULL)        // Se a pilha não existe
        return 0;          // Retorna 0
    int cont = 0;         // Contador de elementos
    Elem* no = *pi;       // Começa pelo topo da pilha
    while(no != NULL){    // Enquanto tem elementos
        cont++;           // Conta mais um elemento
        no = no->prox;    // Vai para o próximo elemento
    }
    return cont;          // Retorna o total de elementos
}

// Função para verificar se a pilha está cheia (sempre retorna 0 porque pilha dinâmica nunca fica cheia)
int Pilha_cheia(Pilha* pi){
    return 0;  // Pilha dinâmica nunca fica cheia, sempre retorna 0 (não cheia)
}

// Função para verificar se a pilha está vazia
int Pilha_vazia(Pilha* pi){
    if(pi == NULL)        // Se a pilha não existe
        return 1;         // Considera vazia
    if(*pi == NULL)       // Se o topo aponta para NULL
        return 1;         // Pilha está vazia
    return 0;             // Pilha não está vazia
}

// Função para imprimir todos os elementos da pilha (do topo para baixo)
void imprime_Pilha(Pilha* pi){
    if(pi == NULL)        // Se a pilha não existe
        return;           // Sai da função
    Elem* no = *pi;       // Começa pelo topo da pilha
    while(no != NULL){    // Enquanto tem elementos
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %.2f %.2f %.2f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;     // Vai para o próximo elemento
    }
}

// QUESTÃO 1: pop2() - desempilha dois elementos do topo da pilha
int pop2(Pilha* pi){
    if(pi == NULL || (*pi) == NULL)  // Se pilha não existe ou está vazia
        return 0;                    // Retorna erro
    
    // Verifica se tem pelo menos 2 elementos na pilha
    if(tamanho_Pilha(pi) < 2)
        return 0;                    // Retorna erro se não tem 2 elementos
    
    // Remove o primeiro elemento (topo)
    Elem *no1 = *pi;                 // Guarda o elemento do topo
    *pi = no1->prox;                 // Move o topo para o próximo
    free(no1);                       // Libera a memória do primeiro
    
    // Remove o segundo elemento (que agora é o topo)
    Elem *no2 = *pi;                 // Guarda o novo elemento do topo
    *pi = no2->prox;                 // Move o topo para o próximo
    free(no2);                       // Libera a memória do segundo
    
    return 1;                        // Retorna sucesso
}

// QUESTÃO 1: push2() - empilha dois elementos no topo da pilha
int push2(Pilha* pi, struct aluno al1, struct aluno al2){
    if(pi == NULL)                    // Se pilha não existe
        return 0;                     // Retorna erro
    
    // Empilha o primeiro elemento
    Elem* no1 = (Elem*) malloc(sizeof(Elem)); // Aloca memória para o primeiro
    if(no1 == NULL)                   // Se não conseguiu alocar
        return 0;                     // Retorna erro
    no1->dados = al1;                 // Coloca os dados do primeiro aluno
    no1->prox = (*pi);                // Aponta para o antigo topo
    *pi = no1;                        // Atualiza o topo da pilha
    
    // Empilha o segundo elemento
    Elem* no2 = (Elem*) malloc(sizeof(Elem)); // Aloca memória para o segundo
    if(no2 == NULL)                   // Se não conseguiu alocar
        return 0;                     // Retorna erro
    no2->dados = al2;                 // Coloca os dados do segundo aluno
    no2->prox = (*pi);                // Aponta para o primeiro elemento
    *pi = no2;                        // Atualiza o topo da pilha
    
    return 1;                         // Retorna sucesso
}

// QUESTÃO 2: popN() - desempilha n elementos do topo da pilha
int popN(Pilha* pi, int n){
    if(pi == NULL || (*pi) == NULL || n <= 0)  // Se pilha não existe, vazia ou n inválido
        return 0;                              // Retorna erro
    
    int tam = tamanho_Pilha(pi);               // Conta quantos elementos tem na pilha
    if(n > tam)                                // Se quer remover mais do que tem
        return 0;                              // Retorna erro
    
    Elem *no;                                  // Variável auxiliar
    for(int i = 0; i < n; i++){                // Repete n vezes
        no = *pi;                              // Guarda o elemento do topo
        *pi = (*pi)->prox;                     // Move o topo para o próximo
        free(no);                              // Libera a memória do elemento removido
    }
    return 1;                                  // Retorna sucesso
}

// QUESTÃO 3: pilha_copia() - cria uma cópia da pilha sem alterar a original
Pilha* pilha_copia(Pilha* p){
    if(p == NULL || Pilha_vazia(p))  // Se pilha não existe ou está vazia
        return NULL;                 // Retorna NULL
    
    // Cria duas pilhas auxiliares para ajudar no processo
    Pilha* aux = cria_Pilha();      // Pilha auxiliar 1
    Pilha* copia = cria_Pilha();     // Pilha que será a cópia
    
    if(aux == NULL || copia == NULL) // Se não conseguiu criar as pilhas
        return NULL;                 // Retorna NULL
    
    // Primeiro: copia todos os elementos da pilha original para aux
    Elem* no = *p;                   // Começa pelo topo da pilha original
    while(no != NULL){               // Enquanto tem elementos
        insere_Pilha(aux, no->dados); // Empilha na auxiliar
        no = no->prox;               // Vai para o próximo
    }
    
    // Segundo: transfere de aux para copia (mantém a ordem original)
    while(!Pilha_vazia(aux)){        // Enquanto aux não está vazia
        struct aluno al;             // Variável para guardar os dados
        consulta_topo_Pilha(aux, &al); // Pega o topo de aux
        insere_Pilha(copia, al);     // Empilha na cópia
        remove_Pilha(aux);           // Remove de aux
    }
    
    // Terceiro: restaura a pilha original (desempilha de copia e empilha de volta em p)
    while(!Pilha_vazia(copia)){      // Enquanto copia não está vazia
        struct aluno al;             // Variável para guardar os dados
        consulta_topo_Pilha(copia, &al); // Pega o topo de copia
        insere_Pilha(p, al);         // Empilha de volta na original
        remove_Pilha(copia);         // Remove de copia
    }
    
    // Quarto: agora copia tem os elementos na ordem correta
    while(!Pilha_vazia(aux)){        // Enquanto aux não está vazia
        struct aluno al;             // Variável para guardar os dados
        consulta_topo_Pilha(aux, &al); // Pega o topo de aux
        insere_Pilha(copia, al);     // Empilha na cópia final
        remove_Pilha(aux);           // Remove de aux
    }
    
    libera_Pilha(aux);               // Libera a memória da auxiliar
    return copia;                    // Retorna a cópia criada
}

// QUESTÃO 4: maior_menor_media() - encontra o maior, menor e média dos elementos
void maior_menor_media(Pilha* pi, int* maior, int* menor, float* media){
    if(pi == NULL || Pilha_vazia(pi)){  // Se pilha não existe ou está vazia
        printf("Pilha vazia ou nao inicializada.\n");
        return;                         // Sai da função
    }
    
    int soma = 0;                       // Variável para somar todos os valores
    int count = 0;                      // Contador de elementos
    
    Elem* no = *pi;                     // Começa pelo topo da pilha
    *maior = no->dados.matricula;       // Inicializa maior com o primeiro elemento
    *menor = no->dados.matricula;       // Inicializa menor com o primeiro elemento
    
    while(no != NULL){                  // Enquanto tem elementos na pilha
        int valor = no->dados.matricula; // Pega a matrícula do elemento atual
        soma += valor;                  // Soma o valor
        count++;                       // Conta mais um elemento
        
        if(valor > *maior)              // Se o valor é maior que o maior atual
            *maior = valor;             // Atualiza o maior
        if(valor < *menor)              // Se o valor é menor que o menor atual
            *menor = valor;             // Atualiza o menor
        
        no = no->prox;                  // Vai para o próximo elemento
    }
    
    *media = (float)soma / count;       // Calcula a média (soma dividida pela quantidade)
}

// QUESTÃO 5: pilhas_iguais() - verifica se duas pilhas são iguais
int pilhas_iguais(Pilha* p1, Pilha* p2){
    if(p1 == NULL || p2 == NULL)  // Se alguma pilha não existe
        return 0;                 // Retorna 0 (não são iguais)
    
    int tam1 = tamanho_Pilha(p1); // Conta elementos da primeira pilha
    int tam2 = tamanho_Pilha(p2); // Conta elementos da segunda pilha
    
    if(tam1 != tam2)              // Se têm tamanhos diferentes
        return 0;                 // Retorna 0 (não são iguais)
    
    Elem* no1 = *p1;              // Ponteiro para o topo da primeira pilha
    Elem* no2 = *p2;              // Ponteiro para o topo da segunda pilha
    
    while(no1 != NULL && no2 != NULL){ // Enquanto ambas têm elementos
        if(no1->dados.matricula != no2->dados.matricula) // Se as matrículas são diferentes
            return 0;             // Retorna 0 (não são iguais)
        no1 = no1->prox;          // Vai para o próximo da primeira
        no2 = no2->prox;          // Vai para o próximo da segunda
    }
    
    return 1;                     // Se chegou até aqui, são iguais
}

// QUESTÃO 6: texto_inverso() - imprime um texto na ordem inversa usando pilha
void texto_inverso(){
    char texto[100];                    // Array para guardar o texto digitado
    printf("Digite um texto: ");       // Pede para o usuário digitar
    fgets(texto, sizeof(texto), stdin); // Lê o texto (com quebra de linha)
    
    // Remove a quebra de linha do final do texto
    char *p = texto;                    // Ponteiro para o início do texto
    while(*p != '\0' && *p != '\n'){ // Enquanto não chegou no final ou quebra de linha
        p++;                           // Avança o ponteiro
    }
    *p = '\0';                        // Coloca \0 no lugar da quebra de linha
    
    Pilha* pi = cria_Pilha();          // Cria uma pilha vazia
    struct aluno temp;                 // Variável temporária para guardar cada caractere
    
    // Empilha cada caractere do texto
    p = texto;                         // Volta o ponteiro para o início
    while(*p != '\0'){                // Enquanto não chegou no final
        temp.nome[0] = *p;             // Coloca o caractere na posição 0
        temp.nome[1] = '\0';          // Coloca \0 na posição 1 (fim da string)
        insere_Pilha(pi, temp);       // Empilha o caractere
        p++;                           // Avança para o próximo caractere
    }
    
    printf("Texto na ordem inversa: "); // Imprime a mensagem
    Elem* no = *pi;                    // Começa pelo topo da pilha
    while(no != NULL){                 // Enquanto tem elementos na pilha
        printf("%c", no->dados.nome[0]); // Imprime o caractere do topo
        no = no->prox;                 // Vai para o próximo elemento
    }
    printf("\n");                      // Pula uma linha
    
    libera_Pilha(pi);                 // Libera a memória da pilha
}

// Função auxiliar para converter letra maiúscula para minúscula
char to_lower(char c){
    if(c >= 'A' && c <= 'Z')  // Se é uma letra maiúscula
        return c + 32;           // Converte para minúscula (A=65, a=97, diferença=32)
    return c;                    // Se não é maiúscula, retorna como está
}

// QUESTÃO 6: verifica_palindromo() - verifica se um texto é palíndromo (lê igual de trás para frente)
int verifica_palindromo(char* texto){
    Pilha* pi = cria_Pilha();        // Cria uma pilha vazia
    struct aluno temp;               // Variável temporária para guardar cada letra
    
    // Primeiro: empilha apenas as letras (ignora espaços, pontos, etc.)
    char *p = texto;                 // Ponteiro para o início do texto
    while(*p != '\0'){             // Enquanto não chegou no final
        char c = *p;                 // Pega o caractere atual
        if(c != ' ' && c != '.' && c != ',' && c != '!' && c != '?'){ // Se é uma letra
            temp.nome[0] = to_lower(c); // Converte para minúscula e coloca na temp
            temp.nome[1] = '\0';      // Coloca \0 no final
            insere_Pilha(pi, temp);  // Empilha a letra
        }
        p++;                         // Avança para o próximo caractere
    }
    
    // Segundo: compara com o texto original (lendo de frente para trás)
    p = texto;                       // Volta o ponteiro para o início
    Elem* no = *pi;                  // Começa pelo topo da pilha (que tem as letras de trás para frente)
    while(no != NULL && *p != '\0'){ // Enquanto tem elementos na pilha e texto
        char c = to_lower(*p);       // Pega o caractere do texto e converte para minúscula
        if(c != ' ' && c != '.' && c != ',' && c != '!' && c != '?'){ // Se é uma letra
            if(c != no->dados.nome[0]){ // Se a letra do texto é diferente da letra da pilha
                libera_Pilha(pi);    // Libera a memória
                return 0;            // Retorna 0 (não é palíndromo)
            }
            no = no->prox;          // Vai para o próximo elemento da pilha
        }
        p++;                         // Avança para o próximo caractere do texto
    }
    
    libera_Pilha(pi);               // Libera a memória da pilha
    return 1;                       // Retorna 1 (é palíndromo)
}

// QUESTÃO 7: conta pares e ímpares
void conta_pares_impares(Pilha* pi, int* pares, int* impares){
    *pares = 0;
    *impares = 0;
    
    if(pi == NULL || Pilha_vazia(pi))
        return;
    
    Elem* no = *pi;
    while(no != NULL){
        if(no->dados.matricula % 2 == 0)
            (*pares)++;
        else
            (*impares)++;
        no = no->prox;
    }
}

// QUESTÃO 8: verifica cadeia xCy
int verifica_cadeia_xCy(char* texto){
    Pilha* pi = cria_Pilha();
    struct aluno temp;
    char *p = texto;
    
    // Primeira passada: empilha até encontrar 'C'
    while(*p != '\0' && *p != 'C'){
        if(*p == 'A' || *p == 'B'){
            temp.nome[0] = *p;
            temp.nome[1] = '\0';
            insere_Pilha(pi, temp);
        }
        p++;
    }
    
    if(*p != 'C'){
        libera_Pilha(pi);
        return 0;
    }
    
    p++; // Pula o 'C'
    
    // Segunda passada: compara com o inverso
    Elem* no = *pi;
    while(no != NULL && *p != '\0'){
        if(*p != no->dados.nome[0]){
            libera_Pilha(pi);
            return 0;
        }
        no = no->prox;
        p++;
    }
    
    int resultado = (no == NULL && *p == '\0');
    libera_Pilha(pi);
    return resultado;
}

// QUESTÃO 9: menu
void menu(){
    printf("1-Inicializa pilha.\n");
        printf("2-Verifica se a pilha e vazia.\n");
        printf("3-Verifica se a pilha e cheia.\n");
        printf("4-Empilha o elemento na pilha.\n");
        printf("5-Desempilha elemento da pilha.\n");
        printf("6-Le topo de um pilha.\n");
        printf("7-Converte um numero decimal em binario.\n");
        printf("8-Sair.\n");
}

void menu_principal(){
    Pilha* pi = NULL;
    int opcao;
    struct aluno al;
    
    while(1){
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(pi != NULL)
                    libera_Pilha(pi);
                pi = cria_Pilha();
                printf("Pilha inicializada!\n");
                break;
                
            case 2:
                if(pi == NULL)
                    printf("Pilha nao inicializada!\n");
                else if(Pilha_vazia(pi))
                    printf("Pilha esta vazia!\n");
                else
                    printf("Pilha nao esta vazia!\n");
                break;
                
            case 3:
                if(pi == NULL)
                    printf("Pilha nao inicializada!\n");
                else if(Pilha_cheia(pi))
                    printf("Pilha esta cheia!\n");
                else
                    printf("Pilha nao esta cheia!\n");
                break;
                
            case 4:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                printf("Digite matricula: ");
                scanf("%d", &al.matricula);
                printf("Digite nome: ");
                scanf("%s", al.nome);
                printf("Digite nota 1: ");
                scanf("%f", &al.n1);
                printf("Digite nota 2: ");
                scanf("%f", &al.n2);
                printf("Digite nota 3: ");
                scanf("%f", &al.n3);
                
                if(insere_Pilha(pi, al))
                    printf("Elemento empilhado com sucesso!\n");
                else
                    printf("Erro ao empilhar!\n");
                break;
                
            case 5:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                if(remove_Pilha(pi))
                    printf("Elemento desempilhado com sucesso!\n");
                else
                    printf("Erro ao desempilhar!\n");
                break;
                
            case 6:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                if(consulta_topo_Pilha(pi, &al)){
                    printf("Topo da pilha:\n");
                    printf("Matricula: %d\n", al.matricula);
                    printf("Nome: %s\n", al.nome);
                    printf("Notas: %.2f %.2f %.2f\n", al.n1, al.n2, al.n3);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;
                
            case 7:
                if(pi == NULL){
                    printf("Pilha nao inicializada!\n");
                    break;
                }
                printf("Pilha em binario:\n");
                Elem* no = *pi;
                while(no != NULL){
                    printf("Matricula %d em binario: ", no->dados.matricula);
                    int num = no->dados.matricula;
                    if(num == 0){
                        printf("0");
                    } else {
                        Pilha* bin = cria_Pilha();
                        struct aluno bit;
                        while(num > 0){
                            bit.matricula = num % 2;
                            insere_Pilha(bin, bit);
                            num /= 2;
                        }
                        Elem* b = *bin;
                        while(b != NULL){
                            printf("%d", b->dados.matricula);
                            b = b->prox;
                        }
                        libera_Pilha(bin);
                    }
                    printf("\n");
                    no = no->prox;
                }
                break;
                
            case 8:
                if(pi != NULL)
                    libera_Pilha(pi);
                printf("Saindo...\n");
                return;
                
            default:
                printf("Opcao invalida!\n");
        }
        printf("\n");
    }
}