#ifndef PR_DISPLAY_H_
#define PR_DISPLAY_H_

/*------------------ Includes ----------------------*/
#include "../inc/GPIO.h"
#include "../inc/DR_Systick.h"
#include "DR_fonts.h"
#include "DR_SPI.h"
#include "DR_big_numbers_fonts.h"

/*------------------ Send Data to Display ----------------------*/
void Display_SendCommand(uint8_t);
void Display_SendData(uint8_t);
void Display_SendString(char *);

void Display_SendTemp(char *Temp);
void Display_Send_BigNumber(uint8_t);
void Display_Send_CelsiusChar();

/*------------------- Control Functions -------------------*/
void Display_PositionXY(char, char);
void Display_Init(void);
void Display_Clear(void);

/*------------------- Timer --------------------------------*/
void MSdelay(unsigned int);

/*------------------- Propietary Defines --------------------------------*/
#define RST_PIN 19 // PIO0_19, pin 4
#define DCE_PIN 20 // PIO0_20, pin 5
#define LED_PIN 21 // PIO0_21, pin 6

#define OUT 1

#endif
