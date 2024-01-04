/*
 * ESP8266_conf.h
 *
 *  Created on: 17 nov. 2021
 *      Author: d_lugano
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "LPC845.h"
#include "Tecla.h"
#include "Timer.h"
#include "Leds.h"
#include "PR_UART.h"

#define CANT_COMANDOS 4

#define TRANSMISION 0
#define	CHECKING 1
extern uint8_t stage;

void InitESP8266_conf(void);
uint8_t Esp8266_conf(void);

#endif /* ESP8266_H_ */
