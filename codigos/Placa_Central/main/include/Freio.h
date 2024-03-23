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
    Freio()
    {
        return;
    }
    /**
     * @return bool
     */
    bool Setup()
    {
        pinMode(NIVEL_FREIO, INPUT);
        return true;
    }

    /**
     * @return bool
     */
    bool Loop()
    {
        return false;
    }

    /**
     * @return bool
     */
    bool Debug()
    {
        return false;
    }

    /**
     * @return short
     */
    short getNivelAtual()
    {
        return 0;
    }

private:
    short nivelAtual;
};

#endif //_FREIO_H