/**
 * Project Classes Placa Central
 */


#ifndef _INSTANCIA_H
#define _INSTANCIA_H

#include "Setupable.h"


class Instancia: public Setupable {
public: 
    Comunicacao comunicacao;
    CartaoSD cartaoSD;
    TemperaturaCVT temperaturaCvt;
    Combustivel nivelCombustivel;
    RPM rpm;
    GPS gps;
    void Attribute1;
    Array<bool> estadoSistemas;
    void testeSistemas;
    
bool setupInstancia();
    
bool EscreverSD();
    
bool AtualizarDados();
    
bool EnviarDados();
    
void testarSistemas();
};

#endif //_INSTANCIA_H