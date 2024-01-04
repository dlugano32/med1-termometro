/*
 * DR_teclado.c
 *
 *  Created on: 16 sep. 2021
 *      Author: d_lugano
 */

#include "DR_teclado.h"

uint8_t Tecla=NO_KEY;

void InitTeclado(void)
{
	SYSCON->SYSAHBCLKCTRL0|=(1<<7);		//Habilito la SWM
	PINENABLE0|=(1<<7);	//Desactivo funcion especial PIO0_8
	PINENABLE0|=(1<<8);	//Desactivo funcion especial PIO0_9

	//Entradas Botones Alfombra
	SetDIR(SW_SEL, 	ENTRADA);
	SetDIR(SW_LEFT, ENTRADA);
	SetDIR(SW_DOWN, ENTRADA);
	SetDIR(SW_UP, 	ENTRADA);
	SetDIR(SW_RIGHT,ENTRADA);
	SetDIR(SW_ST, 	ENTRADA);

	//Con pull-ups
	SetPINMODE_OUT(IOCON_INDEX_PIO0_26, 0x02);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_27, 0x02);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_28, 0x02);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_29, 0x02);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_9, 0x02);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_8, 0x02);
}

void DriverTecladoSW(void)
{
	static uint8_t lastKey=NO_KEY;
	static uint8_t cont=0;
	uint8_t key;	//Tecla no presionada

	key=DriverTecladoHW();	//Devuelve la tecla que esta siendo presionada

	if( lastKey==key && cont < DEBOUNCE_COUNT)
	{
		cont++;	//Cuenta cuantos milisegundos esta presionada la tecla
		if(cont == DEBOUNCE_COUNT)
		{
			Tecla=key;	//Es decir, se esta presionando el boton. La variable Tecla es global y es la que va a estar devolviendo mi primitiva
		}
	}
	else if(key!= lastKey)
	{
		cont=0;
	}

	lastKey=key;
}

uint8_t DriverTecladoHW(void)
{
	if( !GetPIN(SW_SEL) )
		return SELECT;

	if( !GetPIN(SW_LEFT) )
		return LEFT_ARROW;

	if( !GetPIN(SW_DOWN) )
		return DOWN_ARROW;

	if( !GetPIN(SW_UP) )
		return UP_ARROW;

	if( !GetPIN(SW_RIGHT) )
		return RIGHT_ARROW;

	if( !GetPIN(SW_ST) )
			return START;

	return NO_KEY;
}



