/* 
    Implementação do led de temperatura crítica da CVT 
*/
#ifndef TEMPERATURA_CVT
#define TEMPERATURA_CVT

#include <max6675.h>

#define CVT_SO 2 // DATA PIN
#define CVT_CS 3 // CHIP SELECT
#define CVT_CLK 4 // CLOCK

float temperaturaCVT;

MAX6675 termopar(CVT_CLK, CVT_CS, CVT_SO); // Objeto para o termopar

float setCvtTemperature()
{
    temperaturaCVT = termopar.readCelsius();
    return temperaturaCVT;
}

float getTempCvt()
{
    return temperaturaCVT;
}

#endif