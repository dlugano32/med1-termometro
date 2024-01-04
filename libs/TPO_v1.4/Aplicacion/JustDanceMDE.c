/*
 * JustDanceMDE.c
 *
 *  Created on: 7 oct. 2021
 *      Author: d_lugano
 */

#include "JustDanceMDE.h"
#include "JustDanceMDE_func.h"

//Variables del juego
const uint32_t dificultad[3]={DIFICIL, MEDIO, FACIL};
static uint32_t n_paso=0;
//Indices de dificultad y de cancion
uint8_t n_nivel=2, n_cancion=1;

void JustDanceMDE(void)
{
	//Variables
	static uint8_t estado=STAND_BY;
	static uint8_t key=NO_KEY;
	uint8_t aux=0;
	static Paso *cancion;

	key=getKey();

	switch(estado)
	{
		case STAND_BY:

			if(key==START)
			{
				estado=CONF_ESP;
			}

			break;

		case CONF_ESP:
			aux=Esp8266_conf();
			if( aux==1 )
			{
				LED_OFF(AZUL);
				LED_ON(VERDE);
				LimpiarBufferRx1();
				cancion=cancionero[n_cancion].paso;
				estado=MENU_PRINCIPAL;
			}
			break;

		case MENU_PRINCIPAL:
			if(key==START)
			{
				EnviarStart();
				print(3);
				TimerStart(0, 1, handlerT0, SEG);	//Timer cuenta atras
				estado=CUENTA_ATRAS;
			}

			if(key==SELECT)
			{
				EnviarSelect();
				InitJustDanceMDE();
				LED_OFF(VERDE);
				LED_ON(AZUL);
				estado=STAND_BY;
			}

			break;

		case CUENTA_ATRAS:

			if(flagT0==1)
			{
				flagT0=0;
				TimerStart(1, 1, handlerT1, MILI);		//Contador milisegundos
				TimerStart(4, 1, handlerT4, SEG);		//Contador segundos
				print(0);
				estado=ESPERANDO_TECLA;
			}
			break;

		case ESPERANDO_TECLA:

			if(n_paso<cancionero[n_cancion].cant)	//Mientras no haya contado todos los pasos
			{
				if( ((cancion[n_paso].timestap-dificultad[n_nivel]*0.3) <= counter ) && ((cancion[n_paso].timestap + dificultad[n_nivel]*0.3) >= counter) ) 	//Tiempo en el que deberia haber una tecla apretada
				{
					//Estas dentro del tiempo correcto
					if(key==cancion[n_paso].tecla)
					{
						//Apretaste la tecla bien
						Puntaje( counter, cancion[n_paso].timestap, dificultad[n_nivel] );
						n_paso++;
					}
					else if(key!=NO_KEY && key!=START && key!=SELECT)
					{
						//Apretaste cualquier tecla
						Puntaje_restar(n_paso, cancionero[n_cancion].cant);
						n_paso++;
					}
				}
				else if( key!=NO_KEY && key!=START && key!=SELECT)
				{
					//Apretaste fuera de tiempo
					Puntaje_restar(n_paso, cancionero[n_cancion].cant);
					n_paso++;
				}

				if( ( cancion[n_paso].timestap+dificultad[n_nivel]*0.3 ) < counter )
				{
					//Te olvidaste de apretar
					Puntaje_restar(n_paso, cancionero[n_cancion].cant);
					n_paso++;
				}
			}

			print(points);

			if(key!=NO_KEY && key!=START && key!=SELECT)	//Envio datos a la PC
			{
				EnviarDatos(key, counter);
			}

			if(key==SELECT)
			{
				EnviarSelect();
				TimerStop(1);
				TimerStop(4);
				InitJustDanceMDE();
				LimpiarBufferRx1();
				LED_ON(AZUL);
				LED_OFF(VERDE);
				estado=STAND_BY;
			}

			if(counter>=cancionero[n_cancion].largo || flagGameOver==1) //game over
			{
				flagGameOver=0;
				EnviarPuntaje(points);
				TimerStop(1);
				TimerStop(4);
				TimerStart(2, 1, handlerT2, SEG);	//Contador GAMEOVER
				estado=GAME_OVER;
			}

			break;

		case GAME_OVER:
			gameOver1();
			if( key==START )
			{
				EnviarStart();
				TimerStop(2);
				write(CLEAR);
				clearMDE();
				estado=MENU_PRINCIPAL;
			}

			if(key==SELECT)
			{
				EnviarSelect();
				TimerStop(2);
				InitJustDanceMDE();
				LimpiarBufferRx1();
				LED_ON(AZUL);
				LED_OFF(VERDE);
				estado=STAND_BY;
			}
			break;

		default:
			estado=MENU_PRINCIPAL;

	}
}

void InitJustDanceMDE(void)
{
	InitESP8266_conf();
	clearMDE();
	TimerStart(5, 1000, handlerT5, MILI);
}

void clearMDE(void)
{
	flagT0=0;
	flagT3=0;
	counter=0;
	counter2=0;
	counter4=0;
	n_paso=0;
	n_nivel=2;
	n_cancion=1;
	points=0;
	flagGameOver=0;
	TimerStop(0);
	TimerStop(1);
	TimerStop(2);
	TimerStop(3);
	TimerStop(4);
	TimerStop(5);
	Display(0);
	write(CLEAR);
}
