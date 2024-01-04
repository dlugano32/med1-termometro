#include <cr_section_macros.h>
#include "../inc/TermometroApp.h"

int main(void)
{
	HW_Init();
    InitTermometroMDE();

    while (1)
    {
    	TermometroMDE();
    }

    return 0 ;
}
