aac_project
===========

Projecto final - ficha de entrega

Grupo número 02:

- Diogo Guiomar, aluno n.º 21302748

- Miguel Tavares, aluno n.º 21304351

I - COMPILAÇÃO

1. Quando emitido o comando:

   make morse

   o projecto compila sem erros quer num PC quer num Raspberry Pi? SIM

2. Quando emitido o comando:

   make -B AAC_RASPBERRY=1 morse

   o projecto compila sem erros num Raspberry Pi? SIM

II - HUMIDADE

3. O programa lê e apresenta no ecrã a humidade do sensor? SIM

4. O programa lê e apresenta no ecrã a humidade observada no aeroporto de Lisboa? SIM

5. O programa acende o LED verde ou vermelho conforme descrito no enunciado? SIM

6. Quando não é possível ler um dos valores o programa mantém o estado anterior dos LEDs verde e vermelho? SIM

III - TEMPERATURA

7. O programa lê e apresenta no ecrã a temperatura do sensor? SIM

8. O programa lê e apresenta no ecrã a temperatura observada no aeroporto de Lisboa? SIM

9. O programa traduz a temperatura para código Morse? SIM

10. O programa apresenta no ecrã uma representação gráfica da transmissão em Morse (pontos, traços e espaços)? SIM

11. O programa transmite a temperatura em código Morse no LED amarelo? SIM

IV - LEDs

12. O programa apaga todos os LEDs utilizados quando o utilizador prime Ctrl+C? SIM

13. O programa está configurado assumindo as seguintes correspondências entre LEDs e pinos:

a. LED vermelho: #24 (pino 5 do wiringPi)

b. LED verde: #25 (pino 6 do wiringPi)

c. LED amarelo (Morse): #23 (pino 4 do wiringPi)

d. Besouro (morse): #18 (pino 1 do wiringPi)

V - OBSERVAÇÕES

Indicar aqui observações relevantes para a avaliação do trabalho.

Foi criado um morse_digitos.c com a finalidade de conter todas as funções relativas aos numeros/letra/ponto/traço.

Foi acrescentado um besouro complementando a transmissão morse feita pelo LED amarelo (em simultâneo)
Para tal, foi incluído a biblioteca <softTone.h> e utilizadas as funções softToneCreate(int pin) e softToneWriter(int pin, int freq)

Nas fotos da montagem foi utilizado um raspberry pi gpio extension board v2.2, diferente daquele utilizados nas aulas.

Na última parte do video, foi adicionada uma linha de código "humidade += 40" (morse.c linha 101) com o intuito de a diferença das humidades ser inferior a 15% e então a LED verde acender
http://youtu.be/Twgb64sIBcA

Link para o repositório (tornado público a partir de 21 Dezembro, 23:55):
https://github.com/Wyve/aac_project
