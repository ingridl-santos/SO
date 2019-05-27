# Sistemas Operarionais

  Trabalhos Práticos
  
- Banheiro
  
  Em uma certa e pequena fábrica de software há apenas um banheiro compartilhado por vários programadores. O banheiro pode ser
  utilizado por até três pessoas ao mesmo tempo. Além disto, temos um funcionário da limpeza, que de tempos em tempos limpa o banheiro, mas só pode entrar no banheiro quando o mesmo está vazio. Além disto, quando o banheiro está sendo limpo, todos os funcionários que por ventura queiram usar o mesmo devem esperar até o banheiro seja limpo.Desta forma, simule o funcionamento  do banheiro usando threads:
  
        Programadores: Devem ser dez threads, e cada uma deve passar no banheiro uma quantidade de tempo tbanheiro,e outra quantidade ttrab trabalhando até a próxima ida ao banheiro.
        Limpeza: Deve ser uma thread, e deve levar tlimp para limpar o banheiro e tesp esperando até a próxima vez para ir no banheiro. Ao sair do banheiro, a thread limpeza deve informar quantas pessoas usaram o banheiro desde a última limpeza.

Todas as threads devem imprimir ao entrar ou sair do banheiro, e sempre que o banheiro está vazio ou cheio.

- Barbeiro Dorminhoco

Em uma barbearia há um ou mais barbeiros, uma cadeira para cada barbeiro atender seus clientes e n cadeiras para espera. Quando não há clientes o barbeiro vai dormir. Quando chega um cliente, este precisa acordar um barbeiro para ser atendido. Se outros clientes chegarem enquanto todos os barbeiros estiverem ocupados, eles se sentarão nas cadeiras e aguardarão sua vez ou caso as cadeiras de espera estejam todas ocupadas os clientes vão embora.

        Faça um programa que coordene as threads barbeiros e clientes. O programa deverá mostrar o “estado” de cada thread, por exemplo, “barbeiro atendendo”, “barbeiro dormindo”, “cliente i esperando” e outras informações como “salão lotado”, etc.

A implementação deve obrigatoriamente incluir 2 (duas) versões, uma usando semáforos e outra usando monitores.

- Escalonamento FCFS e SJF

Entrada

        Seu programa deve ler vários conjuntos de teste. A primeira linha de um conjunto de teste contém um inteiro não negativo, N, que indica o número de processos a serem lidos e colocados na fila de prontos (o valor N = 0 indica o final da entrada). Seguem-se N linhas, cada uma contendo um par de números inteiros não negativos X e Y que representam o tempo de ingresso do processo (X) e o tempo de duração do processo (Y). Os processos são numerados sequencialmente a partir de 1, na ordem em que aparecem na entrada.

Saída

        Para cada conjunto de teste da entrada seu programa deve produzir quatro linhas na saída. A primeira linha deve conter um identificador do conjunto de teste, no formato “Teste n”, onde n é numerado a partir de 1. A segunda linha deve conter o tempo médio de execução de todos os processos desse conjunto de teste, no formato “Tempo medio de execucao: n”, onde n é a média do tempo de execução. A terceira linha deve conter o tempo médio de espera de todos os processos desse conjunto de teste, no formato “Tempo medio de espera: n”, onde n é a média do tempo de espera. A quarta e última linha deve conter a ordem de escalonamento (execução) dos processos, no formato “P1 P2 P3 P4”.

        Exemplo de Entrada (FCFS) | Exemplo de Saída (FCFS)
        4                         |  Teste 1
        0 5                       |  Tempo medio de execução: 8,25s
        0 2                       |  Tempo medio de espera: 4,75s
        1 4                       |  P1 P2 P3 P4
        3 3                       |
        6                         |  Teste 2
        3 1                       |  Tempo medio de execução: 3,6666s
        6 2                       |  Tempo medio de espera: 0,00s
        12 2                      |  P1 P2 P3 P4 P5 P6
        15 4                      |
        24 8                      |
        38 5                      |
        0                         |

        Exemplo de Entrada (SJF) | Exemplo de Saída (SJF)
        4                         |  Teste 1
        0 5                       |  Tempo medio de execução: 6,75s
        0 2                       |  Tempo medio de espera: 3,25s
        1 4                       |  P2 P3 P4 P1
        3 3                       |
        4                         |  Teste 2
        1 6                       |  Tempo medio de execução: 11,00s
        2 6                       |  Tempo medio de espera: 5,75s
        3 3                       |  P1 P3 P3 P2 P4
        5 6                       |
        0                         |

- Escalonamento Round Robin

Entrada

        A primeira linha de um conjunto de teste contém um número inteiro não negativo, M, 
        que indica o valor do quantum a ser utilizado no escalonamento dos processos. Após a
        primeira linha, seu programa deve ler vários conjuntos de teste. Assim, a segunda
        linha contém um número inteiro não negativo, N, que indica o número de processos a
        serem lidos e colocados na fila de prontos (o valor N = 0 indica o final da entrada).
        Seguem-se N linhas, cada uma contendo um par de números inteiros não negativos X e
        Y que representam o tempo de ingresso do processo (X) e o tempo de duração do
        processo (Y). Os processos são numerados sequencialmente a partir de 1, na ordem
        em que aparecem na entrada.

Saída

        Para cada conjunto de teste da entrada seu programa deve produzir quatro linhas na
        saída. A primeira linha deve conter um identificador do conjunto de teste, no formato
        “Teste n”, onde n é numerado a partir de 1. A segunda linha deve conter o tempo
        médio de execução de todos os processos desse conjunto de teste, no formato “Tempo
        medio de execucao: n”, onde n é a média do tempo de execução. A terceira linha deve
        conter o tempo médio de espera de todos os processos desse conjunto de teste, no
        formato “Tempo medio de espera: n”, onde n é a média do tempo de espera. A quarta e
        última linha deve conter a ordem de escalonamento (execução) dos processos, no
        formato “P1 P2 P3 P4”.

        Exemplo de Entrada (Round Robin) | Exemplo de Saída (Round Robin)
        2                                |
        4                                |  Teste 1
        0 5                              |  Tempo medio de execução: 9,75s
        0 2                              |  Tempo medio de espera: 6,25s
        1 4                              |  P1 P2 P3 P1 P4 P3 P1 P4
        3 3                              |
        6                                |  Teste 2
        3 1                              |  Tempo medio de execução: 3,6666s
        6 2                              |  Tempo medio de espera: 0,00s
        12 2                             |  P1 P2 P3 P4 P4 P5 P5 P5 P5 P6 P6 P6
        15 4                             |
        24 8                             |
        38 5                             |
        0                                |

- Alocador de Memória Pessoal

Neste trabalho, vocês farão o seu próprio alocador de memória, com um gerente de memória livre.

Ele será bem simples: No início pedirá um valor N, e alocará N bytes com malloc mesmo. A partir daí, quem usar o alocador poderá pedir memória desta previamente alocada. Desta forma, cabe a ele gerenciar o espaço livre nesta memória, cuidar da segurança (tamanho/número mágico) e a política para escolher onde fazer cada alocação.

O alocador deve ter as seguintes funções implementadas:

__Construtor*__, que recebe o tamanho da memória a ser alocada e uma constante que diz qual a política de alocação (ver código)  

__Aloca__, que recebe um tamanho e retorna um ponteiro para a posição de memória deste tamanho que passe a ser utilizada.

__Verifica__, que recebe um ponteiro e um offset, e verifica se a posição ponteiro+offset já foi previamente alocada, retornando o tamanho desta região alocada se sim, 0 se não

__Libera__, similar à free, libera a memória “alocada” em um ponteiro. Repare que ela não recebe o tamanho da região alocada.

__Destrutor*__, que libera as memórias alocadas.

*Construtor/Destrutor de C++ mesmo.

As alocações podem ser de até 65534 bytes, que é o maior unsigned short int.
