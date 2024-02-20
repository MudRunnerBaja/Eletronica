/**
 * Project Classes Placa Central
 */


#ifndef _CONTADORPORINTERVALO_H
#define _CONTADORPORINTERVALO_H

#include "utils/FilaContador.h"

class ContadorPorIntervalo {
public: 
    
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