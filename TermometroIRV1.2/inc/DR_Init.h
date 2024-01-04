/*
 * DR_Init.h
 *
 *  Created on: 30 May 2023
 *      Author: dlugano
 */

#ifndef DR_INIT_H_
#define DR_INIT_H_

#include "../inc/Header_Fabricante.h"
#include "PR_MLX90614.h"
#include "DR_switch.h"
#include "PR_display.h"
#include "../inc/DR_ADC.h"

void HW_Init(void);
void InitGPIO(void);
void InitSystick(void);

#endif /* DR_INIT_H_ */
