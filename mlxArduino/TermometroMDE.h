#include <Wire.h>
#include <my_MLX90614.h>
#include <Arduino.h>

#define ESPERANDO 0
#define MIDIENDO_TEMP 1
#define DISPLAY_TEMP 2

#define CANT_MEDICIONES 10

extern my_MLX90614 mlx;

void boton_handler (void);

void TermometroMDE(void);
bool MedicionTemp(double *temp);
void displayTemp(double temp);
