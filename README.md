# Sistemas Operarionais
  Trabalhos Práticos
  
  - Banheiro
  
  Em uma certa e pequena fábrica de software há apenas um banheiro compartilhado por vários programadores. O banheiro pode ser 
  utilizado por até três pessoas ao mesmo tempo. Além disto, temos um funcionário da limpeza, que de tempos em tempos limpa o 
  banheiro, mas só pode entrar no banheiro quando o mesmo está vazio. Além disto, quando o banheiro está sendo limpo, todos os 
  funcionários que por ventura queiram usar o mesmo devem esperar até o banheiro seja limpo.Desta forma, simule o funcionamento
  do banheiro usando threads:
  
    Programadores: Devem ser dez threads, e cada uma deve passar no banheiro 
    uma quantidade de tempo tbanheiro,e outra quantidade ttrab trabalhando até a próxima ida ao banheiro.
    
    Limpeza: Deve ser uma thread, e deve levar tlimp para limpar o banheiro e tesp esperando até a próxima 
    vez para ir no banheiro. Ao sair do banheiro, a thread limpeza deve informar quantas pessoas usaram o 
    banheiro desde a última limpeza.

Todas as threads devem imprimir ao entrar ou sair do banheiro, e sempre que o banheiro está vazio ou cheio.

 - Barbeiro Dorminhoco 
 
Em uma barbearia há um ou mais barbeiros, uma cadeira para cada barbeiro atender seus clientes e n cadeiras para espera. 
Quando não há clientes o barbeiro vai dormir. Quando chega um cliente, este precisa acordar um barbeiro para ser atendido. 
Se outros clientes chegarem enquanto todos os barbeiros estiverem ocupados, eles se sentarão nas cadeiras e aguardarão sua vez 
ou caso as cadeiras de espera estejam todas ocupadas os clientes vão embora.

    Faça um programa que coordene as threads barbeiros e clientes. O programa deverá mostrar o “estado” de 
    cada thread, por exemplo, “barbeiro atendendo”, “barbeiro dormindo”, “cliente i esperando” e outras 
    informações como “salão lotado”, etc.

A implementação deve obrigatoriamente incluir 2 (duas) versões, uma usando semáforos e outra usando monitores. 

Sugerimos a utilização da linguagem Java usando a classe Thread para a solução com monitores e C ou C++, por meio das 
bibliotecas “pthread” e “semaphore” para a solução com semáforos.
