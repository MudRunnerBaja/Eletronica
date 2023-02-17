/* 
    Implementação do led de temperatura crítica da CVT 
*/
#include <declarations.h>

float setCvtTemperature()
{
    temperaturaCVT = termopar.readCelsius();
    return temperaturaCVT;
}

float getTempCvt()
{
    return temperaturaCVT;
}