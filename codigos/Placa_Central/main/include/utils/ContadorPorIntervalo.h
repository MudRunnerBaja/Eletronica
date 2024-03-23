/**
 * Project Classes Placa Central
 */

#ifndef _CONTADORPORINTERVALO_H
#define _CONTADORPORINTERVALO_H

#include "FilaContador.h"
#include "../Constantes.h"

class ContadorPorIntervalo
{
public:
    ContadorPorIntervalo(int maximumSize = Constantes::MINUTO)
    {
        return;
    }

    int updateCountValue()
    {
        return 0;
    }

    int getCountValue()
    {
        return 0;
    }
    int somaTodasContagensNoUltimoMinuto()
    {
        return 0;
    }

protected:
    FilaContador array;
    unsigned long MINUTO;
    int counter;
    int mediaCounter;

    void increaseCount()
    {
        return;
    }
};

#endif //_CONTADORPORINTERVALO_H