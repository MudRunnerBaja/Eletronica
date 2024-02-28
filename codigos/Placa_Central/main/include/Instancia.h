/**
 * Project Classes Placa Central
 */


#ifndef _INSTANCIA_H
#define _INSTANCIA_H

#include "Setupable.h"
#include "Comunicacao.h"
#include "CartaoSD.h"
#include "TemperaturaCVT.h"
#include "Combustivel.h"
#include "RPM.h"
#include "GPS.h"
#include <Arduino.h>

class Instancia: public Setupable {
public: 
    Comunicacao comunicacao;
    CartaoSD cartaoSD;
    TemperaturaCVT temperaturaCvt;
    Combustivel nivelCombustivel;
    RPM rpm;
    GPS gps;
    bool* estadoSistemas;
    bool* testeSistemas;
    
bool setup();

bool test();

bool testChosen(int escolhido);
    
bool EscreverSD();
    
bool AtualizarDados();
    
bool EnviarDadosTelemetria();
    
bool EnviarDadosCanBus();

private:
    byte data[5];

};

#endif //_INSTANCIA_H