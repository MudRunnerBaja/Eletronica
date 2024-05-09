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
    bool Setup()
    {
        pinMode(NIVEL_FREIO, INPUT);
        return true;
    }

    bool Loop()
    {
        return false;
    }

    bool Debug()
    {
        return false;
    }

    short getTensaoBateria()
    {
        return 0;
    }

private:
    short tensaoBateria;
};

#endif //_TENSAOBATERIA_H