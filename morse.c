/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo 02:
 * Diogo Guiomar - aluno 21302748
 * Miguel Tavares - aluno 21304351
 *
 * Ficheiro principal de codigo fonte
 */
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

// função para terminar o programa
void sair()
{
	#ifdef AAC_RASPBERRY
	// desligar LEDs e buzzer ao sair
	digitalWrite(AMARELO, LOW);
	digitalWrite(VERMELHO, LOW);
	digitalWrite(VERDE, LOW);
	softToneWrite(BESOURO, OFF);
	#endif
	printf("Terminado\n");
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
	printf("Humidade local: %d\n", humidade);
	printf("Humidade aeroporto: %d\n", humidade_aeroporto);

<<<<<<< HEAD
	// verifica se as humidades variam mais de 15%
=======
	// se a humidade (aeroporto vs local) variar menos de 15%, acende LED verde
>>>>>>> 2dc903d72d0f0f99124f04589abf514353c40d80
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
		printf("Erro de leitura.\n");
	}
	printf("--------------\n");
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
	signal(SIGINT, sair);
	for(;;);
}
