/*
 * PR_UART.h
 *
 *  Created on: 28 oct. 2021
 *      Author: d_lugano
 */

#ifndef PR_UART_H_
#define PR_UART_H_

#include "LPC845.h"
#include "DR_UART.h"

int16_t RxSerie1 ( void );
void TxSerie1 ( uint8_t *);
int16_t RxBufferSerie1(void);
void LimpiarBufferRx1(void);

#endif /* PR_UART_H_ */
