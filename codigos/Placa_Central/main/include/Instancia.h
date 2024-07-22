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

// Incluir todos os dados. Quando atualizar
// cada dado, salvar também nessa struct em
// Instancia

struct _Dados
{
    float velocidade;
    float tempCvt;
    float rpm;
};
typedef struct _Dados Dados;

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
    static Dados dados;

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
        Serial.println("Setup GPS concluido");
        comunicacao.Setup();
        Serial.println("Setup comunicacao concluido");
        temperaturaCvt.Setup();
        Serial.println("Setup temperaturaCvt concluido");
        rpm.Setup();
        Serial.println("Setup rpm concluido");
        nivelCombustivel.Setup();
        Serial.println("Setup nivelCombustivel concluido");
        freio.Setup();
        Serial.println("Setup freio concluido");
        velocidade.Setup();
        Serial.println("Setup velocidade concluido");
        cartaoSD.Setup();
        Serial.println("Setup cartaoSD concluido");
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
            Serial.println("Criando nova instancia");
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
            instance = this;

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

            gps = GPS();
            // Serial.println("Instancia GPS gerada");
            // comunicacao = Comunicacao();
            // Serial.println("Instancia Comunicacao gerada");
            temperaturaCvt = TemperaturaCVT();
            Serial.println("Instancia TemperaturaCVT gerada");
            rpm = RPM_Motor();
            Serial.println("Instancia RPM_Motor gerada");
            nivelCombustivel = Combustivel();
            Serial.println("Instancia Combustivel gerada");
            freio = Freio();
            Serial.println("Instancia Freio gerada");
            velocidade = Velocidade();
            Serial.println("Instancia Velocidade gerada");
            // cartaoSD = CartaoSD();
            Serial.println("Instancia CartaoSD gerada");

            if (callSetup)
            {
                Serial.println("Chamando Setup");
                Setup();
                Serial.println("Setup concluido");
            }
            else
            {
                Serial.println("Setup não será chamado.");
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
Dados Instancia::dados{
    velocidade : 0.0,
    tempCvt : 0.0,
    rpm : 0.0
};

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

typedef class Instancia Instancia;

#endif //_INSTANCIA_H