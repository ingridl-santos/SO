// Ingrid Santos e João Alberto
// TP - Banheiro
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"
#include "semaphore.h"
#include <iostream>


using namespace std;

sem_t mutex;                    //controle de pessoas
sem_t db;                       //controle banheiro geral
sem_t fim;

int rc = 0;                     //numero de pessoas 

int totaldepessoas = 0;

//tava pronto para recebr workload
//int tempoprog1[10] = {1,2,3,2,4,2,1,5,3,1}; //tempo no banheiro
//int tempoprog2[10] = {5,5,5,5,5,5,5,5,5,5}; //tempo de espera para proxima vez

int tempoprog1 = 0; //tempo no banheiro
int tempoprog2 = 0; //tempo de espera para proxima vez
int tempolimp1 = 3;	//tempo de limpeza
int tempolimp2 = 8;	//tempo para proxima limpeza

int limpando =0;

void* programador(void *arg);
void* limpeza(void *arg);
void usar_banheiro(int i);
void trabalhando(int i);
void esperando_para_limpar(int i);
void limpando_banheiro(int i);

int main() {

	cout<<"insira t_banheiro:"<<endl;
	cin>>tempoprog1;

	cout<<"insira t_trab: "<<endl;
	cin>>tempoprog2;

	cout<<"insira t_limp"<<endl;
	cin>>tempolimp1;

	cout<<"insira t_esp"<<endl;
	cin>>tempolimp2;


	sem_init(&mutex, 0, 3); //3 define a quantidade de box
	sem_init(&db, 0, 1);
	sem_init(&fim, 0, 1);

	pthread_t prog[10], limp[1];

	int i;

	//um agente de limpeza
	for (i = 0; i< 1; i++) {
		pthread_create(&limp[i], NULL, limpeza, (void*) &i);
	}

	//10 programadores
	for (i = 0; i < 10 ; i++) {
		pthread_create(&prog[i], NULL, programador, (void*) &i);
	}

	

	//sempre esta executando
	while(1);
	return 0;
}

void* programador(void *arg) {
	int i = *((int *) arg);

	while(1) {  

		sem_wait(&mutex);       //trava as pessoas
		
		sem_wait(&fim);
		if(rc==0){
			
			if(limpando == 1){
				sem_wait(&fim); 
			}

		}
		sem_post(&fim);

		if(rc>3){
			sem_post(&mutex); 
			sem_wait(&db);
			sem_wait(&mutex);
		}

	 	rc = rc + 1;            //adiciona pessoa

		/*if (rc == 3) {          //se for o primeiro usuario
	    	sem_wait(&db);   
		}*/

		sem_post(&mutex);      	//libera as pessoas

		usar_banheiro(i);      	//usa um banheiro
		sem_wait(&mutex);       //trava as pessoas
		rc = rc - 1;            //a pessoa sai do banheiro
		totaldepessoas++;

	    sem_post(&db);
	    
	 	
		sem_post(&mutex);       //libera as pessoas
		trabalhando(i);       

	}
}

void* limpeza(void *arg) {
	int i = *((int *) arg);

	while(1) {               
		esperando_para_limpar(i);       

		sem_wait(&fim);
		//cout<<"a"<<endl;
		sem_wait(&mutex);		//trava as pessoas
		sem_wait(&db);          //trava o banheir
		
		
		//cout<<"b"<<endl;
		
		limpando = 1;
		limpando_banheiro(i);   //limpa o banheiro
		limpando = 0;
		sem_post(&fim);

		sem_post(&db);          //libera o banheiro
		sem_post(&mutex);		//libera as pessoas
		
	}
}

void usar_banheiro(int i) {
	printf("programador %d esta no banheiro\n", i);
	sleep( tempoprog1);
}

void trabalhando(int i) {
	//printf("programador %d esta esperando a hora\n", i);
	sleep(tempoprog2);
}

void esperando_para_limpar(int i) {
	//printf("limpeza %d esta esperando a hora\n", i);
	sleep(tempolimp2);
}

void limpando_banheiro(int i) {
	cout<<"Total de pessoas que passaram pelo banheiro: "<<totaldepessoas<<endl;
	totaldepessoas = 0;
	printf("limpeza %d esta limpando\n", i);
	sleep( tempolimp1);
	cout<<"Terminou de limpar"<<endl;
}