/*
 * Systick.h
 *
 *  Created on: 9 sep. 2021
 *      Author: d_lugano
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "LPC845.h"
#include "DR_teclado.h"
#include "DR_7seg.h"
#include "../Primitivas/PR_Matriz.h"

#define CANT_TIMERS 6

extern uint8_t flagsT[CANT_TIMERS];
extern uint32_t timers[CANT_TIMERS];

extern uint8_t flagTimer;
extern uint8_t tick;

void AnalizarTimers(void);
void InitSystick(void);

#endif /* SYSTICK_H_ */
