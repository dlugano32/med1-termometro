#include "../inc/PR_display.h"

/*------------------ Send Data to Display ----------------------*/

void Display_SendCommand(uint8_t command)
{
    SPI0_TxPush(&command, BYTE_TYPE_COMMAND);

    // DC = 0;         // Data Command Pin = 0 -> Receive Command Mode
    // CS = 0;         // Chip Enable Pin = 0 -> Chip Enabled
    // SPI_Write(cmd); /* write command to the Display 5110 */
    // CS = 1;         // Chip Enable Pin = 1 -> Chip Disabled
}

void Display_SendData(uint8_t dat)
{
    uint8_t byteAux = 0;

    // DC = 1; // Data Command Pin = 1 -> Receive Data Mode
    // CS = 0; // Chip Enable Pin = 0 -> Chip Enabled
    for (uint8_t i = 0; i < 5; i++)
    {
        byteAux = font[(dat) - (0x20)][i];
        SPI0_TxPush(&byteAux, BYTE_TYPE_DATA);
    } /* write data to the Nokia 5110 */
    // CS = 1;                                 // Chip Enable Pin = 1 -> Chip Disabled
}

void Display_SendString(char *data)
{
    while ((*data) != 0) // calculo que significa que es distinto de NULL
    {
        Display_SendData(*data);
        data++;
    }
}

/*------------------- Control and Init Functions -------------------*/

void Display_Init()
{
    SPI0_Init_Master(); // Initializes SPI0 in master mode. pin 1 (pio_16) -> SPI0_SCK; pin 2 (pio_17) -> SPI0_MOSI; pin 3 (pio_18) -> SPI0_SSEL0 (chip enable)

    // Set Pins as Outputs
    SetDIR(0, RST_PIN, OUT);
    // SetDIR(0, DCE_PIN, OUT);
    SetDIR(0, LED_PIN, OUT);

    // Capaz hay que poner pins en modo pull down

    // /*apply 100 ms reset(low to high) pulse */
    SetPIN(0, RST_PIN, 0); /* enable reset */
    MSdelay(100);
    SetPIN(0, RST_PIN, 1); /* disable reset */

    Display_SendCommand(0x21); /* display extended commands*/
    Display_SendCommand(0x13); /* select Bias voltage*/
    Display_SendCommand(0x07); /* set temperature coefficient*/
    Display_SendCommand(0xC0); /* set LCD Vop for contrast */
    Display_SendCommand(0x20); /* display basic commands (chip is active, horizontal addressing, use basic instruction set)*/
    Display_SendCommand(0x0C); /* set normal mode */

    Display_Clear();          /* clear Display */
    Display_PositionXY(0, 0); /* set X and Y position for printing */
}

void Display_PositionXY(char X, char Y)
{
    Display_SendCommand(0x80 | X); /* set X position */
    Display_SendCommand(0x40 | Y); /* set Y position */
}

void Display_Clear()
{
    char i, j;
    // //CS = 0; // Chip Enable Pin = 0 -> Chip Enabled
    // SetPIN(DCE_PIN,1) = 1; // Data Command Pin = 1 -> Receive Data Mode
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 84; j++)
            Display_SendData(' '); /*write 0 to clear display */
    }
    // CS = 1; // Chip Enable Pin = 1 -> Chip Disabled

    Display_PositionXY(0,0);
}
