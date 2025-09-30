#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"

int main(){
    printf("=== EXEMPLO DE USO DAS FUNCOES IMPLEMENTADAS ===\n\n");
    
    // Criando listas para teste
    Lista* li1 = cria_lista();
    Lista* li2 = cria_lista();
    
    // Dados de exemplo
    struct aluno alunos[] = {
        {1, "Joao", 8.5, 7.0, 9.0},
        {2, "Maria", 9.0, 8.5, 7.5},
        {3, "Pedro", 6.5, 8.0, 7.0},
        {4, "Ana", 9.5, 9.0, 8.5}
    };
    
    // Inserindo alunos na lista 1
    printf("1. Inserindo alunos na lista 1:\n");
    for(int i = 0; i < 4; i++){
        insere_lista_ordenada(li1, alunos[i]);
    }
    imprime_lista(li1);
    
    // Teste 1a: Consulta por matrícula
    printf("\n2. Consultando aluno por matricula (matricula 2):\n");
    struct aluno consultado = consulta_lista_matricula(li1, 2);
    if(consultado.matricula != 0){
        printf("Encontrado: %s - Matricula: %d\n", consultado.nome, consultado.matricula);
    } else {
        printf("Aluno nao encontrado!\n");
    }
    
    // Teste 1b: Consulta por posição
    printf("\n3. Consultando aluno por posicao (posicao 1):\n");
    consultado = consulta_lista_posicao(li1, 1);
    if(consultado.matricula != 0){
        printf("Encontrado: %s - Matricula: %d\n", consultado.nome, consultado.matricula);
    } else {
        printf("Aluno nao encontrado!\n");
    }
    
    // Teste 3: Inserir em posição específica
    printf("\n4. Inserindo aluno na posicao 2:\n");
    struct aluno novo = {5, "Carlos", 7.0, 8.0, 9.0};
    if(insere_lista_posicao(li1, novo, 2)){
        printf("Aluno inserido com sucesso!\n");
    }
    imprime_lista(li1);
    
    // Teste 4: Construir lista a partir de vetor
    printf("\n5. Construindo lista a partir de vetor float:\n");
    float notas[] = {8.5, 7.0, 9.0, 6.5};
    Lista* li_vetor = constroi_lista_vetor(notas, 4);
    if(li_vetor != NULL){
        printf("Lista criada a partir do vetor:\n");
        imprime_lista(li_vetor);
    }
    
    // Teste 5: Remover todos com valor específico
    printf("\n6. Removendo todos os alunos com matricula 3:\n");
    int removidos = remove_todos_valor(li1, 3);
    printf("Removidos %d alunos\n", removidos);
    imprime_lista(li1);
    
    // Teste 6: Concatenar listas
    printf("\n7. Concatenando listas:\n");
    insere_lista_ordenada(li2, alunos[0]);
    insere_lista_ordenada(li2, alunos[1]);
    printf("Lista 2 antes da concatenacao:\n");
    imprime_lista(li2);
    
    concatena_listas(li1, li2);
    printf("Lista 1 apos concatenacao:\n");
    imprime_lista(li1);
    
    // Teste 7: Remover repetidos
    printf("\n8. Removendo elementos repetidos:\n");
    int repetidos = remove_repetidos(li1);
    printf("Removidos %d elementos repetidos\n", repetidos);
    imprime_lista(li1);
    
    // Teste 8: Fusão de listas ordenadas
    printf("\n9. Testando fusao de listas ordenadas:\n");
    Lista* li3 = cria_lista();
    Lista* li4 = cria_lista();
    
    struct aluno al1 = {10, "Teste1", 5.0, 6.0, 7.0};
    struct aluno al2 = {20, "Teste2", 6.0, 7.0, 8.0};
    struct aluno al3 = {15, "Teste3", 7.0, 8.0, 9.0};
    
    insere_lista_ordenada(li3, al1);
    insere_lista_ordenada(li3, al3);
    insere_lista_ordenada(li4, al2);
    
    printf("Lista 3 antes da fusao:\n");
    imprime_lista(li3);
    printf("Lista 4 antes da fusao:\n");
    imprime_lista(li4);
    
    fusao_listas_ordenadas(li3, li4);
    printf("Lista 3 apos fusao:\n");
    imprime_lista(li3);
    
    // Liberando memória
    libera_lista(li1);
    libera_lista(li_vetor);
    libera_lista(li3);
    
    printf("\n=== FIM DOS TESTES ===\n");
    return 0;
}
