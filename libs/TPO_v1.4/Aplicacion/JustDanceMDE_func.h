/*
 * MDE_funciones.h
 *
 *  Created on: 11 oct. 2021
 *      Author: d_lugano
 */

#ifndef JUSTDANCEMDE_FUNC_H_
#define JUSTDANCEMDE_FUNC_H_

#include "../Aplicacion/JustDanceMDE_func.h"
#include "../Drivers/LPC845.h"
#include "../Aplicacion/JustDanceMDE.h"
#include "../Librerias/myString.h"

void Puntaje(uint32_t counter, uint32_t timestap , uint32_t dificultad );
void Puntaje_restar(uint8_t npaso, uint8_t cant);
void InitCancion0( Paso* steps);
void InitCancion1( Paso* steps);
void InitMusica(void);

void EnviarStart(void);
void EnviarSelect(void);
void EnviarPuntaje(int32_t puntaje);
void EnviarDatos(uint8_t key, uint32_t timestap);

#endif /* JUSTDANCEMDE_FUNC_H_ */
