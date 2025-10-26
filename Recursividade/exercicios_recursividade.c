#include <stdio.h>

// Exercício 1
// essa função recursiva vai inverter um número inteiro
int inverter_numero(int n, int resultado) {
    // quando n chega a 0, retorna o resultado acumulado
    if (n == 0) {
        return resultado;
    }
    return inverter_numero(n / 10, resultado * 10 + n % 10);
}

// Exercício 2
// essa fubção vai somar todos os elementos de um vetor usando recursão
int somar_vetor(int vet[], int tamanho, int id) {
    if (id >= tamanho) {
        return 0; // Retorna 0 para não afetar a soma
    }
    // recursão, ele vai soma o elemento atual com a soma do resto do vetor
    return vet[id] + somar_vetor(vet, tamanho, id + 1);
}

// Exercicio 3
// essa função recursiva serve para calcular somatório de 1 a N
int somatorio(int n) {
    //se n for menor ou igual a 0, retorna 0
    if (n <= 0) {
        return 0;
    }
    // aqui soma n com o somatório de n-1
    return n + somatorio(n - 1);
}

// Exercício 4
// função recursiva para calcular k^n
int potencia(int k, int n) {
    //qualquer número elevado a 0 é 1
    if (n == 0) {
        return 1;
    }
    // Passo recursivo
    return k * potencia(k, n - 1);
}

// Exercício 5
// essa função inverte a ordem dos elementos de um vetor usando recursão
void inverter_vet(float vet[], int inicio, int fim) {
    //quando os índices se cruzam, para a recursão
    if (inicio >= fim) {
        return;
    }
    // aqui vai troca os elementos das posições inicio e fim
    float temp = vet[inicio];
    vet[inicio] = vet[fim];
    vet[fim] = temp;
    //por fim vai chamar a função com os índices mais próximos do centro
    inverter_vet(vet, inicio + 1, fim - 1);
}

// Exercício 6
//função recursiva para calcular MDC
int mdc(int x, int y) {
    if (y == 0) {
        return x;
    }
    //passo recursivo
    return mdc(y, x % y);
}

// Exercício 7
// essa função conta quantas vezes um dígito k aparece em um número n
int contar_di(int n, int k) {
    //quando n chega a 0, não há mais dígitos para verificar
    if (n == 0) {
        return 0;
    }
    // Se o último dígito de n é igual a k, conta 1 e continua verificando
    if (n % 10 == k) {
        return 1 + contar_di(n / 10, k);
    }
    // Se não é igual, apenas continua verificando o resto do número
    return contar_di(n / 10, k);
}

// Exercício 8
// essa função multiplica dois números usando apenas somas sucessivas
int multiplicar(int n1, int n2) {
    if (n2 == 0) {
        return 0;// verificação de segurança 
    }
    // Passo recursivo
    return n1 + multiplicar(n1, n2 - 1);
}

// Exercício 9
// essa função imprime todos os números pares de 0 até n em ordem crescente
void imprimir_pares_cres(int n) {
    //quando n é negativo, para a recursão
    if (n < 0) {
        return;
    }
    // Primeiro chama recursivamente para n-1, para imprimir em ordem crescente
    imprimir_pares_cres(n - 1);
    // Depois verifica se n é par e imprime
    if (n % 2 == 0) {
        printf("%d ", n);
    }
}

// Exercício 10
// aqui vai imprimir todos os números de n até 0 em ordem decrescente
void decrescent(int n) {
    if (n < 0) {
        return;
    }
    //primeiro imprime n, depois chama recursivamente para n-1
    printf("%d ", n);
    decrescent(n - 1);
}

// Exercício 11
// o objetivo dessa função é imprimir todos os números pares de n até 0 em ordem decrescente
void pares_decrescente(int n) {
    if (n < 0) {
        return;
    }
    //primeiro vai verificar se n é par e imprime
    if (n % 2 == 0) {
        printf("%d ", n);
    }
    // Depois chama recursivamente para n-1 
    pares_decrescente(n - 1);
}

// Exercício 12
// essa função vai calcular o fatorial duplo de um número ímpar 
int fatorial_duplo(int n) {
    if (n <= 1) {
        return 1;
    }
    // Pula de 2 em 2 para manter apenas números ímpares
    return n * fatorial_duplo(n - 2);
}

int main() {
    
    // Teste Exercício 1
    printf("1. Inverter numero 123: %d\n", inverter_numero(123, 0));
    printf("   Explicacao: 123 -> 321 (inverte os digitos)\n\n");
    
    // Teste Exercício 2
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    printf("2. Soma do vetor {1,2,3,4,5}: %d\n", somar_vetor(vetor, tamanho, 0));
    
    // Teste Exercício 3
    printf("3. Somatorio de 1 a 5: %d\n", somatorio(5));
    
    // Teste Exercício 4
    printf("4. 2^3 = %d\n", potencia(2, 3));
    
    // Teste Exercício 5
    float vetorFloat[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    printf("5. Vetor original: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", vetorFloat[i]);
    }
    inverter_vet(vetorFloat, 0, 4);
    printf("\n   Vetor invertido: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", vetorFloat[i]);
    }
    
    // Teste Exercício 6
    printf("6. MDC de 48 e 18: %d\n", mdc(48, 18));
  
    // Teste Exercício 7
    printf("7. Ocorrencias do digito 2 em 762021192: %d\n", contar_di(762021192, 2));
    
    // Teste Exercício 8
    printf("8. 3 * 4 = %d\n", multiplicar(3, 4));
    
    // Teste Exercício 9
    printf("9. Numeros pares de 0 a 8 (crescente): ");
    imprimir_pares_cres(8);
    
    // Teste Exercício 10
    printf("10. Numeros de 0 a 5 (decrescente): ");
    decrescent(5);
    
    // Teste Exercício 11
    printf("11. Numeros pares de 0 a 8 (decrescente): ");
    pares_decrescente(8);
    
    // Teste Exercício 12
    printf("12. Fatorial duplo de 5: %d\n", fatorial_duplo(5));

    return 0;
}
