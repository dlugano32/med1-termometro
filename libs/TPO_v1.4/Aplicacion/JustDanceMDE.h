/*
 * JustDanceMDE.h
 *
 *  Created on: 7 oct. 2021
 *      Author: d_lugano
 */

#ifndef JUSTDANCEMDE_H_
#define JUSTDANCEMDE_H_

#include <ESP8266.h>
#include "../Drivers/LPC845.h"
#include "../Primitivas/Leds.h"
#include "../Primitivas/Timer.h"
#include "../Primitivas/Tecla.h"
#include "../Primitivas/PR_Matriz.h"
//#include "../Primitivas/PR_ESP8266.h"

#define STAND_BY 5
#define CONF_ESP 4
#define MENU_PRINCIPAL 0
#define	CUENTA_ATRAS 1
#define ESPERANDO_TECLA 2
#define GAME_OVER 3

#define CANT_PASOS0 32
#define CANT_PASOS1 96

#define FACIL 3000
#define MEDIO 2000
#define DIFICIL 1000

typedef struct
{
	uint32_t timestap;
	uint8_t tecla;
}Paso;


typedef struct
{
	int32_t largo;
	int32_t cant;
	Paso *paso;

}Canciones;

extern Canciones cancionero[2];
extern Paso pasos0[CANT_PASOS0];
extern Paso pasos1[CANT_PASOS1];
extern int32_t points;
extern uint8_t n_nivel, n_cancion, flagGameOver, flagEscape, flagDatos;

void JustDanceMDE(void);
void clearMDE(void);
void InitJustDanceMDE(void);

#endif /* JUSTDANCEMDE_H_ */
