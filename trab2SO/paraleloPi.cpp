/*
    g++ paraleloPi.cpp -o paraleloPi -fopenmp
    time ./paraleloPi 8000
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char const *argv[]) {
    
    unsigned long int n;
    double r, pi = 1;
    int i, j;
    
    if (argc != 2) {
        printf("Uso: <calcPi> <num de iterações>\n");
        exit(1);
    }

    n = strtol (argv[1], NULL, 10);
    if (!n) {
        printf("Erro: número inválido de iterações");
        exit(2);
    }

    #pragma omp parallel for ordered private( i, j, r) reduction(*:pi) schedule(dynamic)
    for (i = 0; i < n; i++) {
        r = 2;
        for (j = i; j; j--) {
            r = 2 + sqrt(r);
        }
        r = sqrt(r);

        pi *= (r/2);
    }
    #pragma omp ordered
    pi = 2 / pi;

    printf("Aproximação do valor de PI = %1.16f\n", pi);

    return 0;
}
