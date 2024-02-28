/**
 * Project Classes Placa Central
 */


#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include "Setupable.h"
#include <Arduino.h>


class Comunicacao: public Setupable {
public: 
    
bool setup();

bool setupTelemetria();

void enviarDadosTelemetria(String data);

bool setupCanBus();

bool setupI2c();


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
    
bool testTelemetria();

bool testCanBus();

bool testI2c();

private: 
};

#endif //_COMUNICACAO_H