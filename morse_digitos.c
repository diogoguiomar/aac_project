#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>

#ifdef AAC_RASPBERRY
#include <wiringPi.h>
#endif

#include "morse.h"
#include "morse_digitos.h"

void traco()
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, HIGH);
	delay(TRACO);
	#endif
	printf("-");
}

void ponto()
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, HIGH);
	delay(PONTO);
	#endif
	printf(".");
}

void separacao_traco()
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, LOW);
	delay(SEPARACAO_TRACO);
	#endif
}

void separacao_digito()
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, LOW);
	delay(SEPARACAO_DIGITO);
	#endif
	printf("  ");
}

void separacao_letra()
{
	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, LOW);
	delay(SEPARACAO_LETRA);
	#endif
	printf("  ");
}

void digito_0()
{
	int i;
	for (i = 0; i <= 5; i++) {
		traco();
		if (i == 4) break;
		separacao_traco();
	}
}

void digito_1()
{
	int i;
	ponto();
	separacao_traco();
	for (i = 0; i <= 4; i++) {
		traco();
		if (i == 3) break;
		separacao_traco();
	}
}

void digito_2()
{
	int i;
	for (i = 0; i <= 2; i++) {
		ponto();
		separacao_traco();
	}

	for (i = 0; i <= 3; i++) {
		traco();
		if (i == 2) break;
		separacao_traco();
	}
}

void digito_3()
{
	int i;
	for (i = 0; i <= 3; i++) {
		ponto();
		separacao_traco();
	}

	for (i = 0; i <= 2; i++) {
		traco();
		if (i == 1) break;
		separacao_traco();
	}
}

void digito_4()
{
	int i;
	for (i = 0; i <= 4; i++) {
		traco();
		separacao_traco();
	}
	ponto();
}

void digito_5()
{
	int i;
	for (i = 0; i <= 5; i++) {
		ponto();
		if (i == 4) break;
		separacao_traco();
	}
}

void digito_6()
{
	int i;
	traco();
	for (i = 0; i <= 4; i++) {
		ponto();
		if (i == 3) break;
		separacao_traco();
	}
}

void digito_7()
{
	int i;
	for (i = 0; i <= 2; i++) {
		traco();
		separacao_traco();
	}

	for (i = 0; i <= 3; i++) {
		ponto();
		if (i == 2) break;
		separacao_traco();
	}
}

void digito_8()
{
	int i;
	for (i = 0; i <= 3; i++) {
		traco();
		separacao_traco();
	}

	for (i = 0; i <= 2; i++) {
		ponto();
		if (i == 1) break;
		separacao_traco();
	}
}

void digito_9()
{
	int i;
	for (i = 0; i <= 4; i++) {
		ponto();
		separacao_traco();
	}
	traco();
}

void letra_c()
{
	int i;
	for (i = 0; i <= 2; i++) {
		traco();
		separacao_traco();
		ponto();
	}

	#ifdef AAC_RASPBERRY
	digitalWrite(AMARELO, LOW);
	#endif
}
