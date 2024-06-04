/**
 * Project Classes Placa Central
 */

#ifndef _TENSAOBATERIA_H
#define _TENSAOBATERIA_H

#include "Setupable.h"
#include "Constantes.h"

class TensaoBateria : public Setupable
{
public:
    static TensaoBateria instance;

    TensaoBateria *Setup()
    {
        instance = *new TensaoBateria();
        pinMode(DIV_TENSAO, INPUT);
        return &instance;
    }

    bool Loop()
    {
        return false;
    }

    double updateTensaoBateria()
    {
        tensaoBateria;
        return tensaoBateria;
    }

    bool Debug()
    {
        return false;
    }

    double getTensaoBateria()
    {
        return tensaoBateria;
    }

private:
    double tensaoBateria;
};

#endif //_TENSAOBATERIA_H