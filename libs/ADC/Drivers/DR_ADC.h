/*
 * DR_ADC.h
 *
 *  Created on: 14 nov. 2021
 *      Author: d_lugano
 */

#ifndef DR_ADC_H_
#define DR_ADC_H_

#include "LPC845.h"

#define CLK 30000000
#define SAMPLE 10000

#define CANT_MUESTRAS 5

void InitADC(void);

extern uint32_t resultadoADC;

#endif /* DR_ADC_H_ */
