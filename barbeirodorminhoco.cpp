/*  TP1  Sistemas Operacionais
    Arthur Bindá
    Eduardo Lopes
    Ingrid Santos

    Execução: g++ barbeirodorminhoco.cpp -pthread -o barbeiros && ./barbeiros


    Fontes: https://www.youtube.com/watch?v=AaQ2uOsLUJ4
            http://www.ic.unicamp.br/~islene/2s2007-mo806/barbeiro/barbeiro.pdf
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_CLIENTES 20
#define N_CADEIRAS 5 
#define N_BARBEIROS 3

sem_t sem_cadeiras;                         // cadeiras de espera
sem_t sem_cad_barbeiro[N_BARBEIROS];        // cadeiras dos barbeiros
sem_t sem_corte_cabelo[N_BARBEIROS];        // corte de cabelo feito
sem_t sem_cliente_cadeira[N_BARBEIROS];     // sem fila de espera

sem_t sem_escreve_visor, sem_le_visor;
int visor;

void* func_barbeiro(void *v) {
    int id = * (int*) v;
    while(1) {
        sem_wait(&sem_escreve_visor);       // espera ter cliente
        visor = id;                         // avisa que ta livre
        sem_post(&sem_le_visor);            // avisa que ta acordado
        sem_wait(&sem_cliente_cadeira[id]); // espera cliente alocar na cadeira
        sleep(random()%3);                  // realiza atendimento
        printf("Barbeiro %d cortou cabelo de um cliente. \n", id);  
        sem_post(&sem_corte_cabelo[id]);    // avisa que terminou de cortar
 
    }
    return NULL;
}

void* func_cliente(void *v) {
    int id = *(int*) v;
    int minha_cadeira;

    sleep(random()%3);
    if (sem_trywait(&sem_cadeiras) == 0) {                      // tenta entrar e sentar 
        printf("Cliente %d entrou na barbearia.\n", id);        
        sem_wait(&sem_le_visor);                                // espera algum barbeiro indicar que ta dormindo
        minha_cadeira = visor;                                  // ve qual barbeiro indicou que ta dormindo
        sem_post(&sem_escreve_visor);                           // avisa que ta pronto pra ser atendido
        sem_wait(&sem_cad_barbeiro[minha_cadeira]);             // espera barbeiro acordar e ser atendido
        printf("Cliente %d sentou na cadeira do barbeiro %d. \n", id, minha_cadeira);
        sem_post(&sem_cliente_cadeira[minha_cadeira]);          // avisa que ta na cadeira
        sem_post(&sem_cadeiras);                                // deixa cadeira
        sem_wait(&sem_corte_cabelo[minha_cadeira]);             // aguarda barbeiro finalizar o corte
        sem_post(&sem_cad_barbeiro[minha_cadeira]);             // deixa cadeira do barbeiro
        printf("Cliente %d deixou a barbearia.\n", id);
    } else {
        printf("Cliente %d não entrou na barbearia.\n", id);    // nao tem cadeiras vagas
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    pthread_t thread_clientes[N_CLIENTES], thread_barbeiros[N_BARBEIROS];
    int i, id_clientes[N_CLIENTES], id_barbeiros[N_BARBEIROS];

    sem_init(&sem_cadeiras, 0, 5);              // cadeiras
    sem_init(&sem_escreve_visor, 0, 1);
    sem_init(&sem_le_visor, 0, 0);
    
    // inicia semaforos
    for (i = 0; i < N_BARBEIROS; i++) {
        sem_init(&sem_cad_barbeiro[i], 0, 1);
        sem_init(&sem_cliente_cadeira[i], 0, 0);
        sem_init(&sem_corte_cabelo[i], 0, 0);
    }
    
    // cria os clientes
    for (i = 0; i < N_CLIENTES; i++) {
        id_clientes[i] = i;
        pthread_create(&thread_clientes[i], NULL, func_cliente, (void*) &id_clientes[i]);
    }

    // cria os barbeiros
    for (i = 0; i < N_BARBEIROS; i++) {
        id_barbeiros[i] = i;
        pthread_create(&thread_barbeiros[i], NULL, func_barbeiro, (void*) &id_barbeiros[i]);
    }    
    
    // encerra os clientes
    for (i = 0; i < N_CLIENTES; i++) {
        pthread_join(thread_clientes[i], NULL);  
    }
    
    return 0;
}
