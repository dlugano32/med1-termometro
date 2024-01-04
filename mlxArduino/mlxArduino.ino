#include "TermometroMDE.h"

void setup() 
{
  Serial.begin(9600);
  mlx.begin();

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), boton_handler, RISING);
}

void loop() 
{
  TermometroMDE();
}