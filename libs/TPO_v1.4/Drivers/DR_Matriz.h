/*
 * DR_Matriz.h
 *
 *  Created on: 24 sep. 2021
 *      Author: USUARIO
 */

#ifndef DR_MATRIZ_H_
#define DR_MATRIZ_H_

#include "LPC845.h"//para usar los tipos de datos
#include "numberIndex.h"//matriz para formar los numeros en pantalla
#include "GPIO.h"

#define DIN 	0, 13
#define LOAD 	0, 14
#define CLK 	0, 15

void matrixInit (void);
void CLK_Up (void);
void CLK_Down (void);
void LOAD_Up (void);
void LOAD_Down (void);
void sendAddress (uint8_t adr);
void sendData (uint8_t data);
void pinsConfig (void);
void cleanAll (void);
void showAll (void);

void test1 (void);
void test2 (void);




#endif /* DR_MATRIZ_H_ */
