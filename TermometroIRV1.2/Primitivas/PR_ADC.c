/*
 * PR_ADC.c
 *
 *  Created on: 14 nov. 2021
 *      Author: d_lugano
 */

#include "../inc/PR_ADC.h"

double LeerVDD(void)
{
	double ret=0;

	ADC->INTEN=1;		//Habilito las interrupcioned del ADC SEQA

	while(flagADC!=1);	//Espero a que este listo el dato

	flagADC=0;	//Bajo el flag

	ret = ((resultadoADC*VREF)/NBITS ) * 2;	// El resultado del ADC se pasa a unidad de tension y se lo multiplica x2 por el atenuador que tiene en la entrada

	return ret;
}
