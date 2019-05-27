/*  TP - SO
 Escalonamento SJF
 Ingrid Santos e João Alberto */

#include <iostream>
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include <string>

using namespace std;

int main(){


	int np,ingresso, duracao;

	cin>>np;


	int saida[np];
	int w;
	int t = 0;

	int qtdConfirma = 0;
	/*int vetConfirma[np];
	for(int i =0;i<np;i++){vetConfirma[i]=0;}

	int vetIngresso[np];
	int vetDuracao[np];*/

	int numteste = 1;
	int q = np;
	int indiceProcesso = 0;

	int execucao = 0;
	int espera = 0;

	float somaExecucao;
	float somaEspera;

	while(q != 0){

		int saida[np];

		int vetConfirma[np];
		for(int i =0;i<np;i++){vetConfirma[i]=0;}

		int vetIngresso[np];
		int vetDuracao[np];

		while(indiceProcesso != np){


			cin>>ingresso;
			cin>>duracao;


			vetIngresso[indiceProcesso] = ingresso;
			vetDuracao[indiceProcesso] = duracao;

			//DEBUG
			//cout<<"indice"<<indiceProcesso<<": "<<vetConfirma[indiceProcesso]<<" "<<vetIngresso[indiceProcesso]<<" "<<vetDuracao[indiceProcesso]<<endl;
			//cout<<ingresso<<" "<<duracao<<endl;

			indiceProcesso++;
		}

		while(qtdConfirma<np){


			int indiceMenorDuracao = 0;
			int menorDosIguais = 999999999;

			//acha programs que comecam no mesmo tempo
			//DEBUG
			//cout<<"qtdConfima: "<<qtdConfirma<<endl;
			for(int i = 0;i<np;i++){

				//DEBUG
				//cout<<vetIngresso[i]<<" "<<t<<" "<<vetDuracao[i]<<" "<<menorDosIguais<<" "<<vetConfirma[indiceMenorDuracao]<<endl;

				if(vetIngresso[i]<=t and vetDuracao[i]<menorDosIguais and vetConfirma[i] == 0){
					indiceMenorDuracao = i;
					menorDosIguais = vetDuracao[i];
				}

				//DEBUG
				//cout<<vetIngresso[i]<<" "<<t<<" "<<vetDuracao[i]<<" "<<menorDosIguais<<" "<<vetConfirma[indiceMenorDuracao]<<endl;
				//cout<<"--------------"<<endl;
			}

			if(menorDosIguais != 999999999){

				vetConfirma[indiceMenorDuracao] = 1;

				saida[qtdConfirma] = indiceMenorDuracao+1;

				qtdConfirma++;

				//cout<<"indice menor duracao: "<<indiceMenorDuracao<<endl;
				//cout<<"P"<<indiceMenorDuracao+1<<" ";



				//w = indiceMenorDuracao+1;
				//cout<<string(w);

				//saida[qtdConfirma] = w;

				//saida += "P"+ string(w) + " ";

				//DEBUG
				/*int a;
				cin>>a;*/

				int tp = t;
				t += vetDuracao[indiceMenorDuracao];


				execucao = t-vetIngresso[indiceMenorDuracao] ;

				//DEBUG
				/*cout<<endl;
				cout<<t<<" - "<<vetIngresso[indiceMenorDuracao]<<" = "<<execucao<<endl;*/

				espera = tp-vetIngresso[indiceMenorDuracao] ;

				//DEBUG
				/*cout<<tp<<" - "<<vetIngresso[indiceMenorDuracao]<<" = "<<espera<<endl;*/

				somaExecucao += execucao;
				somaEspera += espera;

				//DEBUG
				/*cout<<"tempo de chegada  processo: "<<vetIngresso[indiceMenorDuracao]<<endl;
				cout<<"tempo de inicio   processo: "<<tp<<endl;
				cout<<"tempo de termino  processo: "<<t<<endl;
				cout<<"tempo de execucao processo: "<<execucao<<endl;
				cout<<"tempo de espera   processo: "<<espera<<endl;

				cout<<"------------------------------------------"<<endl;*/

			}else{

				t++;
			}







		}

		cout<<endl;

		cout<<"Teste "<<numteste<<endl;
		cout<<"Tempo medio de execucao: "<<somaExecucao/np<<"s"<<endl;
		cout<<"Tempo medio de espera: "<<somaEspera/np<<"s"<<endl;

		for(int i =0;i<np;i++){
			cout<<"P"<<saida[i]<<" ";

		}
		cout<<endl;


		cin>>np;
		q = np;



		w=0;
		numteste ++;

		indiceProcesso = 0;
		execucao = 0;
		espera = 0;
		somaExecucao = 0.0;
		somaEspera = 0.0;

		t = 0;
		qtdConfirma = 0;
		for(int i =0;i<np;i++){vetConfirma[i]=0;}
	}
	return 0;
}
