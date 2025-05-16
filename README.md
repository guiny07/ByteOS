# ByteOS

Projeto desenvolvido para a disciplina de Sistemas Operacionais do curso de Ciência da Computação.

# 

O projeto consiste na implementação de um simulador de núcleo de um SO, com uma interface gráfica que permita escolhas por parte de quem executa a simulação. 

O desenvolvimento será realizado na linguagem C, utilizando bibliotecas de programação concorrente como pthread e semaphore. 
A interface gráfica será via terminal, com o uso da biblioteca ncurses.

# 

A implementação do "núcleo" do SO partirá da codificação das threads definidas a seguir. A chamada por uma delas será controlada através de duas funções principais: 

- interruptControl() - acionada na ocorrência de eventos externos aos processos sendo executados.
- sysCall() - acionada na ocorrência de eventos gerados pelos processos executados.

A partir da execução dessas funções o núcleo ativará a thread correspondente, bem como o escalonamento do próximo processo usando o algoritmo de escalonamento. 

Os evetnso a serem tratados pelo núcleo são: 

1. processInterrupt(1) - interrupção gerada pela execução da função ProcessCreate e pelo término de operações de E/S.
2. semaphoreP(10) - tratamento de bloqueio de processo.
3. semaphoreV(11) - tratamento de desbloquieo de processo.
4. DiskRequest(4) - chamada de operação de entrada/saída para disco.
5. DiskFinish(5) - sinalização de final de E/S para disco.
6. PrintRequest(14) - chamada de operação de entrada/saída para impressão.
7. PrintFinish(15) - sinalização de final de E/S para impressão.
8. memLoadReq(6) - chamada de operação de carregamento na memória.
9. memLoadFinish(7) - sinalização de final de carregamento.
10. fsRequest(8) - chamada para operação no sistema de arquivos.
11. fsFinish(9) - sinalização de final de operação no sistema de arquivos.
12. processCreate(2) - chamada para iniciar a criação de um processo no BCP*
13. processFinish(3) - chamada para terminar a existência de um processo no BCP*

*BCP (Bloco de Controle de Processos) é a estrutura que armazena os dados dos processos em execução.

# 

A estruturação do projeto será por bibliotecas bem definidas, sendo cada uma para implementação de uma parte do sistema, proporcionando a modularização e encapsulamento das funcionalidades. 
