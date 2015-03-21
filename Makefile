# Para compilar o programa para correr sem LEDs e com leituras dummy (PC ou Raspberry):
#      make morse
#
# Para compilar o programa para correr com LEDs e leituras reais (so Raspberry);
#      make -B AAC_RASPBERRY=1 morse


CFLAGS = -Wall
LDFLAGS = -lm

ifdef AAC_RASPBERRY
LDFLAGS += -lcurl -lwiringPi
CFLAGS += -DAAC_RASPBERRY=$(AAC_RASPBERRY)
endif

morse: morse.c morse_digitos.c dht11ler.c wunderground.c cJSON/cJSON.c
	gcc $(CFLAGS) -o morse morse.c morse_digitos.c dht11ler.c cJSON/cJSON.c wunderground.c $(LDFLAGS)

clean:
	rm morse
