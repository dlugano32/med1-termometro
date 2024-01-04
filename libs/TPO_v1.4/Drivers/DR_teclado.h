/*
 * DR_teclado.h
 *
 *  Created on: 16 sep. 2021
 *      Author: d_lugano
 */

#ifndef DR_TECLADO_H_
#define DR_TECLADO_H_

#include "GPIO.h"
#include "LPC845.h"

extern uint8_t Tecla;

#define DEBOUNCE_COUNT 50

#define PUSH 0
#define NOT_PUSH 1

#define SW_RIGHT 	0,26
#define SW_DOWN 	0,27
#define SW_LEFT 	0,28
#define SW_UP 		0,29

#define SW_ST 		0,9
#define SW_SEL 		0,8

#define RIGHT_ARROW 1
#define DOWN_ARROW	2
#define LEFT_ARROW	3
#define UP_ARROW	4

#define SELECT 		5
#define START		6

#define NO_KEY 255

void InitTeclado(void);
void DriverTecladoSW(void);
uint8_t DriverTecladoHW(void);

#endif /* DR_TECLADO_H_ */
