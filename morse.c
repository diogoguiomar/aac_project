/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo xx:
 * Diogo Guiomar - aluno 21302748
 * Nome aluno - aluno 2xxxxxxx
 *
 * Ficheiro principal de codigo fonte
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>

#ifdef AAC_RASPBERRY
#include <wiringPi.h>
#endif

#include "wunderground.h"
#include "morse.h"
#include "morse_digitos.h"
#include "dht11ler.h"

void confirma()
{
	char resp[4];
	printf("Deseja mesmo sair? (sim para sair)\n");
	scanf("%3s",resp);
	if(strcmp("sim",resp)) {
		printf("Nao saiu\n");
	} else {
		#ifdef AAC_RASPBERRY
		// desligar LEDs ao sair
		digitalWrite(AMARELO, LOW);
		digitalWrite(VERMELHO, LOW);
		digitalWrite(VERDE, LOW);
		#endif
		printf("Saiu\n");
		exit(0);
	}
}

void testar_digito(int digito)
{
	switch(digito)
	{
	case 0:
		digito_0();
		break;
	case 1:
		digito_1();
		break;
	case 2:
		digito_2();
		break;
	case 3:
		digito_3();
		break;
	case 4:
		digito_4();
		break;
	case 5:
		digito_5();
		break;
	case 6:
		digito_6();
		break;
	case 7:
		digito_7();
		break;
	case 8:
		digito_8();
		break;
	default:
		digito_9();
		break;
	}
}

void ler_temperatura(int temperatura)
{
	int digito_1, digito_2;
	// (por fazer) estrutura de controlo para leitura digito a digito
	// decompõe digitos do valor temperatura
	digito_2 = temperatura % 10;
	temperatura /= 10;
	digito_1 = temperatura % 10;

	printf("Temperatura local: %d%d C  ", digito_1, digito_2);
	testar_digito(digito_1);
	separacao_digito();
	testar_digito(digito_2);
	separacao_letra();
	letra_c();
	printf("\n");
}

void ler_humidade(int humidade)
{
	int humidade_aeroporto = 0;
	double variacao = humidade + (humidade * PERCENTAGEM);

	// (por fazer) receber valores do aeroporto

	printf("Humidade local: %d\n", humidade);
	printf("Humidade aeroporto: %d\n", humidade_aeroporto);

	if ((variacao < humidade_aeroporto) || (variacao > humidade_aeroporto)) {
		// (por fazer) acende vermelho
	} else {
		// (por fazer) acende verde
	}

	// (por fazer) se a leitura falha, manter o ultimo estado
}

void ler_dados()
{
	uint8_t humidade = 0, temperatura = 0;

	ler_sensor(&humidade, &temperatura);
	ler_humidade(humidade);
	ler_temperatura(temperatura);
	alarm(TIMER);
}

int main(int argc, char** argv)
{
	#ifdef AAC_RASPBERRY
	wiringPiSetup();
	pinMode(AMARELO, OUTPUT);
	pinMode(VERMELHO, OUTPUT);
	pinMode(VERDE, OUTPUT);
	#endif

	signal(SIGALRM, ler_dados);
	ler_temperatura();
	signal(SIGINT, confirma);
	for(;;);
}
