/*
 * Timer.h
 *
 *  Created on: 9 sep. 2021
 *      Author: d_lugano
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "../Drivers/LPC845.h"
#include "../Drivers/Systick.h"
#include "../Drivers/Systick.h"
#include "../Primitivas/PR_Matriz.h"
#include "PR_7seg.h"

#define SEG 1000
#define MIN 60000
#define DEC 100
#define MILI 1

//void ( * HandlersTimer [CANT_TIMERS]) (void);

void TimerStart(uint8_t ntimer, uint32_t time, void (*handler)(void), uint32_t base);
void TimerStop(uint8_t ntimer);
void TimerEvent(void);


extern uint8_t flagT0;
extern uint8_t flagT3;
extern uint8_t flagT5;
extern uint32_t counter;
extern uint32_t counter2;
extern uint32_t counter4;

void handlerT0(void);
void handlerT1(void);
void handlerT2(void);
void handlerT3(void);
void handlerT4(void);
void handlerT5(void);

#endif /* TIMER_H_ */
