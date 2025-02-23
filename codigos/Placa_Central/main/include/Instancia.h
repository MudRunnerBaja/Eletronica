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
#include "RPM_Motor.h"
#include "GPS.h"
#include "Constantes.h"
#include "Freio.h"
#include "Velocidade.h"
#include "Dados.h"

/**
 * Esse é o principal caso de exemplo para Singletons.
 * https://refactoring.guru/pt-br/design-patterns/singleton/cpp/example#example-1
 */
class Instancia
{
public:
    Instancia() = default;

public:
    static Instancia *GetInstance(bool debugMode, bool callSetup);

    bool *estadoSistemas;
    bool *testeSistemas;

    void TesteAtualizarDados()
    {
        temperaturaCvt.setValoresDeTeste();
        rpm.setValoresDeTeste();
        nivelCombustivel.setValoresDeTeste();
        freio.setValoresDeTeste();
        velocidade.setValoresDeTeste();
    }

    bool DebugLoop()
    {
        gps.Debug();
        comunicacao.Debug();
        temperaturaCvt.Debug();
        rpm.Debug();
        nivelCombustivel.Debug();
        freio.Debug();
        velocidade.Debug();
        cartaoSD.Debug();

        return false;
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
        dados.atualizarDados(
            nivelCombustivel.getNivelAtual(),
            freio.getNivelAtual(),
            freio.getPressaoAtual(),
            0.0, // Pedal Acelerador
            0.0, // Tensao Bateria
            temperaturaCvt.getTemperaturaObjeto(),
            temperaturaCvt.getTemperaturaAmbiente(),
            rpm.getRPM(),
            velocidade.getVel());

        return false;
    }

    void printarDados()
    {
        Serial.println(dados.formatarDados());
    }

    /**
     * @return bool
     */
    bool EnviarDadosTelemetria()
    {
        String data = String(rpm.getRPM());
        data = String(data + ",");
        data = String(data + temperaturaCvt.getTemperaturaObjeto());
        data = String(data + ",");
        data = String(data + gps.getSpeed());
        data = String(data + ",");
        data = String(data + nivelCombustivel.getNivelAtual());
        comunicacao.enviarDadosTelemetria(data);
        return false;
    }

    bool EnviarDadosCanBus()
    {
        // packet1
        // nivelCombustível = short = 2
        // nivelAtualFreio = int = 2
        // pressaoAtualFreio = double = 4

        // packet2
        // pedalAcel = double = 4
        // tensaoBat = double = 4

        // packet3
        // tempObj = float = 4
        // tempAmb = float = 4

        // packet4
        // rpm = double = 4
        // vel = double = 4

        // TODO: Revisar funcionamento e nome do metodo
        comunicacao.sendCanDataTo(dados.getStructDados());
        return false;
    }

    /**
     * @param debugMode if true waits for Serial USB Port comm. Hangs the program indefinitely.
     * @param callSetup if true calls default initialization function. Defaults to true.
     */

private:
    static Instancia *instance;
    byte data[5]; // Dados transmitidos entre dispositivos.

    Comunicacao comunicacao;
    CartaoSD cartaoSD;
    TemperaturaCVT temperaturaCvt;
    Combustivel nivelCombustivel;
    RPM_Motor rpm;
    GPS gps;
    Freio freio;
    Velocidade velocidade;
    DadosSincronizados dados;
};
Instancia *Instancia::instance{nullptr};
// Dados Instancia::dados{
//     velocidade : 0.0,
//     tempCvt : 0.0,
//     rpm : 0.0
// };

Instancia *Instancia::GetInstance(bool debugMode, bool callSetup)
{
    if (instance == nullptr)
    {
        Serial.println("Criando nova instancia");

        instance = new Instancia();
        instance->dados = *(new DadosSincronizados());

        int i = 0;
        while (i < 3)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(75);
            digitalWrite(LED_BUILTIN, LOW);
            delay(75);
            i++;
        }
        digitalWrite(LED_BUILTIN, HIGH);

        if (debugMode)
        {
            digitalWrite(LED_BUILTIN, LOW);
            Serial.println("Iniciando em Debug Mode");
            Serial.println("Piscando led");
            int i = 0;
            while (i < 3)
            {
                digitalWrite(LED_BUILTIN, HIGH);
                delay(75);
                digitalWrite(LED_BUILTIN, LOW);
                delay(75);
                i++;
            }
            Serial.println("Mantendo led aceso");
            digitalWrite(LED_BUILTIN, HIGH);
        }

        if (callSetup)
        {
            Serial.println("Chamando Setup");

            instance->gps = *GPS::GetInstance();
            Serial.println("Setup GPS concluido");

            instance->comunicacao = *Comunicacao::GetInstance();
            Serial.println("Setup comunicacao concluido");

            instance->temperaturaCvt = *TemperaturaCVT::GetInstance();
            Serial.println("Setup temperaturaCvt concluido");

            instance->rpm = *RPM_Motor::GetInstance();
            Serial.println("Setup rpm concluido");

            instance->nivelCombustivel = *Combustivel::GetInstance();
            Serial.println("Setup nivelCombustivel concluido");

            instance->freio = *Freio::GetInstance();
            Serial.println("Setup freio concluido");

            instance->velocidade = *Velocidade::GetInstance();
            Serial.println("Setup velocidade concluido");

            instance->cartaoSD = *CartaoSD::GetInstance();
            Serial.println("Setup cartaoSD concluido");

            Serial.println("Setup concluido");
        }
        else
        {
            Serial.println("Setup não será chamado.");
        }
    }
    return instance;
}

typedef class Instancia Instancia;

#endif //_INSTANCIA_H