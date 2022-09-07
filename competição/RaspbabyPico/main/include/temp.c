/* 
    Implementação do led de temperatura crítica da CVT 
*/

#include <max6675.h>
#define TEMPERATURA_CRITICA_CVT 80

/* Definições: GPIOs do Arduino utilizado na comunicação com o
   MAX6675 */
#define GPIO_SO 4
#define GPIO_CS 5
#define GPIO_CLK 6

int ledTempCvt = 24;

/* Criação de objeto para comunicação com termopar */
MAX6675 termopar(GPIO_CLK, GPIO_CS, GPIO_SO);
float temperaturaCVT;

void cvtSetup()
{
    pinMode(ledTempCvt, OUTPUT);
}

float setCvtTemperature()
{
    temperaturaCVT = termopar.readCelsius();
    if (temperaturaCVT > TEMPERATURA_CRITICA_CVT)
        digitalWrite(ledTempCvt, HIGH);
    else
        digitalWrite(ledTempCvt, LOW);
    return temperaturaCVT;
}
