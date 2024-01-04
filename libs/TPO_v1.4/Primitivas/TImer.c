/*
 * TImer.c
 *
 *  Created on: 9 sep. 2021
 *      Author: d_lugano
 */

#include "Timer.h"


uint8_t flagT0=0;
uint8_t flagT3=0;
uint8_t flagT5=0;
uint32_t counter=0;
uint32_t counter2=0;
uint32_t counter4=0;

void ( * HandlersTimer [CANT_TIMERS]) (void);

void TimerStart(uint8_t ntimer, uint32_t time, void (*handler)(void), uint32_t base)
{
	timers[ntimer]=time*base;
	flagsT[ntimer]=0;
	HandlersTimer[ntimer]=handler;
}

void TimerStop(uint8_t ntimer)
{
	timers[ntimer]=0;
	flagsT[ntimer]=0;
}

void TimerEvent(void)
{
	uint8_t i=0;

	for(i=0; i<CANT_TIMERS; i++)
	{
		if(flagsT[i]==1)
		{
			flagsT[i]=0;
			HandlersTimer[i]();
		}
	}
}

void handlerT0(void)
{
	static uint8_t aux=1;

	print(3-aux); //3,2,1.....

	if (aux==3)
	{
		flagT0=1;
		aux=1;
	}
	else
	{
		TimerStart(0, 1, handlerT0, SEG);
		aux++;
	}

}

void handlerT1(void)
{
	counter++;
	TimerStart(1, 1, handlerT1, MILI);
}

void handlerT2(void)
{
	counter2++;
	TimerStart(2, 1, handlerT2, SEG);
}

void handlerT3(void)
{
	flagT3=1;
}

void handlerT4(void)
{
	counter4++;
	Display(counter4);
	TimerStart(4, 1, handlerT4, SEG);

}

void handlerT5(void)
{
	flagT5=1;
}

