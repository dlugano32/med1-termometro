/*
 * Leds.h
 *
 *  Created on: 26 ago. 2021
 *      Author: d_lugano
 */

#ifndef LEDS_H_
#define LEDS_H_

#include "../Drivers/LPC845.h"
#include "../Drivers/GPIO.h"

#define PIN_LEDR	1,2
#define	PIN_LEDG	1,0
#define	PIN_LEDB	1,1

#define ROJO 2
#define VERDE 0
#define AZUL 1

#define L_ON 0
#define L_OFF 1

void LED_OFF( uint32_t Color);
void LED_ON( uint32_t Color);
void SwapEstadoLed(uint32_t Color);


#endif /* LEDS_H_ */

