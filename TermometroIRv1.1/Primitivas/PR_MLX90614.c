#include "../inc/PR_MLX90614.h"

#include "../inc/Firmware.h"

uint8_t I2C0_adr_Buffer;
uint8_t STATE;
uint16_t I2C0_read_Buffer;
uint8_t I2C0_PEC_Buffer;
uint16_t rawTemp=0;
uint8_t flag_datoLeido=false;

/*------------------Inicializaciones---------------------*/
void Inicializacion_I2C0 (void)
{
	//Configuración del periferico de I2C
    ConfigClock_I2C0();

    //Configurar como Maestro
    I2C0_Set_Master();

    //Habilitar Interrupciones
    SetInterrupts_I2C0();

    //Setear Pines
    SetClock_IOCON(); //Habilito el Clock de IOCON
    ConfigPins_I2C0();
    ClrClock_IOCON(); //Apago el Clock de IOCON para ahorrar energia

}

/*--------------------Control del I2C0---------------------*/
void Leer_I2C0 (uint8_t slave_Adress)
{

	I2C0_adr_Buffer = slave_Adress;

    Initialize_FSM_Read_MLX90614_ObjectTemp ();

    I2C0_Set_Interrupt_MSTPENDING (); //Habilito interrupciones por el flag mstpending

    //FSM_Read_MLX90614_ObjectTemp ();

}

/*---------------------Redefinición del Handler de I2C0 Interrupt--------------*/
void I2C0_IRQHandler(void)
{
    //chequear si termino la mde, si no termino llamarla. si termino deshabilitar interrupciones

    if(flag_datoLeido == false)
    {
    	FSM_Read_MLX90614_ObjectTemp ();
    }

    if(flag_datoLeido == true)
    {
    I2C0_Clr_Interrupt_MSTPENDING ();    
    }
    
}

/*---------------------Maquina de Estados para leer por I2C0--------------*/
void Initialize_FSM_Read_MLX90614_ObjectTemp (void)
{
    STATE = SLAVE_ADDR_W;
    I2C0_read_Buffer= 0;
    //flag_datoLeido = false;
}

void FSM_Read_MLX90614_ObjectTemp (void)
{

    uint8_t byteAux;
    switch (STATE)
    {
    case SLAVE_ADDR_W:

        byteAux = I2C0_adr_Buffer << 1; //Desplazo 1 lugar a la derecha, poniendo un 0. El LSB en 0 significa WR

        I2C0_Load_Send_Byte(&byteAux); 
        I2C0_Start_Signal();

        STATE = COMMAND;

        break;

    case COMMAND:

        byteAux = RAM_READ_TObj1_COMMAND;

        I2C0_Load_Send_Byte(&byteAux);
        I2C0_Continue_Signal();

        STATE = SLAVE_ADDR_RD;

        break;

    case SLAVE_ADDR_RD:

        byteAux = (I2C0_adr_Buffer << 1) | (1 << 0); //Desplazo 1 lugar a la derecha, poniendo un 0, despues pongo un 1. El LSB en 1 significa RD
        I2C0_Load_Send_Byte(&byteAux); 

        I2C0_Start_Signal();

        STATE = DATA_BYTE_LOW;

        break;

    case DATA_BYTE_LOW:

        I2C0_Read_Received_Byte(&byteAux);
        I2C0_read_Buffer = 0xff & byteAux;

        I2C0_Continue_Signal();

        STATE = DATA_BYTE_HIGH;

        break;

    case DATA_BYTE_HIGH:

        I2C0_Read_Received_Byte(&byteAux);
        I2C0_read_Buffer |= (byteAux << 8);

        I2C0_Continue_Signal();

        STATE = PEC;

        break;

    case PEC:

        I2C0_Read_Received_Byte(&byteAux);
        I2C0_PEC_Buffer = byteAux;

        I2C0_Stop_Signal();

        rawTemp=I2C0_read_Buffer;

        flag_datoLeido = true;

        STATE = SLAVE_ADDR_W;

        break;

    default:
        break;
    }
}
