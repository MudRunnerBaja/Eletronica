/**
 * Project Classes Placa Central
 */


#include "Comunicacao.h"

/**
 * Comunicacao implementation
 */


/**
 * @return bool
 */
bool Comunicacao::Setup() {
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

    int cspin, irq, bitrate, spiFrequency;

    CAN.setSPIFrequency(spiFrequency);
    CAN.setPins(cspin, irq);
    CAN.begin(bitrate);

    return false;
}

/**
 * @return void
 */
void Comunicacao::updateData() {
    return;
}

/**
 * @param int CAN Id that should receive the message
 * @param byte* Pointer to buffer with data 
 * @param int buffer size
 * @return int - Number of bytes written
 */
void Comunicacao::sendCanDataTo(int receiverId, byte buffer[], int length) {
    CAN.write(buffer, length);

    int id, dlc, rtr;
    CAN.beginPacket(id, dlc, rtr);

    return;
}

bool Comunicacao::Test() {
    return false;
}

bool Comunicacao::TestChosen(int escolhido) {
    return false;
}