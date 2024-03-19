/**
 * Project Classes Placa Central
 */

#ifndef _FREIO_H
#define _FREIO_H

#include "Setupable.h"
#include "Constantes.h"

class Freio : public Setupable
{
public:
    bool Setup();

    bool Loop();

    bool Debug();

    bool TestChosen(int escolhido);

    short getNivelAtual();

private:
    short nivelAtual;
};

#endif //_FREIO_H