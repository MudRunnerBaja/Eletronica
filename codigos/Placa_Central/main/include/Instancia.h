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

class Instancia
{
public:
    Comunicacao comunicacao;
    CartaoSD cartaoSD;
    TemperaturaCVT temperaturaCvt;
    Combustivel nivelCombustivel;
    RPM_Motor rpm;
    GPS gps;
    Freio freio;
    Velocidade velocidade;
    bool *estadoSistemas;
    bool *testeSistemas;

    static Instancia *instance;

    // Esse é o principal caso de exemplo para Singletons.
    // https://refactoring.guru/pt-br/design-patterns/singleton/cpp/example#example-1

    /**
     * Singletons não devem ser clonáveis.
     */
    Instancia(Instancia &outro) = delete;

    /**
     * NESTE PROJETO IREMOS PERMITIR QUE OUTRAS CLASSES REFERENCIEM SINGLETONS.
     * instancia = Instancia.instance;
     *
     * Isso é um ponto de falha e requer atenção do desenvolvedor quando usado.
     * O ideal é usar um método para referenciar a instância quando necessário, como
     * Instancia.GetInstance() */
    // void operator=(const Instancia &) = delete;

    /**
     * É o método que controla acesso ao singleton.
     * Se a instância nunca foi gerada, gera uma instância
     * com os parâmetros (false, false).
     */
    static Instancia *GetInstance();

    /**
     * Use este método para controlar a geracao do singleton.
     * Apenas a primeira vez irá gerar uma instância, enquanto
     * as demais retornam a instância gerada.
     * @param debugMode if true waits for Serial USB Port comm. Hangs the program indefinitely.
     * @param callSetup if true calls default initialization function. Defaults to true.
     */
    static Instancia *GerarInstancia(bool debugMode, bool callSetup);

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

    void Setup()
    {
        gps.Setup();
        comunicacao.Setup();
        temperaturaCvt.Setup();
        rpm.Setup();
        nivelCombustivel.Setup();
        freio.Setup();
        velocidade.Setup();
        cartaoSD.Setup();
    }

    /**
     * @param debugMode if true waits for Serial USB Port comm. Hangs the program indefinitely.
     * @param callSetup if true calls default initialization function. Defaults to true.
     */
    Instancia(bool debugMode, bool callSetup)
    {
        /**
         * This is a safer way to create an instance. instance = new Singleton is
         * dangerous in case two instance threads wants to access at the same time
         */
        if (instance == nullptr)
        {
            instance = this;

            // Aguardando comunicação Serial
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

            gps = GPS();
            comunicacao = Comunicacao();
            temperaturaCvt = TemperaturaCVT();
            rpm = RPM_Motor();
            nivelCombustivel = Combustivel();
            freio = Freio();
            velocidade = Velocidade();
            cartaoSD = CartaoSD();

            if (callSetup)
            {
                Setup();
            }
        }
    }

private:
    byte data[5]; // Dados transmitidos entre dispositivos.
};

/**
 * Implementações de variáveis e métodos estáticos.
 * Especialmente importante que sejam feitos fora da função
 * para o compilador do Arduino
 */

Instancia *Instancia::instance{nullptr};

Instancia *Instancia::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Instancia(false, false);
    }
    return instance;
}

Instancia *Instancia::GerarInstancia(bool debugMode, bool callSetup)
{
    if (instance == nullptr)
    {
        instance = new Instancia(debugMode, callSetup);
    }
    return instance;
}

#endif //_INSTANCIA_H