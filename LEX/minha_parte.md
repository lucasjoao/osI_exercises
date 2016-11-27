Capítulo de entrada / saída

Perguntas:
5. Um controlador de DMA tem cinco canais. Ele é capaz de solicitar uma palavra de 32 bits a cada 40 nsec. A resposta dessa solicitação demora 40 nsec. O quão rápido o barramento (bus) deve ser para evitar um "congestionamento"? **não irei usar essa**
8. Suponha que um computador consiga ler ou escrever uma palavra da memória em 5 nsec. Também considere que quando uma interrupção ocorre, todos os 32 registradores da CPU mais o contador de programa (program counter) e o PSW são colocados na pilha (stack). Com isso, qual é o número máximo de interrupções por segundo que esse computador consegue processar?
17. Considere um disco rígido com 200 setores de 512 bytes em cada trilha. Quanto de desvio de cilindro (cylinder skew) é necessário para um disco com 7200 RPM (rotações por minuto) que possui um tempo de "procura de trilha-para-trilha" (track-to-track seek time) de 1 msec?
21. Um RAID pode falhar se dois ou mais dispositivos quebrarem dentro de um curto intervalo de tempo. Suponha que a propabilidade de um dispositivo quebrar em uma certa hora é p. Qual é a probabilidade de um RAID de k dispositivos (k-drive RAID) falhar nessa certa hora?

Respostas:
8. "Uma interrupção faz com que 34 (32 + PC + PSW) palavras sejam colocadas na pilha. Retornar da interrupção requer que 34 palavras sejam pegas da pilha. Esse processo de "ida e volta" leva 340 nsec (5 nsec * 68 palavras). Como 1 nsec = 10^9 segundos, o máximo de interrupção por segundo que o computador consegue processar é (10^9) / 340."
17. "Em 1 minuto o disco faz 7200 rotações. Então em 1s é feito 120 rotações. Já em 1msec é feito 0,12 rotação. Com isso, basta uma regra de três:
1 <-> 200
0,12 <-> x
x = 24"
21. "A probabilidade de zero falha é: P0 = (1 - P)^k. A probabilidade de uma falha é: P1 = kP(1 - P)^(k - 1). Então a probabilidade do RAID falhar é: 1 - P0 - P1. Ou seja, 1 - (1 - P)^k - kP(1 - P)^(k - 1)"
