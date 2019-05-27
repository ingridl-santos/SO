/*  TP - SO
Escalonamento Round Robin
Ingrid Santos e João Alberto
 */
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

typedef struct {

	int id;
	int entrada;
	int duracao;
	int exec;
	float espera;

} processo;


void atualizarLista( queue <processo>& processos, int np, int tempo_ingresso[], int tempo_duracao[] , int tempo){


	int x;
	for( x=0 ; x<np ; x++ ){

		if(tempo_ingresso[x] == tempo){

			processo novo;
			novo.id = x;
			novo.entrada = tempo_ingresso[x];
			novo.duracao = tempo_duracao[x];
			novo.exec = 0;
			novo.espera = 0;

			//cout<<"INSERIU"<<endl;
			processos.push(novo);

		}

	}



}


int pegaPrimeiro( queue <int>& saida, queue <processo>& processos, int &qt, int quantum_original, int tempo, float &somaespera, float &somaexecucao){
	

	processo analisar;
	analisar = processos.front();


	if(qt > 0 and analisar.exec < analisar.duracao){
		processos.front().exec += 1;
		qt--;
		//cout<<"tabalhando"<<endl;

		saida.push((processos.front().id)+1);

		//cout<<"P"<<(processos.front().id)+1<<endl;
		//cout<<processos.front().id<<" "<<processos.front().entrada<<" "<<processos.front().duracao<<" "<<processos.front().exec<<endl;
		
		if(qt == 0){

			//cout<<"------"<<endl;
			qt = quantum_original;
			if(processos.front().exec == processos.front().duracao){
				//cout<<"acabou outro+++++++++++++++"<<endl;
				//GUARDAR TEMPO ESPERA
				processos.front().espera = tempo - processos.front().exec + 1 - processos.front().entrada;
				//cout<<"e: "<<processos.front().espera<<endl;
				//cout<<"d: "<<processos.front().duracao<<endl;
				somaespera += processos.front().espera;

				//somaexecucao += (somaespera + processos.front().duracao);
				
				processos.pop();

				
				return 1;
			}else{

				
				processos.push(processos.front());
				processos.pop();


				return 0;
			}
		}


		if(processos.front().duracao == processos.front().exec){
			
			//GUARDAR TEMPO ESPERA
			processos.front().espera = tempo - processos.front().exec + 1 - processos.front().entrada;
			//cout<<"e: "<<processos.front().espera<<endl;
			//cout<<"d: "<<processos.front().duracao<<endl;
			somaespera += processos.front().espera;
			//somaexecucao += (somaespera + processos.front().duracao);
			//cout<<"---"<<endl;
			//cout<<"acabou outro------------"<<endl;
			
			processos.pop();

			return 1;
		}




	}



	

	
	return 0;


}

int main(){

	int quantum_original;
	cin>>quantum_original;

	int teste =1;

	int np;
	cin>>np;

	while(np !=0){

		int t = 0;

		int processados = 0;

		int tempo_ingresso[20], tempo_duracao[20];

		int ingresso,duracao;

		float somaespera = 0.0,somaexecucao = 0.0;

		//LEITURA
		int s;
		for( s=0 ; s<np ; s++ ){
			cin>>ingresso>>duracao;
			tempo_ingresso[s] = ingresso;
			tempo_duracao[s] = duracao;
		}


		//FILA
		queue <processo> processos;

		queue <int> saida;

		
		int quantum = quantum_original;
		int passar = quantum;

		while(processados < np ){

			//cout<<endl<<"tempo: "<<t<<endl;

			//INSERE NA LISTA NO TEMPO CERTO
			atualizarLista(processos,np,tempo_ingresso,tempo_duracao,t);

			
			//PEGA O PRIMEIRO NA FILA PARA PROCESSAR
			int p = pegaPrimeiro(saida,processos,passar,quantum_original,t, somaespera, somaexecucao);	

			//DA OK NO PROCESSAMENTTO
			if(p == 1){processados++;}


			
			//O TEMPO NAO DEPENDE DO PROCESSO
			t++;

		}


		//CALCULO DA EXECUCAO
		somaexecucao = somaespera;
		for(int o =0;o<np;o++){
			somaexecucao += tempo_duracao[o];
		}




		cout<<"Teste "<<teste<<endl;
		cout<<"Tempo medio de execucao: "<<somaexecucao/np<<"s"<<endl;
		cout<<"Tempo medio de espera: "<<somaespera/np<<"s"<<endl;


		while(!saida.empty()){
			cout<<"P"<<saida.front()<<" ";
			saida.pop();
		}
		cout<<endl;

		somaespera = 0.0;
		somaexecucao = 0.0;

		teste ++;
		t = 0;
		cin>>np;

	}


	return 0;
}