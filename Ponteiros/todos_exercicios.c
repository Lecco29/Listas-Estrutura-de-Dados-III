#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================================
// QUESTAO 1: DIFERENCAS ENTRE OPERACOES COM PONTEIROS
// ============================================================================
void questao1() {
    printf("=== QUESTAO 1: DIFERENCAS ENTRE OPERACOES COM PONTEIROS ===\n\n");
    
    int vetor[] = {10, 20, 30, 40, 50};
    int *p = vetor; // p aponta para o primeiro elemento do vetor
    
    printf("Vetor inicial: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n\n");
    
    // Explicando cada operação:
    printf("1) p++ - Incrementa o ponteiro (aponta para o proximo elemento)\n");
    printf("   Antes: p aponta para vetor[0] = %d\n", *p);
    p++;
    printf("   Depois: p aponta para vetor[1] = %d\n\n", *p);
    
    printf("2) (*p)++ - Incrementa o valor apontado pelo ponteiro\n");
    printf("   Antes: *p = %d\n", *p);
    (*p)++;
    printf("   Depois: *p = %d\n", *p);
    printf("   Vetor agora: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n\n");
    
    printf("3) *(p++) - Acessa o valor atual e depois incrementa o ponteiro\n");
    printf("   Valor atual: %d\n", *(p++));
    printf("   Ponteiro agora aponta para: %d\n\n", *p);
    
    printf("4) *(p+10) - Acessa o valor que esta 10 posicoes a frente\n");
    printf("   *(p+10) = %d (valor invalido, fora do vetor)\n", *(p+10));
    printf("   *(p+2) = %d (terceiro elemento a frente)\n\n", *(p+2));
}

// ============================================================================
// QUESTAO 2: COMENTARIOS EM CODIGO COM PONTEIROS
// ============================================================================
void questao2() {
    printf("=== QUESTAO 2: COMENTARIOS EM CODIGO COM PONTEIROS ===\n\n");
    
    int y, *p, x;
    
    y = 0;          // Atribui o valor 0 para a variavel y
    printf("y = %d (y recebe o valor 0)\n", y);
    
    p = &y;         // p recebe o endereco da variavel y (p aponta para y)
    printf("p = %p (p recebe o endereco de y)\n", p);
    
    x = *p;         // x recebe o valor apontado por p (que e o valor de y)
    printf("x = %d (x recebe o valor apontado por p, que e y)\n", x);
    
    x = 4;          // x recebe o valor 4
    printf("x = %d (x recebe o valor 4)\n", x);
    
    (*p)++;         // Incrementa o valor apontado por p (incrementa y)
    printf("y = %d (y foi incrementado via ponteiro)\n", y);
    
    x--;            // Decrementa x
    printf("x = %d (x foi decrementado)\n", x);
    
    (*p) += x;      // Soma x ao valor apontado por p (soma x a y)
    printf("y = %d (y recebeu y + x)\n", y);
    
    printf("\nResultado final: y = %d\n", y);
}

// ============================================================================
// QUESTAO 3: CORRIGIR PROGRAMA COM PONTEIROS
// ============================================================================
void questao3() {
    printf("=== QUESTAO 3: CORRIGIR PROGRAMA COM PONTEIROS ===\n\n");
    
    int x, *p, **q;
    
    x = 10;         // x recebe o valor 10
    p = &x;         // p aponta para x
    q = &p;         // q aponta para p (ponteiro para ponteiro)
    
    printf("Programa original (com erro):\n");
    printf("printf(\"\\n%%d\\n\", &q); // ERRO: imprime endereco de q\n");
    printf("Resultado: %p\n\n", &q);
    
    printf("Programa corrigido:\n");
    printf("printf(\"\\n%%d\\n\", **q); // CORRETO: imprime valor de x\n");
    printf("Resultado: %d\n", **q);
    
    printf("\nExplicacao:\n");
    printf("- q e um ponteiro para ponteiro\n");
    printf("- *q acessa o valor de p (que e o endereco de x)\n");
    printf("- **q acessa o valor de x (que e 10)\n");
    printf("- &q imprime o endereco da variavel q, nao o valor\n");
}

// ============================================================================
// QUESTAO 4: ALOCACAO DINAMICA DE VETOR
// ============================================================================
void questao4() {
    printf("=== QUESTAO 4: ALOCACAO DINAMICA DE VETOR ===\n\n");
    
    int n;
    int *V;
    
    // Solicita o tamanho do vetor ao usuario
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    
    // Verifica se n e valido
    if(n <= 0) {
        printf("Erro: Tamanho invalido!\n");
        return;
    }
    
    // Aloca memoria para o vetor
    V = (int*) malloc(n * sizeof(int));
    
    // Verifica se a alocacao foi bem sucedida
    if(V == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return;
    }
    
    printf("Vetor alocado com sucesso!\n");
    printf("Tamanho: %d elementos\n", n);
    printf("Memoria alocada: %d bytes\n", n * sizeof(int));
    
    // Preenche o vetor com valores de exemplo
    printf("\nPreenchendo o vetor com valores de 1 a %d:\n", n);
    for(int i = 0; i < n; i++) {
        V[i] = i + 1;
        printf("V[%d] = %d\n", i, V[i]);
    }
    
    // Libera a memoria alocada
    free(V);
    printf("\nMemoria liberada com sucesso!\n");
}

// ============================================================================
// QUESTAO 5: FUNCAO INVERTE_VETOR
// ============================================================================
int inverte_vetor(int *v1, int *v2, int n) {
    int maior = v1[0]; // Inicializa com o primeiro elemento
    
    // Copia elementos de v1 para v2 na ordem inversa
    for(int i = 0; i < n; i++) {
        v2[i] = v1[n-1-i]; // v2[0] = v1[n-1], v2[1] = v1[n-2], etc.
        
        // Encontra o maior valor em v1
        if(v1[i] > maior) {
            maior = v1[i];
        }
    }
    
    return maior;
}

void questao5() {
    printf("=== QUESTAO 5: FUNCAO INVERTE_VETOR ===\n\n");
    
    int n;
    int *v1, *v2;
    
    // Solicita o tamanho dos vetores
    printf("Digite o tamanho dos vetores: ");
    scanf("%d", &n);
    
    if(n <= 0) {
        printf("Erro: Tamanho invalido!\n");
        return;
    }
    
    // Aloca memoria para os vetores
    v1 = (int*) malloc(n * sizeof(int));
    v2 = (int*) malloc(n * sizeof(int));
    
    if(v1 == NULL || v2 == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return;
    }
    
    // Preenche v1 com valores do usuario
    printf("Digite os %d elementos do vetor V1:\n", n);
    for(int i = 0; i < n; i++) {
        printf("V1[%d] = ", i);
        scanf("%d", &v1[i]);
    }
    
    // Chama a funcao inverte_vetor
    int maior = inverte_vetor(v1, v2, n);
    
    // Exibe os resultados
    printf("\nVetor V1 original: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", v1[i]);
    }
    
    printf("\nVetor V2 invertido: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", v2[i]);
    }
    
    printf("\nMaior valor em V1: %d\n", maior);
    
    // Libera a memoria
    free(v1);
    free(v2);
}

// ============================================================================
// QUESTAO 6: IMPRIMIR STRING NA ORDEM INVERSA
// ============================================================================
void questao6() {
    printf("=== QUESTAO 6: IMPRIMIR STRING NA ORDEM INVERSA ===\n\n");
    
    char s[10] = "abcde";
    char* cptr;
    
    printf("String original: %s\n", s);
    printf("String na ordem inversa: ");
    
    // Encontra o final da string
    cptr = s;
    while(*cptr != '\0') {
        cptr++;
    }
    
    // Volta uma posicao (antes do '\0') e imprime de tras para frente
    cptr--;
    while(cptr >= s) {
        printf("%c", *cptr);
        cptr--;
    }
    
    printf("\n\nExplicacao:\n");
    printf("1. cptr aponta para o inicio da string\n");
    printf("2. Percorremos ate o final (encontramos '\\0')\n");
    printf("3. Voltamos uma posicao e imprimimos de tras para frente\n");
    printf("4. Continuamos ate chegar no inicio da string\n");
}

// ============================================================================
// QUESTAO 7: CADASTRO DE PRODUTOS COM ESTRUTURA
// ============================================================================
struct Produto {
    int codigo;
    char nome[50];
    float preco;
};

void questao7() {
    printf("=== QUESTAO 7: CADASTRO DE PRODUTOS ===\n\n");
    
    int n;
    struct Produto *produtos;
    
    // Solicita o numero de produtos
    printf("Digite o numero de produtos: ");
    scanf("%d", &n);
    
    if(n <= 0) {
        printf("Erro: Numero invalido!\n");
        return;
    }
    
    // Aloca memoria para o vetor de produtos
    produtos = (struct Produto*) malloc(n * sizeof(struct Produto));
    
    if(produtos == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return;
    }
    
    // Cadastra os produtos
    printf("\n=== CADASTRO DE PRODUTOS ===\n");
    for(int i = 0; i < n; i++) {
        printf("\nProduto %d:\n", i+1);
        printf("Codigo: ");
        scanf("%d", &produtos[i].codigo);
        printf("Nome: ");
        scanf("%s", produtos[i].nome);
        printf("Preco: ");
        scanf("%f", &produtos[i].preco);
    }
    
    // Imprime lista de produtos
    printf("\n=== LISTA DE PRODUTOS ===\n");
    printf("Codigo\tNome\t\tPreco\n");
    printf("------\t----\t\t-----\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%s\t\t%.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
    
    // Consulta preco por codigo
    int codigo_consulta;
    printf("\n=== CONSULTA DE PRECO ===\n");
    printf("Digite o codigo do produto para consultar o preco: ");
    scanf("%d", &codigo_consulta);
    
    int encontrado = 0;
    for(int i = 0; i < n; i++) {
        if(produtos[i].codigo == codigo_consulta) {
            printf("Produto encontrado!\n");
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf("Produto nao encontrado!\n");
    }
    
    // Libera memoria
    free(produtos);
}

// ============================================================================
// QUESTAO 8: VETOR DINAMICO COM FUNCAO
// ============================================================================
void ler_vetor(int *vetor, int n) {
    printf("Digite os %d elementos do vetor:\n", n);
    for(int i = 0; i < n; i++) {
        printf("Elemento %d: ", i+1);
        scanf("%d", &vetor[i]);
    }
}

void questao8() {
    printf("=== QUESTAO 8: VETOR DINAMICO COM FUNCAO ===\n\n");
    
    int n;
    int *vetor;
    
    // Solicita o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    
    if(n <= 0) {
        printf("Erro: Tamanho invalido!\n");
        return;
    }
    
    // Aloca memoria para o vetor
    vetor = (int*) malloc(n * sizeof(int));
    
    if(vetor == NULL) {
        printf("Erro: Nao foi possivel alocar memoria!\n");
        return;
    }
    
    printf("Vetor alocado com sucesso!\n");
    printf("Tamanho: %d elementos\n", n);
    printf("Memoria alocada: %d bytes\n", n * sizeof(int));
    
    // Chama a funcao para ler os elementos
    ler_vetor(vetor, n);
    
    // Imprime o vetor preenchido
    printf("\nVetor preenchido:\n");
    for(int i = 0; i < n; i++) {
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }
    
    // Libera a memoria alocada
    free(vetor);
    printf("\nMemoria liberada com sucesso!\n");
}

// ============================================================================
// QUESTAO 9: MATRIZ DINAMICA COM FUNCOES
// ============================================================================
int** alocar_matriz(int m, int n) {
    int **matriz;
    int i;
    
    // Aloca o vetor de ponteiros (linhas)
    matriz = (int**) malloc(m * sizeof(int*));
    
    if(matriz == NULL) {
        printf("Erro: Nao foi possivel alocar memoria para as linhas!\n");
        return NULL;
    }
    
    // Aloca cada linha da matriz
    for(i = 0; i < m; i++) {
        matriz[i] = (int*) malloc(n * sizeof(int));
        if(matriz[i] == NULL) {
            printf("Erro: Nao foi possivel alocar memoria para a linha %d!\n", i);
            // Libera memoria ja alocada em caso de erro
            for(int j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }
    
    return matriz;
}

void liberar_matriz(int **matriz, int m) {
    int i;
    
    if(matriz != NULL) {
        // Libera cada linha
        for(i = 0; i < m; i++) {
            if(matriz[i] != NULL) {
                free(matriz[i]);
            }
        }
        // Libera o vetor de ponteiros
        free(matriz);
    }
}

void questao9() {
    printf("=== QUESTAO 9: MATRIZ DINAMICA COM FUNCOES ===\n\n");
    
    int m, n;
    int **matriz;
    
    // Solicita as dimensoes da matriz
    printf("Digite o numero de linhas (m): ");
    scanf("%d", &m);
    printf("Digite o numero de colunas (n): ");
    scanf("%d", &n);
    
    if(m <= 0 || n <= 0) {
        printf("Erro: Dimensoes invalidas!\n");
        return;
    }
    
    // Aloca a matriz usando a funcao
    matriz = alocar_matriz(m, n);
    
    if(matriz == NULL) {
        printf("Erro: Nao foi possivel alocar a matriz!\n");
        return;
    }
    
    printf("Matriz %dx%d alocada com sucesso!\n", m, n);
    printf("Memoria alocada: %d bytes\n", m * n * sizeof(int));
    
    // Preenche a matriz com valores de exemplo
    printf("\nPreenchendo a matriz com valores de exemplo:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            matriz[i][j] = i * n + j + 1; // Valores sequenciais
        }
    }
    
    // Imprime a matriz
    printf("\nMatriz preenchida:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    // Libera a memoria usando a funcao
    liberar_matriz(matriz, m);
    printf("\nMemoria da matriz liberada com sucesso!\n");
}

// ============================================================================
// MENU PRINCIPAL
// ============================================================================
int main() {
    int opcao;
    
    printf("=== EXERCICIOS DE PONTEIROS - ESTRUTURA DE DADOS III ===\n\n");
    
    do {
        printf("\nEscolha uma questao (1-9) ou 0 para sair:\n");
        printf("1. Diferencas entre operacoes com ponteiros\n");
        printf("2. Comentarios em codigo com ponteiros\n");
        printf("3. Corrigir programa com ponteiros\n");
        printf("4. Alocacao dinamica de vetor\n");
        printf("5. Funcao inverte_vetor\n");
        printf("6. Imprimir string na ordem inversa\n");
        printf("7. Cadastro de produtos com estrutura\n");
        printf("8. Vetor dinamico com funcao\n");
        printf("9. Matriz dinamica com funcoes\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: questao1(); break;
            case 2: questao2(); break;
            case 3: questao3(); break;
            case 4: questao4(); break;
            case 5: questao5(); break;
            case 6: questao6(); break;
            case 7: questao7(); break;
            case 8: questao8(); break;
            case 9: questao9(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n"); break;
        }
        
        if(opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while(opcao != 0);
    
    return 0;
}
