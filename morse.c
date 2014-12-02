/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo xx:
 * Diogo Guiomar - aluno 21302748
 * Nome aluno - aluno 2xxxxxxx
 *
 * Ficheiro principal de codigo fonte
 */
 // scp -r TP02 pi@192.168.20.2:/home/pi/Desktop
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef AAC_RASPBERRY
#include <wiringPi.h>
#include <softTone.h>
#endif

#include "wunderground.h"
#include "morse.h"
#include "morse_digitos.h"
#include "dht11ler.h"

void confirma()
{
	#ifdef AAC_RASPBERRY
	// desligar LEDs ao sair
	digitalWrite(AMARELO, LOW);
	digitalWrite(VERMELHO, LOW);
	digitalWrite(VERDE, LOW);
	#endif
	printf("Saiu\n");
	exit(0);
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

void ler_temperatura(uint8_t temperatura, uint8_t temperatura_aeroporto)
{
	int digito_1, digito_2;
	// (por fazer) estrutura de controlo para leitura digito a digito
	// decompõe digitos do valor temperatura
	digito_2 = temperatura % 10;
	temperatura /= 10;
	digito_1 = temperatura % 10;

	printf("Temperatura aeroporto: %d C\n", temperatura_aeroporto);
	printf("Temperatura local: %d%d C  ", digito_1, digito_2);
	testar_digito(digito_1);
	separacao_digito();
	testar_digito(digito_2);
	separacao_letra();
	letra_c();
	printf("\n");
}

void ler_humidade(uint8_t humidade, uint8_t humidade_aeroporto)
{
<<<<<<< HEAD
	printf("Humidade local: %d\n", humidade);
	printf("Humidade aeroporto: %d\n", humidade_aeroporto);
	printf("--------------\n");

	#ifdef AAC_RASPBERRY
	double variacao = humidade * PERCENTAGEM;
	if ((humidade_aeroporto < (humidade + variacao)) && (humidade_aeroporto > (humidade - variacao))) {
		digitalWrite(VERMELHO, LOW);
		digitalWrite(VERDE, HIGH);
	} else {
		digitalWrite(VERMELHO, HIGH);
		digitalWrite(VERDE, LOW);
	}
	#endif
=======
		printf("--------------\n");
		printf("Humidade local: %d\n", humidade);
		printf("Humidade aeroporto: %d\n", humidade_aeroporto);

		#ifdef AAC_RASPBERRY
		double variacao = humidade * PERCENTAGEM;
		if ((humidade_aeroporto < (humidade + variacao)) && (humidade_aeroporto > (humidade - variacao))) {
			digitalWrite(VERMELHO, LOW);
			digitalWrite(VERDE, HIGH);
		} else {
			digitalWrite(VERMELHO, HIGH);
			digitalWrite(VERDE, LOW);
		}
		#endif
>>>>>>> 7ab6049793eff5975ab854c5ccd08b9924af331c
}

void ler_dados()
{
	uint8_t humidade = 0, temperatura = 0;
	uint8_t humidade_aeroporto = 0, temperatura_aeroporto = 0;

	uint8_t test1 = wunder_read(&humidade_aeroporto, &temperatura_aeroporto);
	uint8_t test2 = ler_sensor(&humidade, &temperatura);
	
	// verificar erros pelo retorno das funcoes
	if (test1 && test2) {
		ler_humidade(humidade, humidade_aeroporto);
		ler_temperatura(temperatura, temperatura_aeroporto);
	}
	else {
<<<<<<< HEAD
		printf("Erro de leitura.\n");
=======
		printf("Erro de leitura.");
>>>>>>> 7ab6049793eff5975ab854c5ccd08b9924af331c
	}
	alarm(TIMER);
}

int main(int argc, char** argv)
{
	#ifdef AAC_RASPBERRY
	wiringPiSetup();
	pinMode(AMARELO, OUTPUT);
	pinMode(VERMELHO, OUTPUT);
	pinMode(VERDE, OUTPUT);
	softToneCreate(BESOURO);
	#endif

	wunder_init();
	signal(SIGALRM, ler_dados);
	ler_dados();
	signal(SIGINT, confirma);
	for(;;);
}
