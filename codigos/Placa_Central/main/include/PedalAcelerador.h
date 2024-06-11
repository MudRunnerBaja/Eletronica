/**
 * Project Classes Placa Central
 */

#ifndef _PEDAL_ACELERADOR_H
#define _PEDAL_ACELERADOR_H

#include "Setupable.h"
#include "Constantes.h"

class PedalAcelerador : public Setupable
{
public:
    static PedalAcelerador *instance;
    static PedalAcelerador *Setup();

    double getPedalAcelerador()
    {
        return pedalAcelerador;
    }

    double updatePedalAcelerador()
    {
        pedalAcelerador;
        return pedalAcelerador;
    }

    bool Debug()
    {
        return false;
    }

    bool Loop()
    {
        return false;
    }

    PedalAcelerador(PedalAcelerador &outro) = delete;

    PedalAcelerador()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    double pedalAcelerador;
};

PedalAcelerador *PedalAcelerador::instance{nullptr};
PedalAcelerador *PedalAcelerador::Setup()
{
    if (instance == nullptr)
    {
        instance = new PedalAcelerador();
    }

    pinMode(PEDAL_ACELERADOR, INPUT);
    return instance;
}

#endif //_PEDAL_ACELERADOR_H