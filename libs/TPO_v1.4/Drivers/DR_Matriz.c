/*
 * DR_Matriz.c
 *
 *  Created on: 24 sep. 2021
 *      Author: USUARIO
 */
#include "DR_Matriz.h"

void pinsConfig (void)
{
	SetDIR(DIN, SALIDA);
	SetDIR(LOAD, SALIDA);
	SetDIR(CLK, SALIDA);

	//le saco el drain mode a todas las salidas
	SetPINMODE_OUT(IOCON_INDEX_PIO0_13, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_14, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_15, 0);
}

void CLK_Up (void)
{
	SetPIN(CLK, 1);
}
void CLK_Down (void)
{
	SetPIN(CLK, 0);
}
void LOAD_Up (void)
{
	SetPIN(LOAD, 1);
}
void LOAD_Down (void)
{
	SetPIN(LOAD, 0);
}

void matrixInit (void)
{
	uint8_t i;

	LOAD_Down();
	//Shutdown
	for (i=0;i<4;i++)
	{
		sendAddress (12);//0x0C
		sendData (1);
	}
	LOAD_Up();
	//Decode mode
	LOAD_Down();
	for (i=0;i<4;i++)
		{
			sendAddress (9);//0x09
			sendData (0);
		}
	LOAD_Up();
	//scan limit
	LOAD_Down();
	for (i=0;i<4;i++)
		{
			sendAddress (11);//0x0B
			sendData (7);
		}
	LOAD_Up();
	//Brillo
	LOAD_Down();
	for (i=0;i<4;i++)
		{
			sendAddress (10);//0x0A
			sendData (3);//SETTEA EL BRILLO DE LOS LEDS
		}
	LOAD_Up();
	//Display Mode
	LOAD_Down();
	for (i=0;i<4;i++)
		{
			sendAddress(15);//normal mode 0x0F
			sendData(0);
		}
	LOAD_Up();
}


void test1 (void)
{
	uint8_t i;

	LOAD_Down();
	for (i=0;i<4;i++)
	{
		sendAddress(1);
		sendData(0x11);
	}
	LOAD_Up();
}

void test2 (void)
{
	uint8_t i, j;

	for (j=1;j<9;j++)
	{
		LOAD_Down();
		for (i=0;i<4;i++)
		{
			sendAddress (j);//0x0C
			sendData ( numbers2[7][j-1] );	//se pone j-1 para poder hacer coincidir j con los registros a tocar pero dsps se resta 1 por las posiciones de los vectores
			//sendData ( letters[0][j] );
		}
		LOAD_Up();
	}
}


void cleanAll (void)
{
	uint8_t i, j;

	for (j=1;j<9;j++)
	{
		LOAD_Down();
		for (i=0;i<4;i++)
		{
			sendAddress (j);//0x0C
			sendData (0);
		}
		LOAD_Up();
	}
}

void showAll (void)
{
	uint8_t i, j;

	for (j=1;j<9;j++)
	{
		LOAD_Down();
		for (i=0;i<4;i++)
		{
			sendAddress (j);//0x0C
			sendData (0xFF);
		}
		LOAD_Up();
	}
}


void sendAddress (uint8_t adr)//envía los 8 bits primeros D15-D8
{
	//LOAD_Down();//para iniciar la transmición de datos

	uint8_t i;
	for (i=0; i<4; i++)
	{
		CLK_Down();
		SetPIN(DIN, 0);//los primeros 4 bits no importan, los pongo a 0
		CLK_Up();//el bit entra con cada flanco ascendente del clock
	}
	//i=4;//reinicio el contador
	for (i=4; i>0; i--)
	{
		if ( (adr & (0x01<<(i-1))) != 0 )
		{
			CLK_Down();
			SetPIN(DIN, 1);
			CLK_Up();
		}
		else
		{
			CLK_Down();
			SetPIN(DIN, 0);
			CLK_Up();
		}
	}
	/*Se hace de esta manera xq se envian primero los bits D11 al D8, en ese orden*/
}

/**/
void sendData (uint8_t data)//envía los últimos 8 bits D8-D0
{
	uint8_t i;

	for (i=8; i>0; i--)
	{
		if ( (data & (0x01<<(i-1))) != 0 )
		{
			CLK_Down();
			SetPIN(DIN, 1);
			CLK_Up();
		}
		else
		{
			CLK_Down();
			SetPIN(DIN, 0);
			CLK_Up();
		}
	}
	/*De esta manera envío desde el bit D7 al D0, empiezo por el bit mas significativo de la data*/
	CLK_Down();
	//LOAD_Up();//se tiene que terminar la función con esto, sinó no se cargan los valores en los registros
}



