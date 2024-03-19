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
bool Comunicacao::Setup()
{
    setupTelemetria();
    return false;
}

bool Comunicacao::setupTelemetria()
{

    Serial1.setRX(TELEMETRIA_RX);
    Serial1.setTX(TELEMETRIA_TX);
    Serial1.setFIFOSize(128);
    Serial1.begin(9600);

    return false;
}

void Comunicacao::enviarDadosTelemetria(String data)
{

    Serial1.println(data);
}

bool Comunicacao::setupCanBus()
{

    SPI.setSCK(CAN_SCKPIN);
    SPI.setRX(CAN_RXPIN);
    SPI.setTX(CAN_TXPIN);
    CAN.setPins(CAN_CSPIN);

    if (!CAN.begin(500E3))
    {
        Serial.println("Starting CAN failed!");
        return false;
    }
    return true;
}

/**
 * @return void
 */
void Comunicacao::updateData()
{
    return;
}

/**
 * @param int CAN Id that should receive the message
 * @param byte* Pointer to buffer with data
 * @param int buffer size
 * @return int - Number of bytes written
 */
void Comunicacao::sendCanDataTo(int receiverId, byte buffer[], int length)
{
    CAN.write(buffer, length);

    int id, dlc, rtr;
    CAN.beginPacket(id, dlc, rtr);

    return;
}

bool Comunicacao::Loop()
{
    return false;
}

bool Comunicacao::TestChosen(int escolhido)
{
    return false;
}