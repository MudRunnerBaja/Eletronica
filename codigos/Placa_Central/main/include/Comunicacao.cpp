/**
 * Project Classes Placa Central
 */


#include "Comunicacao.h"
#include "Constantes.h"

/**
 * Comunicacao implementation
 */


/**
 * @return void
 */
bool Comunicacao::setup() {
    setupTelemetria();
    return false;
}

bool Comunicacao::setupTelemetria() {
    
    Serial1.setRX(TELEMETRIA_RX);
    Serial1.setTX(TELEMETRIA_TX);
    Serial1.setFIFOSize(128);
    Serial1.begin(9600);
    
    return false;
}

void Comunicacao::enviarDadosTelemetria(String data) {
    
    Serial1.println(data);
}

bool Comunicacao::setupCanBus() {
    return false;
}

bool Comunicacao::setupI2c() {
    return false;
}

/**
 * @return void
 */
void Comunicacao::updateData() {
    return;
}

/**
 * @param int
 * @return void
 */
void Comunicacao::sendI2cDataTo(int slave) {
    return;
}

bool Comunicacao::test() {
    return false;
}

bool Comunicacao::testChosen(int escolhido) {
    return false;
}

/**
 * @return bool
 */
bool Comunicacao::testTelemetria() {
    return false;
}

/**
 * @return bool
 */
bool Comunicacao::testCanBus() {
    return false;
}

/**
 * @return bool
 */
bool Comunicacao::testI2c() {
    return false;
}