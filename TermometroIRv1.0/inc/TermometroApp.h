#ifndef TERMOMETROAPP_H_
#define TERMOMETROAPP_H_

#include "../inc/DR_Init.h"
#include "../inc/Funciones_Primitivas.h"
#include "../inc/Firmware.h"
#include "../inc/DR_switch.h"

enum STATESMDE{ESPERANDO, MIDIENDO_TEMP, DISPLAY_TEMP};

#define CANT_MEDICIONES 10

void InitTermometroMDE(void);
void TermometroMDE(void);
uint8_t MedicionTemp(void);
#endif /* TERMOMETROAPP_H_ */
