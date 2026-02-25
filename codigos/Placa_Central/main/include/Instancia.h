/**
 * Project Classes Placa Central
 */

#ifndef _INSTANCIA_H
#define _INSTANCIA_H

#include <Arduino.h>
#include "Setupable.h"
#include "Comunicacao.h"
#include "CartaoSD.h"
#include "TensaoBateria.h"
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
    static Instancia *GetInstance();

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

    void EscreverSD()
    {
        // while (dados.getDadosEmAtualizacao)
        // {
        //     yield();
        // }

        cartaoSD.escreverSD(dados.formatarDadosSD());
        return;
    }

    void InicializarArquivo(){
        cartaoSD.criarArquivoDados();
    }

    void SetDadosSistemas()
    {
        // rpm.updateRPM();
        nivelCombustivel.setNivelAtual();
        freio.setNivelAtual();
        freio.setPressaoAtual();
        // Pedal Acelerador
        // Tensao Bateria
        // temperaturaCvt.setTemperaturaObjeto();
        // temperaturaCvt.setTemperaturaAmbiente();
        // velocidade.updateVel();
    }

    bool SincronizarDados()
    {
        dados.atualizarDados(
            nivelCombustivel.getNivelAtual(),
            freio.getNivelAtual(),
            freio.getPressaoAtual(),
            0.0, // Pedal Acelerador
            tensaoBat.getTensaoBateria(), // Tensao Bateria
            0, //temperaturaCvt.getTemperaturaObjeto()
            0, //temperaturaCvt.getTemperaturaAmbiente()
            rpm.getRPM(),
            velocidade.getVel(),
            0, //gps.getLatitude()
            0); //gps.getLongitude()
            
        // dados.atualizarDados(0, 1, 2, 500, 4, 5, 6, 7, 200);

        return false;
    }

    void PrintarDados()
    {
        D_println(dados.formatarDados());
    }

    bool EnviarDadosTelemetria()
    {
        // String data = String(rpm.getRPM());
        // data = String(data + ",");
        // data = String(data + temperaturaCvt.getTemperaturaObjeto());
        // data = String(data + ",");
        // data = String(data + gps.getSpeed());
        // data = String(data + ",");
        // data = String(data + nivelCombustivel.getNivelAtual());
        comunicacao.enviarDadosTelemetria(dados.getStructDadosLight());
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
    TensaoBateria tensaoBat;
    Velocidade velocidade;
    DadosSincronizados dados;
};
Instancia *Instancia::instance{nullptr};
Instancia *Instancia::GetInstance()
{
    if (instance == nullptr)
    {
        D_println("Criando nova instancia");

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

        digitalWrite(LED_BUILTIN, LOW);
        D_println("Iniciando em Debug Mode");
        D_println("Piscando led");

        i = 0;
        while (i < 3)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(75);
            digitalWrite(LED_BUILTIN, LOW);
            delay(75);
            i++;
        }

        D_println("Mantendo led aceso");
        digitalWrite(LED_BUILTIN, HIGH);

        D_println("Chamando Setup");

        // instance->gps = *GPS::GetInstance();
        D_println("Setup GPS concluido");

        instance->comunicacao = *Comunicacao::GetInstance();
        D_println("Setup comunicacao concluido");

        // instance->temperaturaCvt = *TemperaturaCVT::GetInstance();
        D_println("Setup temperaturaCvt concluido");

        instance->rpm = *RPM_Motor::GetInstance();
        D_println("Setup rpm concluido");

        instance->nivelCombustivel = *Combustivel::GetInstance();
        D_println("Setup nivelCombustivel concluido");

        instance->freio = *Freio::GetInstance();
        D_println("Setup freio concluido");

        instance->tensaoBat = *TensaoBateria::GetInstance();
        D_println("Setup tensao bateria concluido");

        instance->velocidade = *Velocidade::GetInstance();
        D_println("Setup velocidade concluido");

        // instance->cartaoSD = *CartaoSD::GetInstance();
        D_println("Setup cartaoSD concluido");

        D_println("Setup concluido");
    }
    return instance;
}

typedef class Instancia Instancia;

#endif //_INSTANCIA_H