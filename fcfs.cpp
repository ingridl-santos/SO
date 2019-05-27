/*  TP - SO
Escalonamento FCFS
Ingrid Santos e João Alberto
 */
#include <bits/stdc++.h>

using namespace std;

//funcao para encontrar o tempo de espera de todos os processos
void encontrarTempoEspera(int processos[], int n, int tempo_duracao[], int tempo_espera[], int tempo_ingresso[]){

  int tempo_execucao[n];
  tempo_execucao[0] = 0;
  tempo_espera[0] = 0;

  // calculo do tempo_espera
  for(int i = 1; i < n; i++) {
    // adiciona tempo_duracao do processo anterior
    tempo_execucao[i] = tempo_execucao[i-1] + tempo_duracao[i-1];

    // encontra tempo de espera para processo atual = soma do tempo_execucao - tempo_ingresso[i]
    tempo_espera[i] = tempo_execucao[i] - tempo_ingresso[i];

    // se tempo_espera do processo for negativo significa que ele já está na fila antes da CPU ficar inativa
    // assim o tempo de espera é 0
    if(tempo_espera[i] < 0) {
      tempo_espera[i] = 0;
    }
  }
}

//funcao para calcular o tempo de resposta
void calcularTempoResposta(int processos[], int n, int tempo_duracao[], int tempo_espera[], int tempo_resposta[]) {
  //calcula o tempo de resposta fazendo tempo_duracao[i] + tempo_espera[i]
  for(int i = 0; i < n; i++) {
    tempo_resposta[i] = tempo_duracao[i] + tempo_espera[i];
  }
}

//funcao para calcular tempo medio de espera e resposta
void calcularTemposMedios(int processos[], int n, int tempo_duracao[], int tempo_ingresso[]){
  int tempo_espera[n], tempo_resposta[n];

  //chamada da funcao pra encontrar o tempo de espera dos processos
  encontrarTempoEspera(processos, n, tempo_duracao, tempo_espera, tempo_ingresso);

  //chamada da funcao para encontrar o tempo de resposta dos processos
  calcularTempoResposta(processos, n, tempo_duracao, tempo_espera, tempo_resposta);

  int tempo_total_espera = 0, tempo_total_resposta = 0;

  for(int i = 0; i < n; i++){
    tempo_total_espera =  tempo_total_espera + tempo_espera[i];
    tempo_total_resposta = tempo_total_resposta + tempo_resposta[i];
  }

  cout << "Tempo medio de execucao: " << float(tempo_total_resposta) / float(n) << "s" << endl;
  cout << "Tempo medio de espera: " << float(tempo_total_espera) / float(n) << "s" << endl;
}

int main() {

  int n;

  cin >> n;

  int numteste = 1;

  while(n!=0){

    int ingresso, duracao;
    int processos[n];
    int indiceProc = 0;
    int tempo_ingresso[n], tempo_duracao[n];
    int contProcs = 0;
    int cont = 0;

    while (cont++ < n) {
      tempo_ingresso[n], tempo_duracao[n];

      while(indiceProc != n) {
        cin >> ingresso >> duracao;

        tempo_ingresso[indiceProc] = ingresso;
        tempo_duracao[indiceProc] = duracao;

        indiceProc++;
      }
    }

    cout << "Teste " << numteste << endl;

    calcularTemposMedios(processos, n, tempo_duracao, tempo_ingresso);

    for(int i = 0; i < n; i++) {
      contProcs++;
      cout << "P" << contProcs << " ";
    }
    cout << '\n';

    cin >> n;

    numteste++;

  }
  return 0;
}
