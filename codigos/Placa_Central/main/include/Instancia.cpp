/**
 * Project Classes Placa Central
 */


#include "Instancia.h"

/**
 * Instancia implementation
 */
Instancia::Instancia() {
    Setup();
    return;
}

/**
 * @return bool
 */
bool Instancia::Setup() {
    bool check = true;

    check = comunicacao.Setup();
    check = gps.Setup();
    check = cartaoSD.Setup();
    check = temperaturaCvt.Setup();
    check = rpm.Setup();

    

    return check;
}

/**
 * @return bool
 */
bool Instancia::EscreverSD() {
    return false;
}

/**
 * @return bool
 */
bool Instancia::AtualizarDados() {
    return false;
}

/**
 * @return bool
 */
bool Instancia::EnviarDadosTelemetria() {

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

bool Instancia::EnviarDadosCanBus() {
    return false;
}

/**
 * @return bool
 */
bool Instancia::Test() {
    return;
}

bool Instancia::TestChosen(int escolhido) {
    return;
}