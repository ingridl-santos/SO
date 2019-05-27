/*  TP1  Sistemas Operacionais
    Arthur Bindá
    Eduardo Lopes
    Ingrid Santos
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_CLIENTES 10
#define N_CADEIRAS 5 
#define N_BARBEIROS 2

sem_t sem_cadeiras;
sem_t sem_cad_barbeiro[N_BARBEIROS]; 
sem_t sem_corte_cabelo[N_BARBEIROS];
sem_t sem_cliente_cadeira[N_BARBEIROS];

sem_t sem_escreve_visor, sem_le_visor;
int visor;

void* func_barbeiro(void *v) {
    int id = * (int*) v;
    while(1) {
        sem_wait(&sem_escreve_visor);
        visor = id;
        sem_post(&sem_le_visor);
        sem_wait(&sem_cliente_cadeira[id]);
        printf("Barbeiro %d cortou cabelo de um cliente. \n", id);
        sem_post(&sem_corte_cabelo[id]);
        sleep(random()%3);
    }
    return NULL;
}

void* func_cliente(void *v) {
    int id = *(int*) v;
    int minha_cadeira;

    sleep(random()%3);
    if (sem_trywait(&sem_cadeiras) == 0) {
        printf("Cliente %d entrou na barbearia.\n", id);
        sem_wait(&sem_le_visor);
        minha_cadeira = visor;
        sem_post(&sem_escreve_visor);
        sem_wait(&sem_cad_barbeiro[minha_cadeira]);
        printf("Cliente %d sentou na cadeira do barbeiro %d. \n", id, minha_cadeira);
        sem_post(&sem_cliente_cadeira[minha_cadeira]);
        sem_post(&sem_cadeiras);
        sem_wait(&sem_corte_cabelo[minha_cadeira]);
        sem_post(&sem_cad_barbeiro[minha_cadeira]);
        printf("Cliente %d deixou a barbearia.\n", id);
    } else {
        printf("Cliente %d não entrou na barbearia.\n", id);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t thread_clientes[N_CLIENTES], thread_barbeiros[N_BARBEIROS];
    int i, id_clientes[N_CLIENTES], id_barbeiros[N_BARBEIROS];

    sem_init(&sem_cadeiras, 0, 3);
    sem_init(&sem_escreve_visor, 0, 1);
    sem_init(&sem_le_visor, 0, 0);

    for (i = 0; i < N_BARBEIROS; i++) {
        sem_init(&sem_cad_barbeiro[i], 0, 1);
        sem_init(&sem_cliente_cadeira[i], 0, 0);
        sem_init(&sem_corte_cabelo[i], 0, 0);
    }
    
    for (i = 0; i < N_CLIENTES; i++) {
        id_clientes[i] = i;
        pthread_create(&thread_clientes[i], NULL, func_cliente, (void*) &id_clientes[i]);
    }

    for (i = 0; i < N_BARBEIROS; i++) {
        id_barbeiros[i] = i;
        pthread_create(&thread_barbeiros[i], NULL, func_barbeiro, (void*) &id_barbeiros[i]);
    }    
    
    for (i = 0; i < N_CLIENTES; i++) {
        pthread_join(thread_clientes[i], NULL);  
        // mata os barbeiros
    }
    
    return 0;
}
