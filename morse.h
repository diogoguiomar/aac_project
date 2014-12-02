/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo 02:
 * Diogo Guiomar - aluno 21302748
 * Miguel Tavares - aluno 21304351
 *
 */
 
#ifndef __MORSE_H
#define __MORSE_H

#define PONTO 100
#define TRACO 300
#define SEPARACAO_TRACO 100
#define SEPARACAO_DIGITO 300
#define SEPARACAO_LETRA 700
#define TIMER 15
#define PERCENTAGEM 0.15
#define FREQ 1046
#define OFF 0

#define BESOURO 1 // 18
#define AMARELO 4 // 23
#define VERDE 6 // 25
#define VERMELHO 5 // 24

void confirma();

void testar_digito();

void ler_temperatura(uint8_t temperatura, uint8_t temperatura_aeroporto);

void ler_humidade(uint8_t humidade, uint8_t humidade_aeroporto);

void ler_dados();

#endif
