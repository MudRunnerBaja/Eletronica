
#include <max6675.h>

/* Definições: GPIOs do Arduino utilizado na comunicação com o
   MAX6675 */
#define GPIO_SO 2
#define GPIO_CS 3
#define GPIO_CLK 4

/* Criação de objeto para comunicação com termopar */
MAX6675 termopar(GPIO_CLK, GPIO_CS, GPIO_SO);

float getCvtTemperature()
{
    return termopar.readCelsius();
}