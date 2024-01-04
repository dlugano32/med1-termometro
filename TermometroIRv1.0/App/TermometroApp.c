#include "../inc/TermometroApp.h"

/*Variables globales a TermometroApp.c*/

uint8_t flag_boton, estado, ready;
double VM_temp;	//Valor medio de la temperatura de N mediciones

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
            //Serial.println("Midiendo...");
            ready=MedicionTemp();

            if(ready)
            {
                ready=0;
                //displayTemp(VM_temp);
                //Serial.println("Cuando termine de leer la medicion aprete el boton");
                estado=DISPLAY_TEMP;
            }

        break;

        case DISPLAY_TEMP:
            if(flag_boton)
            {
                flag_boton=0;
                //Serial.println("Esperando...");
                estado=ESPERANDO;
            }
        break;

        default: estado = ESPERANDO;
    }
}

void InitTermometroMDE(void)
{
	uint8_t estado=ESPERANDO;
	uint8_t flag_boton=0 ,ready=0;
	double VM_temp=0;
	//Serial.println("Esperando...");
}

uint8_t MedicionTemp(void)
{
	static double dato[CANT_MEDICIONES];
	static uint8_t i=0, first=1;
	uint8_t ret=0, j=0;
	double acum=0;

	if(first)
	{
		Leer_I2C0(0x5A);
		first=0;
	}

	if(flag_datoLeido)	//Pregunto si hay un dato disponible
	{
		dato[i++]=( (double)rawTemp * 0.02 ) - 273.15;	// Linearizo y paso a celsius la temperatura. -> rawTemp variable global del handler del sensor
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


