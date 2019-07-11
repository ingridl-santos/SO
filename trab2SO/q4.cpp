#include <omp.h>
#include <bits/stdc++.h>

/*
	int omp_get_thread_num();
	int omp_get_num_threads();
	omp_set_num_threads();
	double omp_get_wtime();
	#pragma omp barrier - espera por todos
	#pragma omp critical - uma de cada vez
*/

using namespace std;

#define n 600

int dist[n][n];

void floydWarshallParalelo() {
	//Inicializa matriz dist 
	#pragma omp parallel for
	for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
			if(i!=j){
                dist[i][j] = i*j + (j-i)*(j-i);
            }
			else{
                dist[i][j]=0;
            }
		}
    }
		

	//Floyd-Warshall
	for(int k = 0; k < n; k++) {
		#pragma omp parallel for
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );
            }
        }
	}
}

void floydWarshallNaoParalelo() {
	//Inicializa matriz dist
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(i!=j) {
				dist[i][j] = i*j + (j-i)*(j-i);
            }
			else{
				dist[i][j]=0;
            }
		}
    }

	for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );
            }
        }
    }
}

int main() {
	double w_timer;

	//Versao paralelo
	w_timer = omp_get_wtime();
	floydWarshallParalelo();
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nAlgoritmo Floyd-Warshall Paralelizado: "<<w_timer<<"s";

	//Versao nao paralela
	w_timer = omp_get_wtime();
	floydWarshallNaoParalelo();
	w_timer = (double)omp_get_wtime() - w_timer;
	cout<<"\nAlgoritmo Floyd-Warshall Não Paralelizado: "<<w_timer<<"s\n\n";
}