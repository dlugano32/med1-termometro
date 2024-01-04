/*
 * PR_UART.c
 *
 *  Created on: 28 oct. 2021
 *      Author: d_lugano
 */
#include "PR_UART.h"

int16_t RxSerie1(void)
{
	return PopRx1();
}

void LimpiarBufferRx1(void)
{
	int32_t i=0;

	for(i=0; i<TAM_RX1; i++)
		buf_rx1[i]='\0';

	in_rx1=0;
	out_rx1=0;
}

void TxSerie1(uint8_t* buffer)
{
	uint32_t i=0;

	for(i=0; *(buffer+i)!='\0'; i++)
		PushTx1(buffer[i]);

	flagRx=0;
	flagTx=0;
}

