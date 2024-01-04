/*************************************************** 
  This is a library example for the MLX90614 Temp Sensor

  This sensor use I2C to communicate, 2 pins are required to interface
  
  This library was made by Damian Lugano
 ****************************************************/

#include <Wire.h>
#include <my_MLX90614.h>

my_MLX90614 mlx = my_MLX90614();

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTemp()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTemp()); Serial.println("*C");

  Serial.println();
  delay(500);
}