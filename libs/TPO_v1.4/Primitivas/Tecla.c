/*
 * Tecla.c
 *
 *  Created on: 26 ago. 2021
 *      Author: d_lugano
 */

#include "Tecla.h"


uint32_t getKey(void)
{
	uint8_t aux=Tecla;
	Tecla=NO_KEY;
	return aux;	//Solo devuelvo que hubo un flanco descendente
}
