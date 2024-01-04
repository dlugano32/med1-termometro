
#ifndef FIRMWARE_H_
#define FIRMWARE_H_

/*--------------------Includes------------------------*/
#include "../inc/Header_Fabricante.h"

extern uint8_t flag_datoLeido;

/*--------------------Drivers de I2C--------------------------------------*/
//void SetClock_I2C0 (void);
void ConfigClock_I2C0 (void);
void ConfigPins_I2C0 (void);
void SetInterrupts_I2C0 (void);
void I2C0_Set_Interrupt_MSTPENDING (void);
void I2C0_Clr_Interrupt_MSTPENDING (void);
void I2C0_Set_Master (void);
void I2C0_Load_Send_Byte (uint8_t* Send_Byte);
void I2C0_Read_Received_Byte (uint8_t* byte);
void I2C0_Start_Signal (void);
void I2C0_Continue_Signal (void);
void I2C0_Stop_Signal (void);
//void ConfigPins_SWM0(void);
//void SetClock_SWM0(void);

/*--------------------Drivers de IOCON -----------------------------------*/
void SetClock_IOCON (void);
void ClrClock_IOCON (void);


#endif
