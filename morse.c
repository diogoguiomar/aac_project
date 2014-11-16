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
#include "dht11ler.h"


void traco() 
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, HIGH);
	#endif
	delay(TRACO);
}

void ponto() 
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, HIGH);
	#endif
	delay(PONTO);
}

void separacao_traco() 
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, LOW);
	#endif
	delay(SEPARACAO_TRACO);
}

void separacao_digito() 
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, LOW);
	#endif
	delay(SEPARACAO_DIGITO)
}

void digito_0() 
{
	for (int i = 0; i <= 5; i++) {
		traco();
		if (i == 4) break;
		separacao_traco();
	}
}

void digito_1() 
{
	ponto();
	separacao_traco();
	for (int i = 0; i <= 4; i++) {
		traco();
		if (i == 3) break;
		separacao_traco();
	}
}

void digito_2() 
{
	for (int i = 0; i <= 2; i++) {
		ponto();
		separacao_traco();
	}
	
	for (int j = 0; j <= 3; j++) {
		traco();
		if (j == 2) break;
		separacao_traco();
	}
}

void digito_3() 
{
	for (int i = 0; i <= 3; i++) {
		ponto();
		separacao_traco();
	}
	
	for (int j = 0; j <= 2; j++) {
		traco();
		if (j == 1) break;
		separacao_traco();
	}
}

void digito_4() 
{
	for (int i = 0; i <= 4; i++) {
		traco();
		separacao_traco();
	}
	ponto();
}

void digito_5() 
{
	for (int i = 0; i <= 5; i++) {
		ponto();
		if (i == 4) break;
		separacao_traco();
	}
}

void digito_6() 
{
	traco();
	for (int i = 0; i <= 4; i++) {
		ponto();
		if (i == 3) break;
		separacao_traco();
	}
}

void digito_7() 
{
	for (int i = 0; i <= 2; i++) {
		traco();
		separacao_traco();
	}
	
	for (int j = 0; j <= 3; j++) {
		ponto();
		if (j == 2) break;
		separacao_traco();
	}
}

void digito_8() 
{
	for (int i = 0; i <= 3; i++) {
		traco();
		separacao_traco();
	}
	
	for (int j = 0; j <= 2; j++) {
		ponto();
		if (j == 1) break;
		separacao_traco();
	}
}

void digito_9() 
{
	for (int i = 0; i <= 4; i++) {
		ponto();
		separacao_traco();
	}
	traco();
}

void digito_c() 
{
	traco();
	separacao_traco();
	ponto();
	separacao_traco();
	traco();
	separacao_traco();
	ponto();
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
	case 9:
		digito_9();
		break;
	}
}

void ler_temperatura() 
{
	int digito_1, digito_2;
	uint8_t humidade = 0, temperatura = 0; 
	ler_sensor(&humidade, &temperatura);
	sscanf(humidade, %d%d, digito_1, digito_2);
	//printf("Humidade: %d  ||  Temperatura: %d\n", humidade, temperatura);
	alarm(TIMER);
}

int main(int argc, char** argv)
{
// receber temperatura

  for(;;);
}

