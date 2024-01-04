/*
 * matriz.h
 *
 *  Created on: 24 sep. 2021
 *      Author: USUARIO
 */

#ifndef PR_MATRIZ_H_
#define PR_MATRIZ_H_

#include "../Drivers/DR_Matriz.h"
#include "Timer.h"
#include "../Aplicacion/JustDanceMDE.h"

void show(void);
void print(uint32_t);//para números
void start(void);
void stop(void);
void separarCifras(uint32_t);//utiiza un array global
void gameOver1 (void);
void gameOver2 (uint8_t cant, uint8_t time);
void write (uint8_t* pointer);//para texto
/*HACER EN ALGUN MOMENTO*/
void blink(uint8_t frec);//frecuencia de parpadeo

//extern uint8_t fila;
extern uint8_t cifras[4];
extern uint8_t rows[32];
extern uint8_t startFlag;
extern uint8_t GAME[4];
extern uint8_t OVER[4];
extern uint8_t HOLA[4];
extern uint8_t YA[4];
//extern uint8_t GABI[4];
extern uint8_t CLEAR[4];

/* 5467
 * cifras[0]=5
 * cifras[1]=4
 * cifras[2]=6
 * cifras[3]=7
 * */

/* "GAME"
 * GAME[0] = G
 * GAME[1] = A
 * GAME[2] = M
 * GAME[3] = E
 *
 * */

#endif /* PR_MATRIZ_H_ */
