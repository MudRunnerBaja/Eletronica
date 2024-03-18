/**
 * Project Classes Placa Central
 */


#ifndef _CONTADORPORINTERVALO_H
#define _CONTADORPORINTERVALO_H

#include "FilaContador.h"
#include "../Constantes.h"

class ContadorPorIntervalo {
public: 

ContadorPorIntervalo(int maximumSize = Constantes::MINUTO);
    
int updateCountValue();
    
int getCountValue();
    
int somaTodasContagensNoUltimoMinuto();
protected: 
    FilaContador array;
    unsigned long MINUTO;
    int counter;
    int mediaCounter;
    
void increaseCount();
};

#endif //_CONTADORPORINTERVALO_H