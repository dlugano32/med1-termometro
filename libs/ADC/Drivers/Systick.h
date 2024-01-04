/*
 * Systick.h
 *
 *  Created on: 9 sep. 2021
 *      Author: d_lugano
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "LPC845.h"

#define CANT_TIMERS 16

extern uint8_t flagsT[CANT_TIMERS];
extern uint32_t timers[CANT_TIMERS];

void AnalizarTimers(void);
void InitSystick(void);

#endif /* SYSTICK_H_ */
