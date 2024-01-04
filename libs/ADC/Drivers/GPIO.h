#ifndef GPIO_H_
#define GPIO_H_

#include "LPC845.h"

void SetDIR (uint32_t Puerto, uint32_t Pin, uint32_t Direccion);	//Setea la dirección del pin especificado
void SetPIN (uint32_t Puerto, uint32_t Pin, uint32_t Estado);	//Setea el Estado (0 o 1) indicado en el pin especificado
uint32_t GetPIN (uint32_t Puerto, uint32_t Pin); //Devuelve el valor del pin especificado
void SetPINMODE_IN (uint32_t Pin_index, uint32_t Modo); 	//Pull-Down o Pull-Up
void SetPINMODE_OUT (uint32_t Pin_index, uint32_t Modo);	//Drain Mode


#endif /* GPIO_H_ */
