/**
 * Project Classes Placa Central
 */

#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include "Setupable.h"
#include "Constantes.h"
#include <CAN.h>
#include <Arduino.h>
#include <SPI.h>

class Comunicacao : public Setupable
{
public:
    static Comunicacao instance;

    Comunicacao *Setup()
    {
        instance = *new Comunicacao();

        setupTelemetria();
        return &instance;
    }

    bool Loop()
    {
        return false;
    }

    bool Debug()
    {
        return false;
    }

    bool setupTelemetria()
    {

        Serial1.setRX(TELEMETRIA_RX);
        Serial1.setTX(TELEMETRIA_TX);
        Serial1.setFIFOSize(128);
        Serial1.begin(9600);

        return false;
    }

    /**
     * CAN-BUS by Sandeep Mistry
     * https://github.com/sandeepmistry/arduino-CAN/blob/master/API.md
     */
    bool setupCanBus()
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

    void enviarDadosTelemetria(String data)
    {

        Serial1.println(data);
    }

    void updateData()
    {
        return;
    }

    /**
     * @param int CAN Id that should receive the message
     * @param byte* Pointer to buffer with data
     * @param int buffer size
     * @return int - Number of bytes written
     */
    void sendCanDataTo(int receiverId, byte buffer[], int length)
    {
        CAN.write(buffer, length);

        int dlc, rtr;
        CAN.beginPacket(receiverId, dlc, rtr);

        return;
    }

private:
};

#endif //_COMUNICACAO_H