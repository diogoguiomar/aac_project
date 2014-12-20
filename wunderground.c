/*
 * AAC 2014/2015 - Projecto
 *
 * Grupo 02:
 * Diogo Guiomar - aluno 21302748
 * Miguel Tavares - aluno 21304351
 *
 */
/**
 * Funcoes para ler temperatura e humidade atuais em Lisboa (Wunderground)
 * E' preciso modificar o .h, substituir os 0s pela chave da API do Wunderground
 * Independentemente do intervalo entre chamadas às funcoes de leitura de 
 * temperatura e humidade, so' sera' feito um pedido 'a API do Wunderground a
 * cada 60 segundos (para prevenir que esgotem a vossa quota).
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#ifdef AAC_RASPBERRY
#include <curl/curl.h>
#endif

#include "cJSON/cJSON.h"
#include "wunderground.h"

#ifdef AAC_RASPBERRY
gbuffer_t memo;

int temp_c;
int relative_humidity_int;
char * relative_humidity;

time_t wunder_last_update;

//funcao para uso interno
size_t __save_curl( char *ptr, size_t size, size_t nmemb, void *userdata)
{
	size_t new_size = memo.curr_size + size * nmemb;
	char * new_buffer = malloc(new_size);
	if(memo.curr_size > 0)
		memcpy(new_buffer, memo.buffer, memo.curr_size);
	memcpy(new_buffer + memo.curr_size, ptr, size * nmemb);
	if(memo.curr_size > 0)
		free(memo.buffer);
	memo.buffer = new_buffer;
	memo.curr_size = new_size;
		
	return size * nmemb;
}

//funcao para uso interno
void __curl_refresh()
{
	memo.curr_size = 0;
	if (memo.buffer != NULL) {
		free(memo.buffer);
	}
	CURL * handle = curl_easy_init();
	char* url = LISBOA;
	curl_easy_setopt(handle, CURLOPT_URL, url);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, __save_curl);
	curl_easy_perform(handle);
	curl_easy_cleanup(handle);
}

//funcao para uso interno
int __wunder_refresh()
{
	if (time(NULL) - wunder_last_update >= REFRESH_WUNDERGROUND_SEGUNDOS) {
		__curl_refresh();
		
		char* json = malloc(memo.curr_size + 1);
		memcpy(json, memo.buffer, memo.curr_size);
		*(json + memo.curr_size) = '\0';
		
		cJSON *root = cJSON_Parse(json);
		cJSON *current_observation = cJSON_GetObjectItem(root,"current_observation");
		if (current_observation == NULL) {
			return 0;
		}
		temp_c = cJSON_GetObjectItem(current_observation,"temp_c")->valueint;
		char * rh = cJSON_GetObjectItem(current_observation,"relative_humidity")->valuestring;
		if (relative_humidity != NULL) {
			relative_humidity = malloc(strlen(rh)*sizeof(char)+1);
		}
		memcpy(relative_humidity, rh, strlen(rh)*sizeof(char)+1);
		relative_humidity_int = atoi(relative_humidity);

		cJSON_Delete(root);
		
		time(&wunder_last_update);
	}
	return 1;
}
#endif

//funcao que e' obrigatorio chamar antes da primeira leitura
void wunder_init()
{
#ifdef AAC_RASPBERRY
	time(&wunder_last_update);
	wunder_last_update -= REFRESH_WUNDERGROUND_SEGUNDOS;
	memo.curr_size = 0;
	memo.buffer = NULL;
	relative_humidity = malloc(2 * sizeof(char));
	*relative_humidity = '0';
	*(relative_humidity+1) = '\0';
#endif
}

int wunder_read(uint8_t *humidade_ptr, uint8_t *temperatura_ptr)
{
#ifdef AAC_RASPBERRY
	int sucesso = __wunder_refresh();
	if (sucesso) {
		*humidade_ptr = relative_humidity_int & 0xFF;
		*temperatura_ptr = temp_c & 0xFF;
	}
	return sucesso;
#else
	*humidade_ptr = 60 & 0xFF;
	*temperatura_ptr = 22 & 0xFF;
	return 1;
#endif
}

