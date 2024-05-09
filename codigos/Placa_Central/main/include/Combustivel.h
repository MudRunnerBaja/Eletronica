/**
 * Project Classes Placa Central
 */

#ifndef _COMBUSTIVEL_H
#define _COMBUSTIVEL_H

#include "Setupable.h"
#include "Constantes.h"

class Combustivel : public Setupable
{
public:
    bool Setup()
    {
        return false;
    }

    bool Loop()
    {
        return false;
    }

    bool Debug()
    {
        return false;
    }

    short setNivelAtual()
    {
        return 0;
    }

    short getNivelAtual()
    {
        return 0;
    }

private:
    short nivelAtual;
};

#endif //_COMBUSTIVEL_H