#ifndef DISPLAY_DRIVERS_H_
#define DISPLAY_DRIVERS_H_

/*------------------ Includes ----------------------*/
#include "../inc/Header_Fabricante.h"

/*------------------ Drivers -----------------------*/
void SPI0_Init_Master();
void SPI0_WriteByte(void);

// Buffer Control
void SPI0_TxPush(uint8_t *, uint8_t);
int8_t SPI0_TxPop(uint8_t *, uint8_t*);

/*------------------ SPI0 ISR Redefenition -----------------------*/
void SPI0_IRQHandler(void);

/*------------------ Propietary Defines -----------------------*/
#define TAM_TxBuffer 1024 // Defines the size of SPI0_TxBuffer.
#define NO_DATA -1
#define BYTE_TYPE_COMMAND 2
#define BYTE_TYPE_DATA 3



#endif
