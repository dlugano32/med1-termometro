/*
MLX90614 Library for Arduino 
Written by Damian Lugano / UTN-FRBA
*/

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Wire.h"

//typedef signed char 	int8_t;
//typedef unsigned char 	uint8_t;
//typedef short 			int16_t;
//typedef unsigned short 	uint16_t;
//typedef int 			int32_t;
//typedef unsigned int 	uint32_t;
//typedef unsigned char   byte;
//typedef unsigned char   size_t;

#define MLX90614_I2CADDR 0x5A

// SMBus command access opcode

// RAM
#define MLX90614_RAWIR1 0x04
#define MLX90614_RAWIR2 0x05
#define MLX90614_TA 0x06
#define MLX90614_TOBJ1 0x07
#define MLX90614_TOBJ2 0x08
// EEPROM
#define MLX90614_TOMAX 0x20
#define MLX90614_TOMIN 0x21
#define MLX90614_PWMCTRL 0x22
#define MLX90614_TARANGE 0x23
#define MLX90614_EMISS 0x24
#define MLX90614_CONFIG 0x25
#define MLX90614_ADDR 0x2E
#define MLX90614_ID1 0x3C
#define MLX90614_ID2 0x3D
#define MLX90614_ID3 0x3E
#define MLX90614_ID4 0x3F

/**
 * @brief Class to read from and control a MLX90614 Temp Sensor
 *
 */

class my_MLX90614 {
public:
  // Initialization functions
  my_MLX90614(uint8_t addr = MLX90614_I2CADDR); //Constructor
  void begin();

  // Functions for general use
  double readObjectTemp(void);
  double readAmbientTemp(void);

private:

  float readTemp(uint8_t reg);
  uint16_t read16(uint8_t reg);
  void write16(uint8_t reg, uint16_t data);
  byte crc8(byte *addr, size_t len);
  uint8_t slv_addr;  // MLX90601 slave addres
};
