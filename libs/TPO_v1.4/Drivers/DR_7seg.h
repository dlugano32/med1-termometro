/*
 * DR_7seg.h
 *
 *  Created on: 5 oct. 2021
 *      Author: d_lugano
 */

#ifndef DR_7SEG_H_
#define DR_7SEG_H_

#include "LPC845.h"
#include "GPIO.h"

#define N_DIGITOS 2

#define segG 0,16
#define segF 0,17
#define segA 0,18
#define segB 0,19
#define segC 0,20
#define segD 0,21
#define segE 0,22

#define DIG0 0,12
#define DIG1 0,1

#define DIGITO_0 0
#define DIGITO_1 1

#define DIG_OFF 1
#define DIG_ON 0

extern uint8_t Digito_Display[N_DIGITOS];

void Init7seg(void);
void BarridoDisplay(void);

#endif /* DR_7SEG_H_ */
