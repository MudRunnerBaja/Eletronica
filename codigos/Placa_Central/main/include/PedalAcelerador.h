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
    bool Setup()
    {
        pinMode(PEDAL_ACELERADOR, INPUT);
        return true;
    }

    bool Loop()
    {
        return false;
    }

    double updateTensaoBateria()
    {
        pedalAcelerador;
        return pedalAcelerador;
    }

    bool Debug()
    {
        return false;
    }

    double getTensaoBateria()
    {
        return pedalAcelerador;
    }

private:
    double pedalAcelerador;
};

#endif //_PEDAL_ACELERADOR_H