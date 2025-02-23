/**
 * Project Classes Placa Central
 */

#ifndef _TENSAOBATERIA_H
#define _TENSAOBATERIA_H

#include "Setupable.h"
#include "Constantes.h"

class TensaoBateria
{
public:
    static TensaoBateria *instance;
    static TensaoBateria *Setup();

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

    TensaoBateria(TensaoBateria &outro) = delete;

    TensaoBateria()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    double tensaoBateria;
};

TensaoBateria *TensaoBateria::instance{nullptr};
TensaoBateria *TensaoBateria::Setup()
{
    if (instance == nullptr)
    {
        instance = new TensaoBateria();
    }

    pinMode(DIV_TENSAO, INPUT);
    return instance;
}

#endif //_TENSAOBATERIA_H