/**
 * Project Classes Placa Central
 */


#ifndef _VELOCIDADE_H
#define _VELOCIDADE_H

#include "ContadorPorIntervalo.h"
#include "Setupable.h"


class Velocidade: public ContadorPorIntervalo, public Setupable {
public: 
    
void velSetup();
    
int getVel();
    
int updateVel();
};

#endif //_VELOCIDADE_H