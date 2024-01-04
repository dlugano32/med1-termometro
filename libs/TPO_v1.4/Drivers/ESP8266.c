/*
 * ESP8266_conf.c
 *
 *  Created on: 17 nov. 2021
 *      Author: d_lugano
 */
#include "ESP8266.h"

uint8_t stage=0;

char * comando[CANT_COMANDOS]=
{	 	//"AT\r\n"
		//"AT+CWMODE=1\r\n"
		//,"AT+CWJAP=\"Fibertel WiFi982 2.4GHz\",\"0141832376\"\r\n"
		//,"AT+CWJAP=\"DAMI\",\"zonaportatil\"\r\n"
		//"AT+CWJAP=\"Juanse\",\"SUMO2001\"\r\n"
		"AT+CIPMUX=1\r\n"
		,"AT+CIPSTART=1,\"TCP\",\"192.168.43.234\",4000\r\n"	//FINAL
		//,"AT+CIPSTART=1,\"TCP\",\"192.168.43.180\",4000\r\n"	//Casa
		//,"AT+CIPSTART=1,\"TCP\",\"192.168.0.72\",4000\r\n"	//Casa PC
		//,"AT+CIPSTART=1,\"TCP\",\"192.168.1.105\",4000\r\n"	//Juanse pero mi pc
		//,"AT+CIPSTART=1,\"TCP\",\"192.168.1.102\",4000\r\n"	//Juanse
		,"AT+CIPSEND=1,5\r\n"
		,"READY"
};

void InitESP8266_conf(void)
{
	flagT5=0;
	stage=0;
}


uint8_t Esp8266_conf(void)
{
	static uint8_t estado = TRANSMISION;
	uint8_t ret=0;
	static uint8_t stage=0;

	switch(estado)
	{
		case TRANSMISION:

			if(flagT5==1)
			{
				TxSerie1((uint8_t *)comando[stage]);
				flagT5=0;
				stage++;
				estado=CHECKING;
			}

			break;

		case CHECKING:
			if(stage==CANT_COMANDOS)
			{
				ret=1;	//Aca es cuando salgo
				flagT5=0;
				stage=0;
				estado=TRANSMISION;
			}
			else
			{
				estado=TRANSMISION;
				TimerStart(5, 1000, handlerT5, MILI);
			}
			break;

		default:
			estado=CHECKING;
	}

	return ret;
}

