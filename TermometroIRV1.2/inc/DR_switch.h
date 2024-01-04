/*
 * DR_switch.h
 *
 *  Created on: May 30, 2023
 *      Author: dlugano
 */

#ifndef DR_SWITCH_H_
#define DR_SWITCH_H_

#include "../inc/GPIO.h"
#include "../inc/Firmware.h"

extern uint8_t flag_boton;

#define DEBOUNCE_COUNT 50
#define NO_KEY 255

void InitTeclado(void);
void DriverTecladoSW(void);

#endif /* DR_SWITCH_H_ */
