/**
 * Project Classes Placa Central
 */


#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include "Setupable.h"


class Comunicacao: public Setupable {
public: 
    
bool setup();

bool test();
/*
testarTelemetria;
testarCanBus;
testarI2c;
*/

bool testChosen(int escolhido);
    
void updateData();
    
/**
 * @param int
 */
void sendI2cDataTo(int slave);
    

private: 
    byte data;
};

#endif //_COMUNICACAO_H