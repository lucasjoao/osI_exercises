Capítulo de entrada / saída

Perguntas:
5. Um controlador de DMA tem cinco canais. Ele é capaz de solicitar uma palavra de 32 bits a cada 40 nsec. A resposta dessa solicitação demora 40 nsec. O quão rápido o barramento (bus) deve ser para evitar um "congestionamento"? **não irei usar essa**
8. Suponha que um computador consiga ler ou escrever uma palavra da memória em 5 nsec. Também considere que quando uma interrupção ocorre, todos os 32 registradores da CPU mais o contador de programa (program counter) e o PSW são colocados na pilha (stack). Com isso, qual é o número máximo de interrupções por segundo que esse computador consegue processar?
17. Considere um disco rígido com 200 setores de 512 bytes em cada trilha. Quanto de *cylinder skew* é necessário para um disco com 7200 RPM (rotações por minuto) que possui um tempo de "procura de trilha-para-trilha" (track-to-track seek time) de 1 msec?
21.

Respostas:
5. Provavelmente https://spcl.inf.ethz.ch/Teaching/2015-osnet/assignments/soln6.pdf do que C. Pensar!
8. Estilo K e http://stst.elia.pub.ro/news/SO/Modern%20Operating%20System%20-%20Tanenbaum.pdf. Opções
17. Estilo K e C. Resposta deve ser um número
21. Estilo K e C.
