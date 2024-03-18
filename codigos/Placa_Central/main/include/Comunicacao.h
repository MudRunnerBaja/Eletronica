/**
 * Project Classes Placa Central
 */


#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include <Arduino.h>
#include <CAN.h>
#include "Setupable.h"
#include "Constantes.h"


class Comunicacao: public Setupable {
public: 
    
bool Setup();

bool Test();

bool Debug();

bool TestChosen(int escolhido);

bool setupTelemetria();

/**
* CAN-BUS by Sandeep Mistry
* https://github.com/sandeepmistry/arduino-CAN/blob/master/API.md
*/
bool setupCanBus();
    
void enviarDadosTelemetria(String data);

void updateData();
    
/**
 * @param int CAN Id that should receive the message
 * @param byte* Pointer to buffer with data 
 * @param int buffer size
 * @return int - Number of bytes written
 */
void Comunicacao::sendCanDataTo(int receiverId, byte buffer[], int length);

private: 
};

#endif //_COMUNICACAO_H