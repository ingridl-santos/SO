/*  TP1  Sistemas Operacionais
    Arthur Bindá
    Eduardo Lopes
    Ingrid Santos

    gcc leitorEscritor.cpp -o leitorEscritor -lpthread 
    ./leitorEscritor
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>

#define READERS    20       //quantidade de leitores
#define WRITERS    3        //quantidade de escritores

pthread_mutex_t db;         //exclusao mutua para regioes criticas... controla o acesso ao banco de dados
pthread_mutex_t mutex;      //exclusao mutua para regioes cri­ticas... controla o acesso a variável rc
int   rc;                   //quantidade de leitores lendo ou querendo ler a base de dados

// prototipos-------------------------------------

void read_data_base(void);
void use_data_read(void);
void think_up_data(void);

void write_data_base(void);


void reader() {
while (1) {  /* repete eternamente */

  pthread_mutex_lock(&mutex);           //down(&mutex); garante acesso exclusivo a variavelrc
      rc=rc+1;                              //um novo leitor

      if(rc==1)  pthread_mutex_lock(&db);   //caso este seja o primeiro leitor...
      pthread_mutex_unlock(&mutex);         //up(&mutex); libera o acesso a variavel rc

      read_data_base();                     //le a base de dados
      pthread_mutex_lock(&mutex);           //down(&mutex); garante acesso exclusivo a variavel rc
      rc=rc-1;                              //um leitor a menos...

      if(rc==0) pthread_mutex_unlock(&db);  //caso este seja o ultimo leitor...
      pthread_mutex_unlock(&mutex);         //up(&mutex); libera o acesso a variavel rc

      use_data_read();                      //utiliza as informacoes da base de dados para algum trabalho...
    }
}

void writer() {

while(1)            //repete eternamente

    {
    think_up_data();            //pensa em informações para adicionar a base de dados
        pthread_mutex_lock(&db);    //down(&db); garante acesso exclusivo a base de dados
        write_data_base();          //escreve novas informacoes na base de dados

        pthread_mutex_unlock(&db);  //up(&db); libera o acesso a base de dados
    }
}

void read_data_base() {
    /*quanto tempo o leitor permanecerá lendo a base de dados*/
    int readingtime;
    readingtime = rand() % 3;

    printf("Usuário lendo banco de dados. Total de %d leitores lendo agora.\n",rc);
    nanosleep(readingtime);
}
void use_data_read() {

    /*quanto tempo o leitor permanecerá utilizando os dados lidos*/
    int usetime;
    usetime = rand() % 20;

    printf("Usuário utilizando conhecimento adquirido no banco de dados\n");
    nanosleep(usetime);
}
void think_up_data() {

    /*quanto tempo o escritor gasta pensando no que irá escrever*/
    int thinktime;
    thinktime = rand() % 10;

    printf("Escritor pensando no que irá escrever\n");
    nanosleep(thinktime);
}
void write_data_base() {

    /*quanto tempo o escritor gasta escrevendo na base de dados*/
    int writetime;
    writetime = rand() % 6;

    printf("Escritor escrevendo no banco de dados\n");
    nanosleep(writetime);
}


/////MAIN FUNCTION///////////////////////////////
main() {

    pthread_t writerthreads[WRITERS], readerthreads[READERS]; 
    int i;

    //inicializacao dos semaforos...
    pthread_mutex_init(&db, NULL);
    pthread_mutex_init(&mutex, NULL);


    //criação das threads independentes de escritores...
    for(i=0;i<WRITERS;i++){
        pthread_create( &writerthreads[i], NULL,(void *) writer, NULL);
    }

    //criação das threads independentes de leitores...
    for(i=0;i<READERS;i++){
        pthread_create( &readerthreads[i], NULL,(void *) reader, NULL);
    }


    for(i=0;i<WRITERS;i++){
        pthread_join(writerthreads[i], NULL);
    }

    for(i=0;i<READERS;i++){
        pthread_join(readerthreads[i], NULL);
    }
    exit(0);
}
