/*
 * matriz.c
 *
 *  Created on: 24 sep. 2021
 *      Author: USUARIO
 */
#include "PR_Matriz.h"

//uint8_t fila=1;
uint8_t cifras[] = {0, 0, 0, 0};
uint8_t rows[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
uint8_t startFlag=0;

/*Arrays para escribir palabras*/
uint8_t GAME[] 	= { 6,0,12,4 };
uint8_t OVER[] 	= { 14,21,4,17 };
uint8_t HOLA[] 	= { 7,14,11,0 };
uint8_t YA[]	= { 26,24,0,26 };
//uint8_t GABI[] = { 6,0,1,8 };
uint8_t CLEAR[] = { 26,26,26,26 };//limpia la pantalla


/*Es la función que está dentro de la rutina del systick y que se encarga de imprimir las n-simas columnas de cada matriz*/
/*
 *INTENTO 1
void show(void)
{
	uint8_t i=0;

	LOAD_Down();
	for (i=0; i<4; i++)
	{
		sendAddress(fila);//las adress coinciden en este caso con el lúmero de columna en cuestión
		sendData(rows[ (((fila-1)*4)+i) ]);//imprimo la columna n-sima de cada matriz
	}
	LOAD_Up();

	fila++;
	if(fila>8)
	{
		fila=1;//cuando ya imprimo las 8 columnas, vuelvo a la primera
	}
}
*/

/*
 * INTENTO 2
void show(void)
{
    uint8_t i;
    uint8_t fila;

    for (fila=1;fila<9;fila++)
    {
        LOAD_Down();
        for (i=0; i<4; i++)
        {
            sendAddress(fila);//las adress coinciden en este caso con el lúmero de columna en cuestión
            sendData(rows[ (((fila-1)*4)+i) ]);//imprimo la columna n-sima de cada matriz
        }
        LOAD_Up();
    }
}
*/

void show(void)
{
    static uint8_t fila=1; //registro al cual se envía la data
    static uint8_t indice=0; //posición del array arrows que se está enviando

    if ( (indice%4) == 0 )
    {
        LOAD_Down(); //inicio el envío de datos de una hilera completa
    }

    sendAddress(fila);
    sendData( rows[indice] );
    indice++;
    if (indice > 31)
    {
        indice = 0;
    }

    if ( (indice%4) == 0 ) //cierro el envío de datos para esa hilera completa
    {
        LOAD_Up();
        fila++;
        if (fila > 8)
        {
            fila = 1;
        }
    }
}

void separarCifras(uint32_t aux)//utiiza un array global
{
	int8_t i;// no lo uso como unsigned xq necesito que llegue a -1 para cortar el for!!!!!!

	if (aux > 9999)//desborde
	{
		cifras[0]=0;
		cifras[1]=0;
		cifras[2]=0;
		cifras[3]=0;
	}
	else
	{
		for (i=3;i>=0;i--)// hace de 3 a 0
		{
			cifras[i] = aux%10;//tomo su última cifra
			aux/=10;//elimino su ultima cifra
		}
	}
}

/*Carga el valor de score en el array de cifras y luego, dependiendo de cada número, carga los datos correspondientes en el array de columnas*/
void print(uint32_t valor)
{
	uint8_t i, j;//xq tengo que cargar el numero de cada matriz
	separarCifras((uint32_t)valor);
	//cifras[0]---> unidad de mil
	//cifras[3]---> unidad

	for (i=0; i<4; i++)
	{
		switch (cifras[i])
		{
			case 0:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[0][j];
				}
				break;
			case 1:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[1][j];
				}
				break;
			case 2:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[2][j];
				}
				break;
			case 3:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[3][j];
				}
				break;
			case 4:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[4][j];
				}
				break;
			case 5:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[5][j];
				}
				break;
			case 6:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[6][j];
				}
				break;
			case 7:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[7][j];
				}
				break;
			case 8:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[8][j];
				}
				break;
			case 9:
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[9][j];
				}
				break;
			default://en default lo pongo en 0 por las dudas
				for(j=0; j<8; j++)//xq tengo que cargar 8 datos
				{
					rows [i+(4*j)] = numbers2[0][j];
				}
				break;
		}
	}

}

void gameOver1 (void)
{
	if (counter2 == 0)
	{
		write(GAME);
	}
	if (counter2 == 2)
	{
		write(OVER);
	}
	if (counter2 == 4)
	{
		print(points);
	}
	if (counter2 == 6)
	{
		counter2=0;
	}
}




void gameOver2 (uint8_t cant, uint8_t time)
{
	uint8_t i;
	for (i=0; i<cant; i++)
	{
		write (GAME);
		TimerStart(0, time, handlerT0, SEG);
		while (1)
		{
			if (flagT0)
			{
				flagT0=0;
				break;
			}
			TimerEvent();
		}
		write (OVER);
		TimerStart(0, time, handlerT0, SEG);
		while (1)
		{
			if (flagT0)
			{
				flagT0=0;
				break;
			}
			TimerEvent();
		}
		print(points);
		TimerStart(0, time, handlerT0, SEG);
		while (1)
		{
			if (flagT0)
			{
				flagT0=0;
				break;
			}
			TimerEvent();
		}
	}
	//print(0);
}

void stop(void)
{
	write (CLEAR);//limpio la pantalla
	TimerStart(3, 1, handlerT3, SEG);
	while (1)//espero un tiempo prudente hasta que se limpie por completo
	{
		if (flagT3)
		{
			flagT3=0;
			break;
		}
		TimerEvent();
	}
	startFlag=0;//deja de imprimir

}

void write (uint8_t* pointer)//para texto
{
	uint8_t i, j;

	for (i=0;i<4;i++)
	{
		for(j=0; j<8; j++)//xq tengo que cargar 8 datos
		{
			rows [i+(4*j)] = letters2[ pointer[i] ][j];
		}
	}


}

void start(void)
{
	 startFlag=1;
}







