/*  TP1  Sistemas Operacionais
    Arthur Bindá
    Eduardo Lopes
    Ingrid Santos
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS 5           //quantidade de cadeiras na barbearia
#define CONSUMERS 100000    //quantidade total de clientes

/*
typedef   int semaphore; /*os semaforos sao um tipo especial de int
semaphore customers=0;  /*array para controlar o estado de todos
semaphore barbers=0;
semaphore mutex = 1;  /*exclusÃ£o mutua para regioes cri­ticas
semaphore s[N];   /*um semaforo por filosofo
*/

sem_t customers;    //semaforo para controlar os consumidores esperando pelo corte de cabel
sem_t barbers;      //semaforo para controlar os barbeiros esperando pelos consumidores
sem_t mutex;        //semaforo para exclusao mutua para regioes criticas
int waiting=0;


//prototipos...
void cut_hair();
void get_haircut();

void barber()
{

while(1)
{
if(waiting==0) printf("Barber esperando consumidores... \n"); //caso a quantidade de pessoas na barbearia seja 0

     sem_wait(&customers);   //down(&customers); dorme se a quantidade de consumidores for 0
     sem_wait(&mutex);       //down(&mutex); garante acesso exclusivo a variavel waiting
     waiting=waiting-1;      //diminui a quantidade de clientes esperando

     sem_post(&barbers);     //up(&barbers); um barbeiro esta pronto para realizar o corte de cabelo
     sem_post(&mutex);       //up(&mutex); libera o acesso a variavel waiting
     cut_hair();             //corta o cabelo do cliente

 }
}

void customer()
{
sem_wait(&mutex);           //down(&mutex); garante acesso exclusivo a variavel waiting

    if(waiting<CHAIRS)          //se nao houver cadeiras livres, vai embora...
    {
waiting = waiting + 1;  //aumenta a quantidade de clientes esperando

        printf("Mais um consumidor! Total de %d consumidores esperando\n",waiting);
sem_post(&customers);   //up(&customers);acorda o barbeiro avisando que temos um novo cliente
        sem_post(&mutex);       //up(&mutex); libera o acesso a variavel waiting

        sem_wait(&barbers);     //down(&barbers); espera se todos os barbeiros estiverem ocupados
        get_haircut();          //obtem corte de cabelo...
    }
else

{
printf("Cadeiras lotadas... vou embora\n");
sem_post(&mutex);
}
}

void cut_hair()
{

/*Barbeiro esta cortando cabelo*/
printf("Barber is cutting hair\n");
sleep(3);
return;
}

void get_haircut()
{
/*Cliente esta recebendo corte de cabelo*/
sleep(3);
return;
}

main()
{
pthread_t barberthread, consumerthread[CONSUMERS];

int i=0,sleeptime;


// Create independent threads each of which will execute function
/*To initialize a semaphore, use sem_init():
int sem_init(sem_t *sem, int pshared, unsigned int value);
sem_init(&sem_name, 0, 10);
*/
sem_init(&customers, 0, 0);

sem_init(&barbers, 0, 1);
sem_init(&mutex, 0, 1);

pthread_create( &barberthread, NULL,(void *) barber, NULL );

for(i=0;i<CONSUMERS;i++)
{
sleeptime = rand()%5;

sleep(sleeptime);
pthread_create(&consumerthread[i], NULL, (void *) customer, NULL);
}

pthread_join( barberthread, NULL);
for(i=0;i<CONSUMERS;i++){

pthread_join( consumerthread[i], NULL);
}

exit(0);
}

