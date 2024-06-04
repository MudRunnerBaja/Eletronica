/**
 * Project Classes Placa Central
 */

#ifndef _VEL_H
#define _VEL_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

class Velocidade : public Setupable
{
public:
    static Velocidade instance;

    Velocidade *Setup()
    {
        instance = *new Velocidade();

        pinMode(VEL_INTERRUPT_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(VEL_INTERRUPT_PIN), updateVel, RISING);
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

    double getVel()
    {
        return vel;
    }

    /**
     * O AttachInterrupt requer uma referência estática para uma função.
     * Ele não é pensado para trabalhar com objetos ou classes.
     * Uma alternativa é trabalhar com a Velocidade como um singleton, mas tratar
     *  a função e das variáveis como estáticas envolve menos código.
     */
    static void updateVel()
    {
        tpulse = micros() - told;
        vel = MINUTO_EM_MICROSSEGUNDOS / tpulse;
        told = micros();
    }

private:
    volatile byte state = LOW;
    static long told;
    static long tpulse;
    static double vel;
};

#endif //_VEL_H