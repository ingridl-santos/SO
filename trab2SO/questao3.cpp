#include <omp.h>
#include <vector>
#include <chrono>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
using namespace std;

#define tamanho 5
#define n_threads 10

int main()
{
  srand(time(NULL));
  vector<string> alfabeto {"Ola", "tudo", "bem", "com", "voce", "eu", "sou", "muito", "legal", "caramba", "aprovacao", "tirar", "10", "em", "SO", "acabou", "periodo", "ferias", "sossego", "agua", "praia", "surfar", "ler", "um", "livro", "cinema", "manaus", "amazonas", "fortaleza", "redondinho", "criancada", "ta", "chegando", "ela", "mulher", "assasina", "homiaranha", "hulk", "thor", "TCC", "UFAM"};
  int tam_alfabeto = alfabeto.size();
  // Inicializando o vetor
  string vetor[tamanho];
  for (int i = 0; i < tamanho; i++)
  {
    vetor[i] = "&";
  }

  omp_set_num_threads(n_threads);
  int threads_vetor[n_threads];
  string palavra_escrita[n_threads];
  cout << "meu vetor de threads (com as posições que eu vou acessar)= ";

  for (int i = 0; i < n_threads; i++)
  {
    threads_vetor[i] = rand() % tamanho;
    palavra_escrita[i] = alfabeto[(rand() % tam_alfabeto)];
    cout << "(" << threads_vetor[i] << "," << palavra_escrita[i] << "), ";
  }

  cout << endl;
  string aux;
  int thread_cont;

#pragma omp parallel
  {
    cout << ANSI_COLOR_GREEN "[start]" ANSI_COLOR_RESET " A thread " << omp_get_thread_num() << " começou!" << endl;
    thread_cont = threads_vetor[omp_get_thread_num()];
    aux = vetor[thread_cont] + palavra_escrita[thread_cont] + "-";
    sleep(1);
    vetor[thread_cont] = aux;
    cout << ANSI_COLOR_RED "[end]" ANSI_COLOR_RESET " A thread " << omp_get_thread_num() << " finalizada" << endl;
  }
  cout << "vetor: ";
  for (int i = 0; i < tamanho; i++)
  {
    cout << vetor[i] << " ";
  }
  cout << endl;
}