/**
 * Project Classes Placa Central
 */

#ifndef _RPM_H
#define _RPM_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

class RPM_Motor
{
public:
    static RPM_Motor *GetInstance();

    /**
     * O AttachInterrupt requer uma referência estática para uma função.
     * Isso é contornável tornando varíaveis e métodos estáticos.
     */
    static void updateRPM();
    bool Debug()
    {
        return true;
    }

    double getRPM()
    {
        return rpm;
    }

    void setValoresDeTeste()
    {
        rpm = (float)((random(RAND_MAX) / RAND_MAX) * 4200);
    }

public:
    RPM_Motor() = default;

private:
    static RPM_Motor *instance;

    volatile byte state = LOW;
    static long told;
    static long tpulse;
    static double rpm;
};

RPM_Motor *RPM_Motor::instance{nullptr};
long RPM_Motor::told = 0;
long RPM_Motor::tpulse = 0;
double RPM_Motor::rpm = 0.0;

RPM_Motor *RPM_Motor::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new RPM_Motor();

        pinMode(RPM_INTERRUPT_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(RPM_INTERRUPT_PIN), updateRPM, RISING);
        told = micros();
    }

    return instance;
}

void RPM_Motor::updateRPM()
{
    tpulse = micros() - told;
    rpm = MINUTO_EM_MICROSSEGUNDOS / tpulse;
    told = micros();
}

#endif //_RPM_H