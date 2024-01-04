#include "../inc/TermometroApp.h"

/*Variables globales a TermometroApp.c*/

uint8_t flag_boton, estado, ready;
double VM_temp;	//Valor medio de la temperatura de N mediciones
char VM_temp_string[10];

/*Maquina de estados*/

void TermometroMDE( void )
{

    switch(estado)
    {
        case ESPERANDO:
            if(flag_boton)
            {
                flag_boton=0;
                estado=MIDIENDO_TEMP;
            }

        break;

        case MIDIENDO_TEMP:
            ready=MedicionTemp();

            if(ready)
            {
                ready=0;
                Display_Clear();
                Display_PositionXY(0, 0);
                Display_SendString("-----------------");
                Display_SendTemp(ftoa(VM_temp, VM_temp_string, 3));
                Display_PositionXY(6, 3);
                Display_SendString("Pulse el boton");
                Display_PositionXY(6, 4);
                Display_SendString("para continuar");
                Display_PositionXY(0, 5);
                Display_SendString("-----------------");
                estado=DISPLAY_TEMP;
            }

        break;

        case DISPLAY_TEMP:
            if(flag_boton)
            {
                flag_boton=0;
                Display_Clear();
                Display_PositionXY(0, 0);
                Display_SendString("-----------------");
                Display_PositionXY(6, 2);
                Display_SendString("Pulse el boton");
                Display_PositionXY(6, 3);
                Display_SendString("para medir");
                Display_PositionXY(0, 5);
                Display_SendString("-----------------");
                estado=ESPERANDO;
            }
        break;

        default: estado = ESPERANDO;
    }
}

void InitTermometroMDE(void)
{
	estado=ESPERANDO;
	flag_boton=0 ,ready=0;
	VM_temp=0;
    Display_Clear();
    Display_PositionXY(0, 0);
    Display_SendString("-----------------");
    Display_PositionXY(6, 2);
    Display_SendString("Pulse el boton");
    Display_PositionXY(6, 3);
    Display_SendString("para medir");
    Display_PositionXY(0, 5);
    Display_SendString("-----------------");
}

uint8_t MedicionTemp(void)
{
	static double dato[CANT_MEDICIONES];
	static uint8_t i=0, first=1;
	uint8_t ret=0, j=0;
	double acum=0, T1=0, Vdd;

	if(first)
	{
		Leer_I2C0(0x5A);
		first=0;
	}

	if(flag_datoLeido)	//Pregunto si hay un dato disponible
	{
		Vdd=LeerVDD();	//Leo el valor de la fuente de alimentación mediante el ADC

		T1=( (double)rawTemp * 0.02 ) - 273.15;	// Linearizo y paso a celsius la temperatura. -> rawTemp variable global del handler del sensor
		dato[i++] = T1- ( (Vdd - 3) * 0.6) ;	//Compenso el error de la temperatura medida por la fuente de alimentación

		flag_datoLeido=0;

		if(i!=CANT_MEDICIONES)
			Leer_I2C0(0x5A);
	}

	if(i==CANT_MEDICIONES)
	{
		i=0;
		first=1;

		for(j=0, acum=0; j<CANT_MEDICIONES; j++)
		{
			acum+=dato[j];
		}

		VM_temp=acum/CANT_MEDICIONES;

		ret=1;
	}

	return ret;
}


