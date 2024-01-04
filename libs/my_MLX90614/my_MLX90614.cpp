#include "my_MLX90614.h"

/*########################Public#############################*/

// Constructor
my_MLX90614::my_MLX90614(uint8_t i2caddr) 
{
    slv_addr = i2caddr; 
}

void my_MLX90614::begin(void)
{
    Wire.begin(); // initializes the scl and sda pins
}

double my_MLX90614 :: readObjectTemp(void)
{
    return readTemp(MLX90614_TOBJ1);
}

double my_MLX90614 :: readAmbientTemp(void)
{
    return readTemp(MLX90614_TA);
}

/*########################Private#############################*/

float my_MLX90614 :: readTemp(uint8_t reg)
{
    float temp=0;

    temp=read16(reg);
    temp*=0.02;     // Linearization of the temperature
    temp-=273.15;   // Kelvin to Celsius

    return temp;
}

uint16_t my_MLX90614 :: read16(uint8_t reg)
{   // Only for Arduino
    uint16_t raw_temp;
    uint8_t pec;

    Wire.beginTransmission(slv_addr);   // start transmission to MLX90614
    Wire.write(reg);                    // sends register address to read from
    Wire.endTransmission(false);

    Wire.requestFrom(slv_addr, (size_t)3); // request 3 bytes to read
    raw_temp = Wire.read();
    raw_temp |= Wire.read() << 8;

    pec=Wire.read();

    return raw_temp;
}

void my_MLX90614 :: write16(uint8_t reg, uint16_t data)
{
    uint8_t pec, pecbuf[4];

    pecbuf[0] = slv_addr << 1;
    pecbuf[1] = reg;
    pecbuf[2] = data & 0xff;
    pecbuf[3] = data >>8;

    pec=crc8(pecbuf, (size_t)4);

    Wire.beginTransmission(slv_addr);   // start transimission to device
    Wire.write(reg);                    // sends registre addres to write
    Wire.write(data & 0xff);            // data byte low
    Wire.write(data >> 8);              // data byte high
    Wire.write(pec);                    // pec
    Wire.endTransmission(true);         // end transmission
}

byte my_MLX90614 :: crc8(byte *data, size_t len)
// The PEC calculation includes all bits except the START, REPEATED START, STOP,
// ACK, and NACK bits. The PEC is a CRC-8 with polynomial X8+X2+X1+1.
// PEC is packet error code
{
    uint8_t crc = 0;
    uint8_t polynomial = 0x07;  // Polynomial X8+X2+X1+1

    for (size_t i = 0; i < len; ++i)
    {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8; ++bit)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ polynomial;
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}