/**
 * Project Classes Placa Central
 */

#ifndef _CONTADORPORINTERVALO_H
#define _CONTADORPORINTERVALO_H

#include <Arduino.h>
#include "FilaContador.h"
#include "../Constantes.h"

class ContadorPorIntervalo
{
protected:
    FilaContador array;
    unsigned long MINUTO;
    int counter;
    int mediaCounter;

    void increaseCount()
    {
        counter++;
        return;
    }

public:
    ContadorPorIntervalo(int pinToMonitor, unsigned long intervalToUpdate = INTERVALO_TIMER_MS)
    {
        pinMode(pinToMonitor, INPUT);
        this->MINUTO = intervalToUpdate;
        array = *(new FilaContador(intervalToUpdate));
        attachInterrupt(digitalPinToInterrupt(pinToMonitor), increaseCount, RISING);
    }

    int updateCountValue()
    {
        int countInstantaneoAtual = counter * MINUTO;
        int somaCountAnteriores = (mediaCounter * array.currentSize);
        array.InsertLast(countInstantaneoAtual);
        int mediaCounter = (countInstantaneoAtual + somaCountAnteriores) / array.currentSize;
        counter = 0;
        return mediaCounter;
    }

    int getCountValue()
    {
        return mediaCounter;
    }
    int somaTodasContagensNoUltimoMinuto()
    {
        return (mediaCounter * array.currentSize);
    }
};

#endif //_CONTADORPORINTERVALO_H