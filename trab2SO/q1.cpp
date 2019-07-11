#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
using namespace std;

#define SIZE 10000

int mat1[SIZE][SIZE];
int mat2[SIZE][SIZE];
int matF[SIZE][SIZE];

void semParalelismo(int m1l, int m1c, int m2l, int m2c){
    

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < m1l; i++){
        for (int j = 0; j < m2c; j++){
            for (int k = 0; k < m1l; k++){
                matF[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();

    cout << ">Imprimindo matriz resultante: " << endl;
    // for (int i = 0; i < m1l; i++){
    //     for (int j = 0; j < m2c; j++){
    //         cout << matF[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    cout << ">Fim da matriz resultante. " << endl;
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Tempo de execucao sem paralelismo: " << elapsed.count() << " sesgundos\n";
}

void comParalelismo(int m1l, int m1c, int m2l, int m2c){
    int matF[m1l][m2c];

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for
    for (int i = 0; i < m1l; i++){
        #pragma omp parallel for
        for (int j = 0; j < m2c; j++){
            #pragma omp parallel for
            for (int k = 0; k < m1l; k++){
                matF[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    cout << ">Imprimindo matriz resultante: " << endl;
    // for (int i = 0; i < m1l; i++){
    //     for (int j = 0; j < m2c; j++){
    //         cout << matF[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    cout << ">Fim da matriz resultante. " << endl;

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Tempo de execucao com paralelismo: " << elapsed.count() << " sesgundos\n";
}

    int main(){

        int mat_1_c, mat_1_l, mat_2_c, mat_2_l, escolha;

        cout << ">QUESTAO 1: MULTIPLICANDO MATRIZES\n->Insira as dimensoes da matriz 1" << endl;
        cin >> mat_1_l >> mat_1_c;
        cout << "\n->Insira as dimensoes da matriz 2" << endl;
        cin >> mat_2_l >> mat_2_c;

        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                mat1[i][j] = 0;
                mat2[i][j] = 0;
                matF[i][j] = 0;
            }
        }

    #pragma omp parallel for
    for (int i = 0; i < mat_1_l; i++){
        for (int j = 0; j < mat_1_c; j++){
            mat1[i][j] = rand() % 10;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < mat_2_l; i++){
        for (int j = 0; j < mat_2_c; j++){
            mat2[i][j] = rand() % 10;
        }
    }

    cout << ">Matrizes preenchidas, fazer com paralelismo digite 1, sem paralelismo 2" << endl;
    cin >> escolha;

    if(escolha == 1){
        comParalelismo(mat_1_l, mat_1_c, mat_2_l, mat_2_c);
    }else{
        semParalelismo(mat_1_l, mat_1_c, mat_2_l, mat_2_c);
    }
}
