/*
 * DR_Systick.c
 *
 *  Created on: 30 May 2023
 *      Author: dlugano
 */

#include "../inc/DR_Systick.h"
uint32_t delayMS=0;
uint8_t flagMS=0;

void SysTick_Handler(void)
{
	DriverTecladoSW();

	if(delayMS!=0)
	{
		delayMS--;

		if(!delayMS)
		{
			flagMS=1;
		}
	}
}

/*------------------- Timer --------------------------------*/

void MSdelay(unsigned int val)
{
	delayMS=val;
	while(!flagMS);
	flagMS=0;
}
