/**
 * Project Classes Placa Central
 */

#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include "Setupable.h"
#include "Constantes.h"
#include "../libs/acan2515-2.1.4/src/ACAN2515.h"
#include <Arduino.h>
#include <SPI.h>

ACAN2515 can(CAN_CSPIN, SPI, 255);

class Comunicacao
{
public:
    static Comunicacao *instance;
    static Comunicacao *Setup();

    static Comunicacao *GetInstance();

    // static const byte MCP2515_CS  = 10 ; // CS input of MCP2515 (adapt to your design)
    // static const uint32_t QUARTZ_FREQUENCY = 16UL * 1000UL * 1000UL ; // 16 MHz

    // ACAN2515 can (CAN_CSPIN, SPI, 255) ;

    bool Loop()
    {
        return false;
    }

    bool Debug()
    {
        return false;
    }

    void enviarDadosTelemetria(String data)
    {

        Serial1.println(data);
    }

    void updateData()
    {
        return;
    }

    // Apagar se o código morrer
    //
    // void receberDados(short nivelComb, int nivelFreio, double pressaoFreio, double pedal, double tensaoBat, float tmpCvt, float tmpAmb, double rpm, double vel)
    // {
    //     nivelComb = nivelComb;
    //     nivelFreio = nivelFreio;
    //     pressaoFreio = pressaoFreio;
    //     pedal = pedal;
    //     tensaoBat = tensaoBat;
    //     tmpCvt = tmpCvt;
    //     tmpAmb = tmpAmb;
    //     rpm = rpm;
    //     vel = vel;
    // }

    unsigned char pickDoubleByte(double d, int index)
    {
        unsigned char *p = (unsigned char *)&d;

        unsigned char byteArr[4];

        for (int i = 0; i != sizeof(double); ++i)
        {
            byteArr[i] = p[i];
        }

        return byteArr[index];
    }

    unsigned char pickFloatByte(float d, int index)
    {
        unsigned char *p = (unsigned char *)&d;

        unsigned char byteArr[4];

        for (int i = 0; i != sizeof(float); ++i)
        {
            byteArr[i] = p[i];
        }

        return byteArr[index];
    }

    /**
     * @param DadosCompartilhamento struct com todos os dados
     * @param int CAN Id that should receive the message
     * @param byte* Pointer to buffer with data
     * @param int buffer size
     * @return int - Number of bytes written
     *
     * REVISAR
     */
    void sendCanDataTo(DadosCompartilhamento data)
    {
        // packet0
        // nivelCombustível = short = 2
        // nivelAtualFreio = int = 2
        // pressaoAtualFreio = double = 4
        byte packet0[8];
        CANMessage frame0;
        frame0.ext = true;
        frame0.id = 0x1FFFFFFF;
        frame0.len = 8;
        const bool ok0 = can.tryToSend(frame0);
        if (!ok0)
        {
            Serial.println("CAN Send failure 0");
        }
        
        
        frame0.data[0] = highByte(data.nivelComb);
        frame0.data[1] = lowByte(data.nivelComb);
        frame0.data[2] = highByte(data.nivelFreio);
        frame0.data[3] = lowByte(data.nivelFreio);
        frame0.data[4] = pickDoubleByte(data.pressaoFreio, 3);
        frame0.data[5] = pickDoubleByte(data.pressaoFreio, 2);
        frame0.data[6] = pickDoubleByte(data.pressaoFreio, 1);
        frame0.data[7] = pickDoubleByte(data.pressaoFreio, 0);

        // packet1
        // pedalAcel = double = 4
        // tensaoBat = double = 4
        CANMessage frame1;
        frame1.ext = true;
        frame1.id = 0x11FFFFFF;
        frame1.len = 8;
        const bool ok1 = can.tryToSend(frame1);
        if (!ok1)
        {
            Serial.println("CAN Send failure 1");
        }
        
        frame1.data[0] = pickDoubleByte(data.pedal, 0);
        frame1.data[1] = pickDoubleByte(data.pedal, 1);
        frame1.data[2] = pickDoubleByte(data.pedal, 2);
        frame1.data[3] = pickDoubleByte(data.pedal, 3);
        frame1.data[4] = pickDoubleByte(data.tensaoBat, 0);
        frame1.data[5] = pickDoubleByte(data.tensaoBat, 1);
        frame1.data[6] = pickDoubleByte(data.tensaoBat, 2);
        frame1.data[7] = pickDoubleByte(data.tensaoBat, 3);

        // packet2
        // tempObj = float = 4
        // tempAmb = float = 4

        CANMessage frame2;
        frame2.ext = true;
        frame2.id = 0x111FFFFF;
        frame2.len = 8;
        const bool ok2 = can.tryToSend(frame2);
        if (!ok2)
        {
            Serial.println("CAN Send failure 2");
        }

        frame2.data[0] = pickFloatByte(data.tmpCvt, 3);
        frame2.data[1] = pickFloatByte(data.tmpCvt, 2);
        frame2.data[2] = pickFloatByte(data.tmpCvt, 1);
        frame2.data[3] = pickFloatByte(data.tmpCvt, 0);
        frame2.data[4] = pickFloatByte(data.tmpAmb, 3);
        frame2.data[5] = pickFloatByte(data.tmpAmb, 2);
        frame2.data[6] = pickFloatByte(data.tmpAmb, 1);
        frame2.data[7] = pickFloatByte(data.tmpAmb, 0);

        // packet3
        // rpm = double = 4
        // vel = double = 4

        CANMessage frame3;
        frame3.ext = true;
        frame3.id = 0x1111FFFF;
        frame3.len = 8;
        const bool ok3 = can.tryToSend(frame3);
        if (!ok3)
        {
            Serial.println("CAN Send failure 3");
        }

        frame3.data[0] = pickDoubleByte(data.rpm, 0);
        frame3.data[1] = pickDoubleByte(data.rpm, 1);
        frame3.data[2] = pickDoubleByte(data.rpm, 2);
        frame3.data[3] = pickDoubleByte(data.rpm, 3);
        frame3.data[4] = pickDoubleByte(data.vel, 0);
        frame3.data[5] = pickDoubleByte(data.vel, 1);
        frame3.data[6] = pickDoubleByte(data.vel, 2);
        frame3.data[7] = pickDoubleByte(data.vel, 3);

        return;
    }

public:
    Comunicacao() = default;

private:
    // static Comunicacao *instance;

    // short nivelComb;
    // int nivelFreio;
    // double pressaoFreio;
    // double pedal;
    // double tensaoBat;
    // float tmpCvt;
    // float tmpAmb;
    // double rpm;
    // double vel;

    static bool setupTelemetria()
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
    static bool setupCanBus()
    {
        SPI.setSCK(CAN_SCKPIN);
        SPI.setRX(CAN_RXPIN);
        SPI.setTX(CAN_TXPIN);
        // CAN.setPins(CAN_CSPIN);


        ACAN2515Settings settings(20UL * 1000UL * 1000UL, 125UL * 1000UL); // CAN bit rate 125 kb/s
        settings.mRequestedMode = ACAN2515Settings::NormalMode;      // Select loopback mode
        const uint16_t errorCode = can.begin(settings, []
                                             { can.isr(); });
        if (errorCode == 0)
        {
            Serial.print("CAN init sucess");
        }
        else
        {
            Serial.print("CAN Configuration error 0x");
            Serial.println(errorCode, HEX);
        }

        return true;
        // CAN.setPins(CAN_CSPIN);

        // ACAN2515Settings settings(QUARTZ_FREQUENCY, 125UL * 1000UL); // CAN bit rate 125 kb/s
        // settings.mRequestedMode = ACAN2515Settings::NormalMode;      // Select loopback mode
        // const uint16_t errorCode = can.begin(settings, []
        //                                      { can.isr(); });
        // if (errorCode == 0)
        // {
        //     Serial.print("CAN init sucess");
        // }
        // else
        // {
        //     Serial.print("CAN Configuration error 0x");
        //     Serial.println(errorCode, HEX);
        // }
    }
};

Comunicacao *Comunicacao::instance{nullptr};
Comunicacao *Comunicacao::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Comunicacao();

        // TODO:
        // setupTelemetria();
        // setupCanBus();
    }

    return instance;
}

#endif //_COMUNICACAO_H