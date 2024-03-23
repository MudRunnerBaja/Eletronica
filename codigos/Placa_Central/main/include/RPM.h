/**
 * Project Classes Placa Central
 */

#ifndef _RPM_H
#define _RPM_H

#include "utils/ContadorPorIntervalo.h"
#include "Setupable.h"
#include "Constantes.h"

class RPM : public ContadorPorIntervalo, public Setupable
{
public:
    RPM(int maximumSize = Constantes::MINUTO)
    {
        return;
    }

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

    int getRPM()
    {
        return 0;
    }

    int updateRPM()
    {
        return 0;
    }
};

#endif //_RPM_H