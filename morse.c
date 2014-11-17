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

void ler_temperatura() 
{
	int digito_1, digito_2;
	uint8_t humidade = 0, temperatura = 0; 
	
	ler_sensor(&humidade, &temperatura);
	
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
	
	alarm(TIMER);
}

void ler_dados() 
{

}

int main(int argc, char** argv)
{
	// incompleto
	signal(SIGALRM, ler_temperatura);
	ler_temperatura();
	for(;;);
}

