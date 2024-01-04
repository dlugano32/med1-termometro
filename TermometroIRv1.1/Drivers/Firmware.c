#include "../inc/Firmware.h"

/*--------------------Drivers de I2C--------------------------------------*/

void ConfigClock_I2C0 (void)
{
    //Ver 19.7.1 del manual del LPC.

	SYSCON->PRESETCTRL0 &= ~(1<<5);		// Reset the I2C0 peripheral
	SYSCON->PRESETCTRL0 |= (1<<5);

	SYSCON->FCLKSEL[5] = 0x0;			//Selecciono FRO como fuente de clk de i2c

										// Habilito el clk del periferico de i2c
    SYSCON->SYSAHBCLKCTRL0 &= ~(1<<5);	// Limpio el Bit 5
    SYSCON->SYSAHBCLKCTRL0 |= (1<<5);	// Seteo en 1 el Bit 5

    SYSCON->SYSAHBCLKCTRL0 &=~(1<<7);	//Habilita el clock de la switch matrix
    SYSCON->SYSAHBCLKCTRL0 |= (1<<7);

	SWM0->PINENABLE0 &= ~(1<<12);	//Clear 0 I2C0_SDA enabled on pin PIO0_11.
	SWM0->PINENABLE0 &= ~(1<<13);	//Clear 0 I2C0_SCL enabled on pin PIO0_10.

    I2C0->CLKDIV = 0x12; //18 en decimal. Necesito que divida al clock del sistema por 19. Segun el manual si quiero dividir por 2 pongo un uno y asi.
    
    I2C0->MSTTIME &= ~(111 << 0); //Limpio los primeros 3 bits
    I2C0->MSTTIME |= (0x2 << 0); //Seteo los primeros 3 bits. Master SCL Low Time 4 Clocks
    
    I2C0->MSTTIME &= ~(111 << 4); //Limpio los bits 6:4
    I2C0->MSTTIME |= (0x2 << 4); //Master SCL High Time 4 Clocks

}

void ConfigPins_I2C0 (void)
{
    IOCON->PIO[IOCON_INDEX_PIO0_10] &= ~(11 << 8); //Configuro PIO0_10 como Standard Mode I2C. I2C0_SCL
    IOCON->PIO[IOCON_INDEX_PIO0_11] &= ~(11 << 8); //Configuro PIO0_11 como Standard Mode I2C. I2C0_SDA
}

void SetInterrupts_I2C0 (void)
{
    ISER0 |= (1 << 8); //Habilito las interrupciones generales del I2C0
}

void I2C0_Set_Interrupt_MSTPENDING (void)
{
    I2C0->INTENSET |= (1 << 0);
}

void I2C0_Clr_Interrupt_MSTPENDING (void)
{
    I2C0->INTENCLR |= (1 << 0);
}

void I2C0_Set_Master (void)
{
    I2C0->CFG = (1 << 0); //Seteo el Bit 0 en 1
}

void I2C0_Load_Send_Byte (uint8_t* byte)
{
    I2C0->MSTDAT = *byte;

}

void I2C0_Read_Received_Byte (uint8_t* byte)
{
    *byte = I2C0->MSTDAT;
}

void I2C0_Start_Signal (void)
{
    I2C0->MSTCTL = (1 << 1); //Señal de Start
}

void I2C0_Continue_Signal (void)
{
    I2C0->MSTCTL = (1 << 0); //Señal de Continue
}

void I2C0_Stop_Signal (void)
{
    I2C0->MSTCTL = (1 << 2); //Señal de Stop
}

/*--------------------Drivers de IOCON -----------------------------------*/


void SetClock_IOCON (void)
{
    SYSCON->SYSAHBCLKCTRL0 &= ~(1<<18); //Limpio el Bit 18
    SYSCON->SYSAHBCLKCTRL0 |= (1<<18); //Seteo en 1 el Bit 18
}

void ClrClock_IOCON (void)
{
    SYSCON->SYSAHBCLKCTRL0 &= ~(1<<18); //Limpio el Bit 18
}
