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
    static Velocidade *instance;
    static Velocidade *Setup();

    /**
     * O AttachInterrupt requer uma referência estática para uma função.
     * Ele não é pensado para trabalhar com objetos ou classes.
     * Uma alternativa é trabalhar com a Velocidade como um singleton, mas tratar
     *  a função e das variáveis como estáticas envolve menos código.
     */
    static void updateVel();

    bool Debug()
    {
        return true;
    }

    double getVel()
    {
        return vel;
    }

    Velocidade(Velocidade &outro) = delete;

    Velocidade()
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
    static double vel;
};

Velocidade *Velocidade::instance{nullptr};
Velocidade *Velocidade::Setup()
{
    if (instance == nullptr)
    {
        instance = new Velocidade();
    }

    pinMode(VEL_INTERRUPT_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(VEL_INTERRUPT_PIN), updateVel, RISING);
    told = micros();
    return instance;
}

long Velocidade::told = 0;
long Velocidade::tpulse = 0;
double Velocidade::vel = 0.0;
void Velocidade::updateVel()
{
    tpulse = micros() - told;
    vel = MINUTO_EM_MICROSSEGUNDOS / tpulse;
    told = micros();
}

#endif //_VEL_H