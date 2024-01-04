/*
===============================================================================
 Name        : TPOJustDance.c
 Author      : dlugano
 Date		 : 21/9/2021
===============================================================================
*/

#include "../Drivers/DR_Init.h"
#include "../Aplicacion/JustDanceMDE.h"
#include "../Aplicacion/JustDanceMDE_func.h"

int main (void)
{
	InitHw();
	InitJustDanceMDE();
	InitMusica();

	LED_OFF(ROJO);
	LED_OFF(VERDE);
	LED_ON(AZUL);

	matrixInit();
	cleanAll();
	start();

	while(1)
	{
		JustDanceMDE();
		TimerEvent();
	}
	return 0;
}
