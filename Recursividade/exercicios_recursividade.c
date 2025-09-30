#include <stdio.h>

// Exercício 1: Função recursiva para inverter um número inteiro
// Esta função pega um número como 123 e retorna 321
// Parâmetros: n = número a ser invertido, resultado = acumulador do resultado
int inverterNumero(int n, int resultado) {
    // Caso base: quando n chega a 0, retorna o resultado acumulado
    if (n == 0) {
        return resultado;
    }
    // Passo recursivo: pega o último dígito de n e adiciona ao resultado
    // n/10 remove o último dígito, resultado*10 + n%10 adiciona o dígito ao resultado
    return inverterNumero(n / 10, resultado * 10 + n % 10);
}

// Exercício 2: Função recursiva para somar elementos de um vetor
// Soma todos os elementos de um vetor usando recursão
// Parâmetros: vetor = array de inteiros, tamanho = tamanho do vetor, indice = posição atual
int somarVetor(int vetor[], int tamanho, int indice) {
    // Caso base: quando o índice ultrapassa o tamanho do vetor
    if (indice >= tamanho) {
        return 0; // Retorna 0 para não afetar a soma
    }
    // Passo recursivo: soma o elemento atual com a soma do resto do vetor
    return vetor[indice] + somarVetor(vetor, tamanho, indice + 1);
}

// Exercício 3: Função recursiva para calcular somatório de 1 a N
// Calcula a soma de todos os números de 1 até N
// Exemplo: somatorio(5) = 1+2+3+4+5 = 15
int somatorio(int n) {
    // Caso base: se n for menor ou igual a 0, retorna 0
    if (n <= 0) {
        return 0;
    }
    // Passo recursivo: soma n com o somatório de n-1
    return n + somatorio(n - 1);
}

// Exercício 4: Função recursiva para calcular k^n
// Calcula a potência de k elevado a n usando apenas multiplicações
// Exemplo: potencia(2, 3) = 2 * 2 * 2 = 8
int potencia(int k, int n) {
    // Caso base: qualquer número elevado a 0 é 1
    if (n == 0) {
        return 1;
    }
    // Passo recursivo: k^n = k * k^(n-1)
    return k * potencia(k, n - 1);
}

// Exercício 5: Função recursiva para inverter vetor
// Inverte a ordem dos elementos de um vetor usando recursão
// Parâmetros: vetor = array de floats, inicio = índice inicial, fim = índice final
void inverterVetor(float vetor[], int inicio, int fim) {
    // Caso base: quando os índices se cruzam, para a recursão
    if (inicio >= fim) {
        return;
    }
    // Troca os elementos das posições inicio e fim
    float temp = vetor[inicio];
    vetor[inicio] = vetor[fim];
    vetor[fim] = temp;
    // Passo recursivo: chama a função com os índices mais próximos do centro
    inverterVetor(vetor, inicio + 1, fim - 1);
}

// Exercício 6: Função recursiva para calcular MDC
// Calcula o Máximo Divisor Comum usando o algoritmo de Euclides
// Exemplo: mdc(48, 18) = 6
int mdc(int x, int y) {
    // Caso base: quando y é 0, x é o MDC
    if (y == 0) {
        return x;
    }
    // Passo recursivo: mdc(x,y) = mdc(y, x%y)
    // O resto da divisão x%y é usado para continuar o algoritmo
    return mdc(y, x % y);
}

// Exercício 7: Função recursiva para contar ocorrências de dígito
// Conta quantas vezes um dígito k aparece em um número n
// Exemplo: contarDigito(762021192, 2) = 3 (o dígito 2 aparece 3 vezes)
int contarDigito(int n, int k) {
    // Caso base: quando n chega a 0, não há mais dígitos para verificar
    if (n == 0) {
        return 0;
    }
    // Se o último dígito de n é igual a k, conta 1 e continua verificando
    if (n % 10 == k) {
        return 1 + contarDigito(n / 10, k);
    }
    // Se não é igual, apenas continua verificando o resto do número
    return contarDigito(n / 10, k);
}

// Exercício 8: Função recursiva para multiplicação usando somas
// Multiplica dois números usando apenas somas sucessivas
// Exemplo: multiplicar(3, 4) = 3 + 3 + 3 + 3 = 12
int multiplicar(int n1, int n2) {
    // Caso base: qualquer número multiplicado por 0 é 0
    if (n2 == 0) {
        return 0;
    }
    // Passo recursivo: n1 * n2 = n1 + n1 * (n2-1)
    return n1 + multiplicar(n1, n2 - 1);
}

// Exercício 9: Função recursiva para imprimir números pares de 0 até N (crescente)
// Imprime todos os números pares de 0 até n em ordem crescente
// Exemplo: imprimirParesCrescente(8) imprime: 0 2 4 6 8
void imprimirParesCrescente(int n) {
    // Caso base: quando n é negativo, para a recursão
    if (n < 0) {
        return;
    }
    // Primeiro chama recursivamente para n-1 (para imprimir em ordem crescente)
    imprimirParesCrescente(n - 1);
    // Depois verifica se n é par e imprime
    if (n % 2 == 0) {
        printf("%d ", n);
    }
}

// Exercício 10: Função recursiva para imprimir números de 0 até N (decrescente)
// Imprime todos os números de n até 0 em ordem decrescente
// Exemplo: imprimirDecrescente(5) imprime: 5 4 3 2 1 0
void imprimirDecrescente(int n) {
    // Caso base: quando n é negativo, para a recursão
    if (n < 0) {
        return;
    }
    // Primeiro imprime n, depois chama recursivamente para n-1
    printf("%d ", n);
    imprimirDecrescente(n - 1);
}

// Exercício 11: Função recursiva para imprimir números pares de 0 até N (decrescente)
// Imprime todos os números pares de n até 0 em ordem decrescente
// Exemplo: imprimirParesDecrescente(8) imprime: 8 6 4 2 0
void imprimirParesDecrescente(int n) {
    // Caso base: quando n é negativo, para a recursão
    if (n < 0) {
        return;
    }
    // Primeiro verifica se n é par e imprime
    if (n % 2 == 0) {
        printf("%d ", n);
    }
    // Depois chama recursivamente para n-1 (para imprimir em ordem decrescente)
    imprimirParesDecrescente(n - 1);
}

// Exercício 12: Função recursiva para calcular fatorial duplo
// Calcula o fatorial duplo de um número ímpar (produto dos ímpares de 1 até n)
// Exemplo: fatorialDuplo(5) = 5!! = 1 * 3 * 5 = 15
int fatorialDuplo(int n) {
    // Caso base: quando n é menor ou igual a 1, retorna 1
    if (n <= 1) {
        return 1;
    }
    // Passo recursivo: n!! = n * (n-2)!!
    // Pula de 2 em 2 para manter apenas números ímpares
    return n * fatorialDuplo(n - 2);
}

int main() {
    printf("=== EXERCICIOS DE RECURSIVIDADE ===\n\n");
    
    // Teste Exercício 1: Inverter número
    printf("1. Inverter numero 123: %d\n", inverterNumero(123, 0));
    printf("   Explicacao: 123 -> 321 (inverte os digitos)\n\n");
    
    // Teste Exercício 2: Somar vetor
    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    printf("2. Soma do vetor {1,2,3,4,5}: %d\n", somarVetor(vetor, tamanho, 0));
    printf("   Explicacao: 1+2+3+4+5 = 15\n\n");
    
    // Teste Exercício 3: Somatório
    printf("3. Somatorio de 1 a 5: %d\n", somatorio(5));
    printf("   Explicacao: 1+2+3+4+5 = 15\n\n");
    
    // Teste Exercício 4: Potência
    printf("4. 2^3 = %d\n", potencia(2, 3));
    printf("   Explicacao: 2*2*2 = 8\n\n");
    
    // Teste Exercício 5: Inverter vetor
    float vetorFloat[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    printf("5. Vetor original: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", vetorFloat[i]);
    }
    inverterVetor(vetorFloat, 0, 4);
    printf("\n   Vetor invertido: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", vetorFloat[i]);
    }
    printf("\n   Explicacao: inverte a ordem dos elementos\n\n");
    
    // Teste Exercício 6: MDC
    printf("6. MDC de 48 e 18: %d\n", mdc(48, 18));
    printf("   Explicacao: maior divisor comum entre 48 e 18\n\n");
    
    // Teste Exercício 7: Contar dígito
    printf("7. Ocorrencias do digito 2 em 762021192: %d\n", contarDigito(762021192, 2));
    printf("   Explicacao: conta quantas vezes o digito 2 aparece\n\n");
    
    // Teste Exercício 8: Multiplicação por soma
    printf("8. 3 * 4 = %d\n", multiplicar(3, 4));
    printf("   Explicacao: 3+3+3+3 = 12 (multiplicacao usando somas)\n\n");
    
    // Teste Exercício 9: Números pares crescente
    printf("9. Numeros pares de 0 a 8 (crescente): ");
    imprimirParesCrescente(8);
    printf("\n   Explicacao: imprime pares em ordem crescente\n\n");
    
    // Teste Exercício 10: Números decrescente
    printf("10. Numeros de 0 a 5 (decrescente): ");
    imprimirDecrescente(5);
    printf("\n   Explicacao: imprime todos os numeros em ordem decrescente\n\n");
    
    // Teste Exercício 11: Números pares decrescente
    printf("11. Numeros pares de 0 a 8 (decrescente): ");
    imprimirParesDecrescente(8);
    printf("\n   Explicacao: imprime pares em ordem decrescente\n\n");
    
    // Teste Exercício 12: Fatorial duplo
    printf("12. Fatorial duplo de 5: %d\n", fatorialDuplo(5));
    printf("   Explicacao: 5!! = 1*3*5 = 15 (produto dos impares)\n\n");
    
    printf("=== FIM DOS TESTES ===\n");
    return 0;
}
