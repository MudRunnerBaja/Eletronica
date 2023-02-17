/* 
    Implementação da contagem de rpm do carro 
*/
#ifndef RPM_MOTOR
#define RPM_MOTOR

#include <declarations.h>

#define RPM_INPUT_PIN 28 // PINO DE SINAL DO RPM

int rpmCounter = 0;
int rpmGlobal;

float setRpm()
{
    rpmGlobal = rpmCounter * MINUTO;
    rpmCounter = 0;
    return rpmGlobal;
}

float getRpm()
{
    return rpmGlobal;
}

void rpmCounterFunc()
{
    rpmCounter++;
}

void rpmSetup()
{
    pinMode(RPM_INPUT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RPM_INPUT_PIN), rpmCounterFunc, RISING);
}
#endif