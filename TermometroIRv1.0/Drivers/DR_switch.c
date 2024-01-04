/*
 * DR_switch.c
 *
 *  Created on: May 30, 2023
 *      Author: dlugano
 */

#include "../inc/DR_switch.h"

void InitTeclado(void)
{
	//Entradas Botones Alfombra
	SetDIR(PUERTO0,26,ENTRADA);

    SetClock_IOCON(); //Habilito el Clock de IOCON

	//Activo pull-down
	SetPINMODE_IN(IOCON_INDEX_PIO0_26, 0x01);

    ClrClock_IOCON(); //Apago el Clock de IOCON para ahorrar energia

}

void DriverTecladoSW(void)
{
	static uint8_t cont=0;
	uint8_t key=0;	//Tecla no presionada

	key=GetPIN(PUERTO0, 26);	//Devuelve la tecla que esta siendo presionada

	if( key && cont < DEBOUNCE_COUNT)
	{
		cont++;	//Cuenta cuantos milisegundos esta presionada la tecla
		if(cont == DEBOUNCE_COUNT)
		{
			flag_boton=1;
			cont=0;
		}
	}
}
