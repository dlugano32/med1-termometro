/*
 * DR_UART.c
 *
 *  Created on: 26 oct. 2021
 *      Author: d_lugano
 */

#include "DR_UART.h"
#include "JustDanceMDE_func.h"

//Variables
uint32_t in_tx1=0;
uint32_t out_tx1=0;
uint32_t in_rx1=0;
uint32_t out_rx1=0;

uint8_t buf_tx1[TAM_TX1];
uint8_t buf_rx1[TAM_RX1];


uint8_t datoRx;
uint8_t flagRx=0;
uint8_t flagTx=0;

void InitUART1(void)
{
	//Habilito el clock de la UART1
	SYSCON->SYSAHBCLKCTRL0|= (1<<SYSCON_SYSAHBCLKCTRL0_UART1_SHIFT);

	//Reseteo la uart
	SYSCON->PRESETCTRL0 &= ~(1<<15);
	SYSCON->PRESETCTRL0 |= (1<<15);

	//Selecciono pines TX y RX
	SYSCON->SYSAHBCLKCTRL0|= (1<<7);	//Habilito el CLK de la SWM
	PINASSIGN1 &= ~(0x00FFFFF00); 		//Pongo en cero todos los bits
	PINASSIGN1 = (6 << 8) | (23 << 16);	//TX=PO.6 y RX=P0.23

	//Configuracion de la comunicacion
	USART1->CFG=
		(0 << 0)	//0=DISABLE 	1=ENABLE
	|	(1 << 2)	//Data length 	0=7bits 1=8bits 2=9bits
	|	(0 << 4)	//Paridad 		0=NOPARITY 2=EVEN(PAR) 3=ODD(IMPAR)
	|	(0 << 6)	//Stop length	0=1bitStop 1=2bitStop
	|	(0 << 9)	//CTSEN			0=NOFLOWCONTROL 1=FLOWCONTROL
	|	(0 << 11)	//SYNCEN		0=ASINCRONICA 1=SINCRONICA
	;

	//Configuracion de la interrupcion
	USART1->INTENSET = (1 << 0);	//RX

	//Configuracion del baudrate
	UART1CLKSEL=0;	//CLK del periferico = FRO= 30MHz
	USART1->BRG = (FREQ_PRINCIPAL / (BAUDRATE1* 16));

	//Habilito la interrupcion USART0 en el NVIC
	ISER0 |=(1<<ISE_UART1_SHIFT);

	USART1->CFG|=1;	//Habilito la UART
}

void UART1_IRQHandler(void)
{
	uint32_t stat = USART1->STAT;
	int32_t aux;
	static uint8_t datoRx;

    // CASO RECEPCION
	if(stat & (1 << 0))
	{
		datoRx=USART1->RXDAT;
		//PushRx1(datoRx);

		if(datoRx=='\n')
			flagRx=1;

		//RxDatosMDE(datoRx);
		//Escape(datoRx);

	}

	//CASO TRANSMISION
	if(stat & (1 << 2))
	{
		aux=PopTx1();

		if(aux!=-1)
		{
			USART1->TXDAT=aux;
		}
		else
		{
			USART1->INTENCLR=1<<2;	//Desactivo las interrupciones por Tx para avisar cuando se termino de mandar
			flagTx=1;
		}
	}

}

void RxDatosMDE(uint8_t dato)
{
	static uint8_t estado=INICIO_TRAMA;
	static uint8_t cont=0, buffer[2];

	switch(estado)
	{
	case INICIO_TRAMA:
		if(dato=='#')
		{
			estado=DATO;
		}
		break;

	case DATO:
		buffer[cont]=dato;
		cont++;

		if(cont==2)
			estado=FIN_TRAMA;

		break;

	case FIN_TRAMA:
		if(dato=='@')
		{
			n_nivel=buffer[0]-1-(48);	//1=DIFICIL 2=MEDIO 3=FACIL
			n_cancion=buffer[1]-(48);
			flagDatos=1;
			buffer[0]='\0';
			buffer[1]='\0';
			cont=0;
			estado=INICIO_TRAMA;
		}
		break;
	}
}

void Escape(uint8_t dato)
{
	static uint8_t estado=INICIO_TRAMA;

	switch(estado)
	{
	case INICIO_TRAMA:
		if(dato=='@')
		{
			estado=DATO;
		}
		break;

	case DATO:
		if(dato=='C')
		{
			estado=FIN_TRAMA;
		}
		else
		{
			estado=INICIO_TRAMA;
		}
		break;

	case FIN_TRAMA:
		if(dato=='#')
		{
			flagEscape=1;
			estado=INICIO_TRAMA;
		}
		break;
	}
}

void PushTx1 ( uint8_t dato)
{
	buf_tx1[in_tx1]=dato;
	in_tx1++;
	in_tx1%=TAM_TX1;

	USART1->INTENSET|= 1<<2;	//Activo las interrupciones para que me avise cuando haya terminado de mandar el mensaje para poder transmitir otra vez
}

int16_t PopTx1( void )
{
	int16_t aux=-1;

	if(in_tx1!=out_tx1)
	{
		aux=buf_tx1[out_tx1];
		out_tx1++;
		out_tx1%=TAM_TX1;
	}

	return aux;
}

void PushRx1( uint8_t dato )
{
	buf_rx1[in_rx1]=dato;
	in_rx1++;
	in_rx1%=TAM_RX1;
}

int16_t PopRx1( void )
{
	int16_t aux=-1;

	if(in_rx1!=out_rx1)
	{
		aux=buf_rx1[out_rx1];
		out_rx1++;
		out_rx1%=TAM_RX1;
	}

	return aux;
}
