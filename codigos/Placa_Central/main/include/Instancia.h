/**
 * Project Classes Placa Central
 */

#ifndef _INSTANCIA_H
#define _INSTANCIA_H

#include <Arduino.h>
#include "Setupable.h"
#include "Comunicacao.h"
#include "CartaoSD.h"
#include "TemperaturaCVT.h"
#include "Combustivel.h"
#include "RPM.h"
#include "GPS.h"
#include "Constantes.h"
#include "Freio.h"

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

    /**
     * Implementacao de uma instancia.
     * @param debugMode if true waits for Serial USB Port comm. Hangs the program indefinitely.
     * @param callSetup if true calls default initialization function. Defaults to true.
     */
    Instancia(bool debugMode, bool callSetup)
    {
        comunicacao = Comunicacao();

        while (debugMode && !Serial)
        {
            digitalWrite(LED_BUILTIN, LOW);
            int i = 0;
            while (i < 3)
            {
                digitalWrite(LED_BUILTIN, HIGH);
                delay(75);
                digitalWrite(LED_BUILTIN, LOW);
                delay(75);
            }
        }

        if (callSetup)
        {
            Setup();
        }
    }

    /**
     * @return bool
     */
    bool Setup()
    {
        bool check = false;
        /*
            freio.Setup();
            cartaoSD.Setup();
            comunicacao.setupCanBus();
            temperaturaCvt.Setup();

            gps.Setup();
        */
        return check;
    }

    /**
     * @return bool
     */
    bool EscreverSD()
    {
        return false;
    }

    /**
     * @return bool
     */
    bool AtualizarDados()
    {
        return false;
    }

    bool Debug()
    {
        return false;
    }

    /**
     * @return bool
     */
    bool EnviarDadosTelemetria()
    {
        /*
            String data = String(rpm.getRPM());
            data = String(data + ",");
            data = String(data + temperaturaCvt.getTemperaturaCvt());
            data = String(data + ",");
            data = String(data + gps.getSpeed());
            data = String(data + ",");
            data = String(data + nivelCombustivel.getNivelAtual());

            comunicacao.enviarDadosTelemetria(data);
            */
        return false;
    }

    bool EnviarDadosCanBus()
    {
        return false;
    }

    /**
     * @return bool
     */
    bool Loop()
    {
        return true;
    }

private:
    byte data[5];
};

#endif //_INSTANCIA_H