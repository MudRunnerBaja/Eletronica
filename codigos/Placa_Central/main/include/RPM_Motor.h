/**
 * Project Classes Placa Central
 */

#ifndef _RPM_H
#define _RPM_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

class RPM_Motor : public Setupable
{
public:
    static RPM_Motor instance;

    static RPM_Motor *Setup()
    {
        instance = *new RPM_Motor();

        pinMode(RPM_INTERRUPT_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(RPM_INTERRUPT_PIN), updateRPM, RISING);
        told = micros();

        return &instance;
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

    /**
     * O AttachInterrupt requer uma referência estática para uma função.
     * Ele não é pensado para trabalhar com objetos ou classes.
     * Uma alternativa é trabalhar com o RPM como um singleton, mas tratar
     *  a função e das variáveis como estáticas envolve menos código.
     */
    static void updateRPM()
    {
        tpulse = micros() - told;
        rpm = MINUTO_EM_MICROSSEGUNDOS / tpulse;
        told = micros();
    }

private:
    volatile byte state = LOW;
    static long told;
    static long tpulse;
    static double rpm;
};

long RPM_Motor::told = 0;
long RPM_Motor::tpulse = 0;
double RPM_Motor::rpm = 0.0;

#endif //_RPM_H