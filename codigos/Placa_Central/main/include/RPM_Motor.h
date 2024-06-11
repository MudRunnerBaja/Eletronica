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
    static RPM_Motor *instance;
    static RPM_Motor *Setup();

    /**
     * O AttachInterrupt requer uma referência estática para uma função.
     * Ele não é pensado para trabalhar com objetos ou classes.
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

    RPM_Motor(RPM_Motor &outro) = delete;

    RPM_Motor()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    volatile byte state = LOW;
    static long told;
    static long tpulse;
    static double rpm;
};

// Implementações de variáveis e métodos estáticos.
// Especialmente importante que sejam feitos fora da função
// para o compilador do Arduino

RPM_Motor *RPM_Motor::instance{nullptr};
long RPM_Motor::told = 0;
long RPM_Motor::tpulse = 0;
double RPM_Motor::rpm = 0.0;

RPM_Motor *RPM_Motor::Setup()
{
    if (instance == nullptr)
    {
        instance = new RPM_Motor();
    }

    pinMode(RPM_INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RPM_INTERRUPT_PIN), updateRPM, RISING);
    told = micros();

    return instance;
}

void RPM_Motor::updateRPM()
{
    tpulse = micros() - told;
    rpm = MINUTO_EM_MICROSSEGUNDOS / tpulse;
    told = micros();
}

#endif //_RPM_H