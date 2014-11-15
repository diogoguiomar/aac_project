/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo xx:
 * Nome aluno - aluno 2xxxxxxx
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



void ler_temperatura() {
	uint8_t humidade = 0, temperatura = 0; 
	ler_sensor(&humidade, &temperatura);
	//printf("Humidade: %d  ||  Temperatura: %d\n", humidade, temperatura);
	alarm(TIMER);
}

int main(int argc, char** argv)
{
// receber temperatura

  for(;;);
}

// sscanf - %d%d
// imprime_morse(int d)
//		case d
//		case 2 // imprime_morse_2
// -----
// 	
// 
