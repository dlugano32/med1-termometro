/*
 * DR_7seg.c
 *
 *  Created on: 5 oct. 2021
 *      Author: d_lugano
 */

#include "DR_7seg.h"

uint8_t Digito_Display[N_DIGITOS]={0,0};

void Init7seg(void)
{
	PINENABLE0|=(1<<1);
	PINENABLE0|=(1<<10);

	SetDIR(segA, SALIDA);
	SetDIR(segB, SALIDA);
	SetDIR(segC, SALIDA);
	SetDIR(segD, SALIDA);
	SetDIR(segE, SALIDA);
	SetDIR(segF, SALIDA);
	SetDIR(segG, SALIDA);

	SetDIR(DIG0, SALIDA);
	SetDIR(DIG1, SALIDA);

	SetPINMODE_OUT(IOCON_INDEX_PIO0_16, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_17, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_18, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_19, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_20, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_21, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_22, 0);

	SetPINMODE_OUT(IOCON_INDEX_PIO0_0, 0);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_12, 0);
}

void BarridoDisplay(void)
{
	const uint8_t Tabla_Digitos_BCD_7seg[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

	static uint8_t Indice_Display=0;
	uint8_t auxiliar=0;

	//Apago los displays
	SetPIN(DIG0, 1);
	SetPIN(DIG1, 1);

/*
	SetPIN(DIG0, 0);
	SetPIN(DIG1, 0);
*/

	auxiliar=Tabla_Digitos_BCD_7seg[ Digito_Display[Indice_Display] ];
	//auxiliar=~auxiliar;

	SetPIN( segA, ( (auxiliar>>0) & (uint8_t) 0x01) );
	SetPIN( segB, ( (auxiliar>>1) & (uint8_t) 0x01) );
	SetPIN( segC, ( (auxiliar>>2) & (uint8_t) 0x01) );
	SetPIN( segD, ( (auxiliar>>3) & (uint8_t) 0x01) );
	SetPIN( segE, ( (auxiliar>>4) & (uint8_t) 0x01) );
	SetPIN( segF, ( (auxiliar>>5) & (uint8_t) 0x01) );
	SetPIN( segG, ( (auxiliar>>6) & (uint8_t) 0x01) );

	switch( Indice_Display )
	{
		case 0:
			SetPIN(DIG0, 0);
			break;

		case 1:
			SetPIN(DIG1, 0);
			break;
	}

	/*switch( Indice_Display )
	{
		case 0:
			SetPIN(DIG0, 1);
			break;

		case 1:
			SetPIN(DIG1, 1);
			break;
	}*/

	Indice_Display ++;
	Indice_Display %= 2;
}

