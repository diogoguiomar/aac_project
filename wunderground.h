/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo 02:
 * Diogo Guiomar - aluno 21302748
 * Miguel Tavares - aluno 21304351
 *
 */
#ifndef __WUNDERGROUND_H
#define __WUNDERGROUND_H

#define LISBOA "http://api.wunderground.com/api/85055ca574cf575b/conditions/q/zmw:00000.3.08579.json"
#define REFRESH_WUNDERGROUND_SEGUNDOS 60

typedef struct gbuffer {
	size_t curr_size;
	char* buffer;
} gbuffer_t;


void wunder_init();
int wunder_read(uint8_t *humidade_ptr, uint8_t *temperatura_ptr);

#endif
