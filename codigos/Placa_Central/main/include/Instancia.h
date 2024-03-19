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
#include "Constantes.h"
#include "Freio.h"
#include <RPi_Pico_ISR_Timer.hpp>    // Manipuladores de Interrupção
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h>      // Manipuladores de Interrupção

class Instancia : public Setupable
{

public:
    Comunicacao comunicacao;
    CartaoSD cartaoSD;
    TemperaturaCVT temperaturaCvt;
    Combustivel nivelCombustivel;
    RPM rpm;
    GPS gps;
    Freio freio;
    bool *estadoSistemas;
    bool *testeSistemas;

    Instancia(bool debugMode = false, bool callSetup = true);

    bool Setup();

    bool Loop();

    bool Debug();

    bool TestChosen(int escolhido);

    bool EscreverSD();

    bool AtualizarDados();

    bool EnviarDadosTelemetria();

    bool EnviarDadosCanBus();

private:
    byte data[5];
};

#endif //_INSTANCIA_H