/**
 * Project Classes Placa Central
 */

#ifndef _RPM_H
#define _RPM_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

class RPM : public Setupable
{
public:
    bool Setup()
    {
        pinMode(RPM_INTERRUPT_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(RPM_INTERRUPT_PIN), updateRPM, RISING);
        told = micros();
        return true;
    }

    bool Loop()
    {
        return false;
    }

    bool Debug()
    {
        return true;
    }

    double getRPM()
    {
        return rpm;
    }

    double updateRPM()
    {
        tpulse = micros() - told;
        rpm = 60000000 / tpulse; // O que é essa constante?
        told = micros();
        return rpm;
    }

private:
    volatile byte state = LOW;
    long told = 0, tpulse = 0;
    double rpm = 0;
};

#endif //_RPM_H