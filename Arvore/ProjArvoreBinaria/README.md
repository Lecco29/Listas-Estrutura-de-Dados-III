# Exercícios de Árvore Binária

Este projeto contém os exercícios de árvore binária implementados para a disciplina de Estrutura de Dados III.

## Arquivos

- `ArvoreBinaria.h` - Cabeçalho com protótipos das funções
- `ArvoreBinaria.c` - Implementação das funções básicas da árvore
- `exercicios_arvore.c` - Implementação dos exercícios solicitados
- `main.c` - Programa principal original

## Exercícios Implementados

### Exercício 1
Testa as funções `insere_ArvBin` e `remove_ArvBin`, explicando como cada uma opera na árvore.

### Exercício 2
Implementa as funções de varredura:
- `emOrdem_ArvBin` - Varredura em ordem (esquerda -> raiz -> direita)
- `posOrdem_ArvBin` - Varredura pós-ordem (esquerda -> direita -> raiz)

### Exercício 3
Implementa `TotalNO_Arvore` - função recursiva que conta a quantidade de nós na árvore.

### Exercício 4
Implementa `Cons_Arvore` - função que consulta se um determinado valor existe na árvore.

### Exercício 5
Implementa `Remove_ArvoreAtual` - função que remove um nó específico da árvore, tratando os 3 casos:
- Nó sem filhos
- Nó com 1 filho
- Nó com 2 filhos

## Como Compilar

```bash
gcc -o exercicios exercicios_arvore.c ArvoreBinaria.c
```

## Como Executar

```bash
./exercicios
```

## Menu de Opções

O programa apresenta um menu com as seguintes opções:
1. Testar insere_Arvore e remove_Arvore
2. Implementar EMOrdem e POSOrdem
3. Contar nós da árvore
4. Consultar valor na árvore
5. Remover nó específico
0. Sair

## Observações

- Todas as funções foram implementadas usando apenas conceitos de árvores binárias
- Não foram utilizadas bibliotecas externas além das padrão (stdio.h, stdlib.h)
- O código está comentado explicando o funcionamento de cada função
- Os exercícios incluem testes práticos com diferentes cenários
