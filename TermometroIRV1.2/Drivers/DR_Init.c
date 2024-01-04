/*
 * DR_Init.c
 *
 *  Created on: May 30, 2023
 *      Author: dlugano
 */

#include "../inc/DR_Init.h"

void HW_Init(void)
{
	Inicializacion_I2C0();
	InitGPIO();
	InitSystick();
	InitADC();
	Display_Init();
	InitTeclado();
}

void InitGPIO(void)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << SYSCON_SYSAHBCLKCTRL0_GPIO0_SHIFT);
	SYSCON->SYSAHBCLKCTRL0 |= (1 << SYSCON_SYSAHBCLKCTRL0_GPIO1_SHIFT);
}

void InitSystick(void)
{
	SYSTICK->CSR=7;			//Pongo en 1 los ultimos 3 bits del registro
	SYSTICK->RVR=12000-1;	//Configuro el systick cada 1ms sabiendo que el FRO es 12MHZ, le pongo -1 porque el micro tarda un tick mas en hacer el reload
	SYSTICK->CVR=SYSTICK->RVR;	//La primer recarga la tiene que hacer el usuario
}
