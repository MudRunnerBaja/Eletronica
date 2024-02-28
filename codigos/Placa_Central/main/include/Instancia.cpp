/**
 * Project Classes Placa Central
 */


#include "Instancia.h"

/**
 * Instancia implementation
 */


/**
 * @return bool
 */
bool Instancia::setup() {
    return false;
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
bool Instancia::test() {
    return;
}

bool Instancia::testChosen(int escolhido) {
    return;
}