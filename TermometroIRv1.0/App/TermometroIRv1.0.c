#include <cr_section_macros.h>
#include "../inc/TermometroApp.h"

int main(void)
{
	HW_Init();
    InitTermometroMDE();
    //uint8_t ready=0;
    //Leer_I2C0(0x5A); /// La primera medición se descarta

    while (1)
    {
    	//ready=MedicionTemp();
    	TermometroMDE();
    }

    return 0 ;
}
