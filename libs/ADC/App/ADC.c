#include "DR_Init.h"
#include "PR_ADC.h"

int main(void)
{
	uint32_t aux=0;

	InitHw();

	LED_OFF(ROJO);
	LED_OFF(AZUL);
	LED_OFF(VERDE);

    while(1)
    {
    	aux=LeerADC();

    	if(aux<100)
    	{
    		LED_OFF(ROJO);
			LED_OFF(AZUL);
			LED_OFF(VERDE);
    	}
    	else if( aux > 100 && aux < 1360)
    	{
    		LED_ON(ROJO);
    		LED_OFF(AZUL);
    		LED_OFF(VERDE);
    	}
    	else if(aux >1360 && aux <2720)
    	{
    		LED_OFF(ROJO);
    		LED_ON(AZUL);
    		LED_OFF(VERDE);
    	}
    	else if(aux > 2720)
    	{
    		LED_OFF(ROJO);
    		LED_OFF(AZUL);
    		LED_ON(VERDE);
    	}

    }
    return 0 ;
}

