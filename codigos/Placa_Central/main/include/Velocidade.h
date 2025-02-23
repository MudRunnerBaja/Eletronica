/**
 * Project Classes Placa Central
 */

#ifndef _VEL_H
#define _VEL_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

class Velocidade
{
public:
    Velocidade() = default;

public:
    static Velocidade *GetInstance();

    static void updateVel();
    bool Debug()
    {
        return true;
    }

    void setValoresDeTeste()
    {
        vel = (double)((random(RAND_MAX) / RAND_MAX) * 52);
    }

    double getVel()
    {
        // return 2.1;
        return vel;
    }

private:
    static Velocidade *instance;

    volatile byte state = LOW;
    static long told;
    static long tpulse;
    static double vel;
};

Velocidade *Velocidade::instance{nullptr};
Velocidade *Velocidade::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Velocidade();

        pinMode(VEL_INTERRUPT_PIN, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(VEL_INTERRUPT_PIN), updateVel, RISING);
        told = micros();
    }
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