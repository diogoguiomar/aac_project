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

void ler_temperatura(uint8_t temperatura)
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

void ler_humidade(uint8_t humidade, uint8_t humidade_aeroporto)
{
	// caso exista algum erro na leitura dos sensores, o valor devolvido e' 0 (zero)
	if (!(humidade_aeroporto && humidade)) {

		double variacao = humidade + (humidade * PERCENTAGEM);

		printf("Humidade local: %d\n", humidade);
		printf("Humidade aeroporto: %d\n", humidade_aeroporto);

		#ifdef AAC_RASPBERRY
		if ((variacao < humidade_aeroporto) || (variacao > humidade_aeroporto)) {
			digitalWrite(VERMELHO, HIGH);
			digitalWrite(VERDE, LOW);
		} else {
			digitalWrite(VERMELHO, LOW);
			digitalWrite(VERDE, HIGH);
		}
		#endif
	}
}

void ler_dados()
{
	uint8_t humidade = 0, temperatura = 0;
	uint8_t humidade_aeroporto = 0, temperatura_aeroporto = 0;

	wunder_read(&humidade_aeroporto, &temperatura_aeroporto);
	ler_sensor(&humidade, &temperatura);
	ler_humidade(humidade, humidade_aeroporto);
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

	wunder_init();
	signal(SIGALRM, ler_dados);
	ler_temperatura();
	signal(SIGINT, confirma);
	for(;;);
}
