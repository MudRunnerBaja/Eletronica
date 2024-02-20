/**
 * Project Classes Placa Central
 */


#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include "Setupable.h"


class Comunicacao: public Setupable {
public: 
    
void displaySetup();
    
void updateData();
    
/**
 * @param int
 */
void sendI2cDataTo(void int);
    
void Operation1();
    
bool testarTelemetria();
    
bool testarCanBus();
    
bool testarI2c();
private: 
    byte data;
};

#endif //_COMUNICACAO_H