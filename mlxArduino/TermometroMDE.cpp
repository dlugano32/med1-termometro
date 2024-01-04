#include "TermometroMDE.h"

volatile uint8_t flag_boton=0;

my_MLX90614 mlx = my_MLX90614();

void TermometroMDE( void )
{
    static uint8_t  estado=ESPERANDO;
    static bool ready=0, first_time=0;
    static double VM_temp;

    switch(estado)
    {
        case ESPERANDO:
            if(flag_boton)
            {
                flag_boton=0;
                estado=MIDIENDO_TEMP;
            }
            else if(first_time)
            {
              first_time=0;
              Serial.println("Esperando...");
            }
        break;

        case MIDIENDO_TEMP:
            Serial.println("Midiendo...");
            ready=MedicionTemp(&VM_temp);

            if(ready)
            {
                ready=0;
                displayTemp(VM_temp);
                Serial.println("Cuando termine de leer la medicion aprete el boton");
                estado=DISPLAY_TEMP;
            }

        break;

        case DISPLAY_TEMP:
            if(flag_boton)
            {
                flag_boton=0;
                first_time=1;
                //Clear display
                estado=ESPERANDO;
            }
        break;

        default: estado = ESPERANDO;
    }
}

void boton_handler (void)
{
  delay(400); //Espero

  if(digitalRead(2))  // Me fijo si sigue en estado alto
  {
    flag_boton=1; // Recien ahi activo el flag
  }
  else
  {
    flag_boton=0;
  }
}

bool MedicionTemp(double *temp)
{
    uint8_t i;

    for(i=0, (*temp)=0; i<CANT_MEDICIONES; i++)
    {
        (*temp)+=mlx.readObjectTemp();
    }

    (*temp)/=CANT_MEDICIONES;

    return true;
}

void displayTemp(double temp)
{
    Serial.print("Object = "); 
    Serial.print(temp); 
    Serial.println("*C");
}