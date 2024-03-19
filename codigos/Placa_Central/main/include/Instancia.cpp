/**
 * Project Classes Placa Central
 */

#include "Instancia.h"

/**
 * Instancia implementation
 * @param debugMode if true waits for Serial USB Port comm. Hangs the program indefinitely.
 * @param callSetup if true calls default initialization function. Defaults to true.
 */
Instancia::Instancia(bool debugMode, bool callSetup)
{
    /* Wait for serial */
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
    return;
}

/**
 * @return bool
 */
bool Instancia::Setup()
{
    bool check = false;

    freio.Setup();
    cartaoSD.Setup();
    comunicacao.setupCanBus();
    temperaturaCvt.Setup();
    gps.Setup();

    return check;
}

/**
 * @return bool
 */
bool Instancia::EscreverSD()
{
    return false;
}

/**
 * @return bool
 */
bool Instancia::AtualizarDados()
{
    return false;
}

/**
 * @return bool
 */
bool Instancia::EnviarDadosTelemetria()
{

    String data = String(rpm.getRPM());
    data = String(data + ",");
    data = String(data + temperaturaCvt.getTemperaturaCvt());
    data = String(data + ",");
    data = String(data + gps.getSpeed());
    data = String(data + ",");
    data = String(data + nivelCombustivel.getNivelAtual());

    comunicacao.enviarDadosTelemetria(data);
    return false;
}

bool Instancia::EnviarDadosCanBus()
{
    return false;
}

/**
 * @return bool
 */
bool Instancia::Loop()
{
    return;
}

bool Instancia::TestChosen(int escolhido)
{
    return;
}