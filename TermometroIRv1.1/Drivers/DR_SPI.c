#include "../inc/DR_SPI.h"

/*------------------ SPI0 Tx Buffer  -----------------------*/
uint8_t SPI0_TxBuffer[TAM_TxBuffer];
uint8_t SPI0_TxBuffer_ByteType[TAM_TxBuffer];

uint32_t Index_SPI0_TxBuffer_IN = 0;
uint32_t Index_SPI0_TxBuffer_OUT = 0;

/*------------------ Drivers -----------------------*/
void SPI0_Init_Master()
{
    /*---- Set and select Peripheral Clock, Reset the peripheral, Enable interrupts  -----*/

    SYSCON->SYSAHBCLKCTRL0 |= (1 << 11); // Enables Clock for SPI0

    SYSCON->FCLKSEL[9] = 0x0; // Sets FRO Clock as Peripheral Clock for SPI0 (12 Mhz)

    SYSCON->PRESETCTRL0 &= ~(1 << 11); // Asserts the SPI0 Reset
    SYSCON->PRESETCTRL0 |= (1 << 11);  // Clears the SPI0 Reset

    ISER0 |= (1 << 0); // ISE_SPI0 Interrupt enable

    /*---- Config Peripheral pins  -----*/

    SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // Enables clock for switch matrix

    SWM0->PINASSIGN_DATA[3] &= ~(0xFF << 24); // Clears bits 24 to 31
    SWM0->PINASSIGN_DATA[3] |= (16 << 24);    // Assigns SPI0_SCK_IO to pio_16 (pin 1)

    SWM0->PINASSIGN_DATA[4] &= ~(0xFF << 0); // Clears bits 0 to 7
    SWM0->PINASSIGN_DATA[4] |= (17 << 0);    // Assigns SPI0_MOSI_IO to pio_17 (pin 2)

    SWM0->PINASSIGN_DATA[4] &= ~(0xFF << 16); // Clears bits 16 to 23
    SWM0->PINASSIGN_DATA[4] |= (18 << 16);     // Assigns  SPI0_SSEL0_IO to pio_18 (pin 3)

    SWM0->PINASSIGN_DATA[4] &= ~(0xFF << 24); // Clears bits 24 to 31
    SWM0->PINASSIGN_DATA[4] |= (20 << 24);     // Assigns  SPI0_SSEL1_IO to pio_20 (pin 5) (Actually used for the DCE of the display, to change between data and command)

    SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7); // Disables clock for switch matrix

    /*---- Config the Peripheral -----*/

    SPI0->DIV = 11; // Sets SPI Clock Rate (for communicating) to 1 Mhz

    SPI0->CFG |= (1 << 0); // The SPI is enabled for operation.

    SPI0->CFG |= (1 << 2); // Master mode. The SPI will operate in master mode. SCK, MOSI, and the SSEL signals are outputs, MISO is an input.

    // LSFB BIT. By default, Data is transmitted and received in standard MSB first order

    // set mode 3 cpol 1 cpha 1
    SPI0->CFG |= (1 << 4); // Sets CPHA = 1. Capture. The SPI changes serial data on the first clock transition of the transfer (when the clock changes away from the rest state). Data is captured on the following edge.
    SPI0->CFG |= (1 << 5); // Sets CPOl = 1. High. The rest state of the clock (between transfers) is high.

    // SPOL BIT0 By default, The SSEL0 pin is active low. The value in the SSEL0 fields of the RXDAT, TXDATCTL, and TXCTL registers related to SSEL0 is not inverted relative to the pins.

    SPI0->TXCTL |= (1 << 16); // SSEL0 not asserted

    SPI0->TXCTL |= (1 << 17); // SSEL1 not asserted

    SPI0->TXCTL |= (1 << 22); //  Ignore received data. Received data is ignored, allowing transmission without reading unneeded received data. No receiver flags are generated.

    SPI0->TXCTL |= (7 << 24); // Data is 8 bits long
}

void SPI0_WriteByte(void)
{
    uint8_t auxByte, byteType;

    if (SPI0_TxPop(&auxByte, &byteType) != NO_DATA) // if there is data to send
    {
        SPI0->TXCTL &= ~(1 << 16); // SSEL0 is asserted

        if (byteType == BYTE_TYPE_DATA) //the byte to send is data
        {   
            SPI0->TXCTL |= (1 << 17); // SSEL1 not asserted. This makes pin 5 go high during transmission, which means that the display will treate the byte received as data
        }

        if (byteType == BYTE_TYPE_COMMAND)
        {
            SPI0->TXCTL &= ~(1 << 17); // SSEL1 asserted. This makes pin 5 go low during transmission, which means that the display will treate the byte received as command
        }

        SPI0->TXCTL |= (1 << 20); // SSEL deasserted. This piece of data is treated as the end of a transfer. SSEL will be deasserted at the end of this piece of data

        SPI0->TXDAT = auxByte; // Transmit Data.
    }

    else // if there is no data to send
    {
        SPI0->INTENCLR |= (1 << 1); // An interrupt wont be generated when data may be written to TXDAT. Disables Interrupts
    }
}

// Buffer Control
void SPI0_TxPush(uint8_t *pData, uint8_t data_type)
{
    SPI0_TxBuffer[Index_SPI0_TxBuffer_IN] = *pData;
    SPI0_TxBuffer_ByteType[Index_SPI0_TxBuffer_IN] = data_type;

    Index_SPI0_TxBuffer_IN++;

    if (Index_SPI0_TxBuffer_IN == TAM_TxBuffer) // Circular Buffer
    {
        Index_SPI0_TxBuffer_IN = 0;
    }

    SPI0->INTENSET |= (1 << 1); // An interrupt will be generated when data may be written to TXDAT.
}

int8_t SPI0_TxPop(uint8_t *pDestiny, uint8_t *byteType)
{

    if (Index_SPI0_TxBuffer_IN == Index_SPI0_TxBuffer_OUT) // Buffer is empty
    {
        return NO_DATA;
    }
    else
    {
        *pDestiny = SPI0_TxBuffer[Index_SPI0_TxBuffer_OUT];
        *byteType = SPI0_TxBuffer_ByteType[Index_SPI0_TxBuffer_OUT];
        Index_SPI0_TxBuffer_OUT++;

        if (Index_SPI0_TxBuffer_OUT == TAM_TxBuffer) // Circular Buffer
        {
            Index_SPI0_TxBuffer_OUT = 0;
        }
    }

    return 0;
}

/*------------------ SPI0 ISR Redefinition -----------------------*/
void SPI0_IRQHandler(void)
{
    uint8_t SPI0_Stat;

    SPI0_Stat = SPI0->INTSTAT;

    if (((SPI0_Stat >> 1) & 1) == 1)
    { // Transmitter Ready flag Check
        SPI0_WriteByte();
    }
}
