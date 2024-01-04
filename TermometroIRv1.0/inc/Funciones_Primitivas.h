#ifndef FUNCIONES_PRIMITIVAS_H_
#define FUNCIONES_PRIMITIVAS_H_

/*------------------Includes-----------------------------*/
#include <stdint.h>

/*------------------Defines-----------------------------*/
#define WRITE_BIT 0
#define READ_BIT 1
#define RAM_READ_TObj1_COMMAND  0x07

extern uint16_t rawTemp;
extern uint8_t flag_datoLeido;

/*------------------Inicializaciones---------------------*/
void Inicializacion_I2C0 (void);

/*--------------------Control del I2C0---------------------*/
void Leer_I2C0 (uint8_t slave_Adress);

/*---------------------Redefinición del Handler de I2C0 Interrupt--------------*/
void I2C0_IRQHandler(void);

/*---------------------Maquina de Estados para leer por I2C0--------------*/
void Initialize_FSM_Read_MLX90614_ObjectTemp (void);
void FSM_Read_MLX90614_ObjectTemp (void);

/*---------------------Enums---------------------------*/
enum STATES {SLAVE_ADDR_W, COMMAND, SLAVE_ADDR_RD, DATA_BYTE_LOW, DATA_BYTE_HIGH, PEC};
enum bools {false, true};

#endif
