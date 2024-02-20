/**
 * Project Classes Placa Central
 */


#ifndef _CONTADORPORINTERVALO_H
#define _CONTADORPORINTERVALO_H

class ContadorPorIntervalo {
public: 
    
int updateCountValue();
    
int getCountValue();
    
int somaTodasContagensNoUltimoMinuto();
protected: 
    FilaContador array;
    ulong MINUTO;
    int counter;
    int mediaCounter;
    
void increaseCount();
};

#endif //_CONTADORPORINTERVALO_H