/* 
    g++ multiplicaMatrizParalelo.cpp -o matrizP -fopenmp
    time ./matrizP
 */


#include <stdio.h>
#include <stdlib.h>
#define ORDER 1024
#define AVAL 3.0
#define BVAL 5.0
#define TOL  0.001
 
int main(int argc, char **argv)
{
    int Ndim, Pdim, Mdim;   /* A[N][P], B[P][M], C[N][M] */
    double *A, *B, *C, tmp;
    int i, j, k;
 
    Ndim = Pdim = Mdim = ORDER;
 
    A = (double *) malloc(Ndim * Pdim * sizeof(double));
    B = (double *) malloc(Pdim * Mdim * sizeof(double));
    C = (double *) malloc(Ndim * Mdim * sizeof(double));
 
    /* initialize A[N][P] = AVAL */
    for (i = 0; i < Ndim; i++)
        for (j = 0; j < Pdim; j++)
            *(A+(i*Ndim+j)) = AVAL;
 
    /* initialize B[P][M] = BVAL */
    for (i = 0; i < Pdim; i++)
        for (j = 0; j < Mdim; j++)
            *(B+(i*Pdim+j)) = BVAL;
 
    /* initialize C[N][M] = 0.0 */
    for (i = 0; i < Ndim; i++)
        for (j = 0; j < Mdim; j++)
            *(C+(i*Ndim+j)) = 0.0;
 
    /* multiply the matrices */
    #pragma omp parallel for private(tmp, i, j, k) shared(Ndim, Mdim, Pdim)
    for (i = 0; i < Ndim; i++){
        for (j = 0; j < Mdim; j++){
            tmp = 0.0;
            for(k = 0;k < Pdim; k++){
                /* C(i,j) = sum(A(i,k) * B(k,j)) */
                tmp += (*(A+(i*Ndim+k))) * (*(B+(k*Pdim+j)));
            }
            *(C+(i*Ndim+j)) = tmp;
        }
    }
 
    printf("Done!\n");
    return 0;
}