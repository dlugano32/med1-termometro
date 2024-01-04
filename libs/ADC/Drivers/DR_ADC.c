/*
 * DR_ADC.c
 *
 *  Created on: 14 nov. 2021
 *      Author: d_lugano
 */

#include "DR_ADC.h"

uint32_t resultadoADC=0;

void InitADC(void)
{
	uint16_t DIV=0;

	SYSCON->PDRUNCFG &= ~(1<<4);			//Power ADC

	SYSCON->SYSAHBCLKCTRL0|= (1<<24);	//Activo el CLK del ADC
	SYSCON->ADCCLKSEL=0;				//Selecciono el CLK del ADC a 30MHz
	SYSCON->ADCCLKDIV=0;				//Sin divisiones

	SYSCON->SYSAHBCLKCTRL0|= (1<<7);	//Habilito la SWM
	PINENABLE0 &= ~(1<<15);				//Habilito el canal 1 del ADC en el PIO0_6

	/*CALIBRACION DEL ADC*/

	ADC->CTRL=60;			//Divido el CLK de 30MHz por 60 y me quedan 500KHz que es lo que necesito para calibrar;
	ADC->CTRL|= (1<<30);	//Arranco el modo auto calibracion

	while(ADC->CTRL & (1<<30));		//Espero a que termino la calibracion

	/*CONFIGURO EL ADC*/
	DIV=CLK/(25 * SAMPLE);	//El divisor para configurar el sample rate

	ADC->CTRL=	(DIV-1)			//CLKDIV
			|	(0 << 8)		//ASYNCMODE 0=Modo sincronico 	1=Modo asincronico
			|	(0 << 10)		//LPWRMODE 0=OFF	1=ON
			|	(0 << 30)		//CALMODE 0=OFF		1=ON
			;

	/* CONFIGURO LA SECUENCIA A */
	ADC->SEQA_CTRL=	(1 << 1)	// 	CHANNELS 	Habilito el canal 1 en la secuencia A
				|	(0 << 12)	//	TRIGGER		Deshbilito triggers
				//|	(0 << 19)	// SYNCBYPASS	Modo sincronico
				//|	(0 << 24)	// TSAMP		Frecuencia de muestro sin delay
				|	(1 << 27)	// BURST		Modo burst (habilita la conversion sucesiva de ADC a partir del ADC_CLK)
				|	(0 << 30)	// MODE
				|	(1 << 31)	// SEQA_ENA		Habilito la secuencia
				;

	ADC->SEQB_CTRL=0;	//Deshabilito la secuencia B
	ADC->TRM &= ~(1 << 5);	//VRANGE 2.7v to 3.6v

	/*Habilito la interrupcion de la secuencia A*/
	ADC->INTEN=1;		//Habilitacion en el periferico
	ISER0 |= (1 << 16);	//habilitacion en el NVIC

}

void ADC_SEQA_IRQHandler(void)
{
	static uint32_t buffer_muestras[CANT_MUESTRAS];
	static uint8_t cont=0;
	int aux=0, i=0;

	buffer_muestras[cont]= (ADC->SEQA_GDAT >> 4) & 0x0FFF;
	cont++;
	cont%=CANT_MUESTRAS;

	for(i=0; i<CANT_MUESTRAS; i++)	//Hago un promedio entre todos los datos del buffer
		aux+=buffer_muestras[i];

	resultadoADC = aux/CANT_MUESTRAS;
}
