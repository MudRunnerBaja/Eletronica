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
    RPM(int maximumSize = Constantes::MINUTO);

    bool Setup();

    bool Loop();

    bool Debug();

    bool TestChosen(int escolhido);

    int getRPM();

    int updateRPM();
};

#endif //_RPM_H