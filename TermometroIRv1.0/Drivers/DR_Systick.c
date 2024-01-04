/*
 * DR_Systick.c
 *
 *  Created on: 30 May 2023
 *      Author: dlugano
 */

#include "../inc/DR_Systick.h"

void SysTick_Handler(void)
{
	DriverTecladoSW();
}
