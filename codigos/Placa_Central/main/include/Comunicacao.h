/**
 * Project Classes Placa Central
 */

#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

#include "Setupable.h"
#include "Constantes.h"
#include "libs/acan2515-2.1.4/src/ACAN2515.h"
#include <Arduino.h>
#include <SPI.h>

class Comunicacao : public Setupable
{
public:
    static Comunicacao *instance;
    static Comunicacao *Setup();

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
     * @param StructDados struct com todos os dados
     * @param int CAN Id that should receive the message
     * @param byte* Pointer to buffer with data
     * @param int buffer size
     * @return int - Number of bytes written
     *
     * REVISAR
     */
    void sendCanDataTo(StructDados data)
    {
        // packet0
        // nivelCombustível = short = 2
        // nivelAtualFreio = int = 2
        // pressaoAtualFreio = double = 4
        byte packet0[8];

        packet0[1] = lowByte(data.nivelComb);
        packet0[0] = highByte(data.nivelComb);
        packet0[3] = lowByte(data.nivelFreio);
        packet0[2] = highByte(data.nivelFreio);
        packet0[4] = pickDoubleByte(data.pressaoFreio, 3);
        packet0[5] = pickDoubleByte(data.pressaoFreio, 2);
        packet0[6] = pickDoubleByte(data.pressaoFreio, 1);
        packet0[7] = pickDoubleByte(data.pressaoFreio, 0);

        // packet1
        // pedalAcel = double = 4
        // tensaoBat = double = 4
        byte packet1[8];

        packet1[0] = pickDoubleByte(data.pedal, 3);
        packet1[1] = pickDoubleByte(data.pedal, 2);
        packet1[2] = pickDoubleByte(data.pedal, 1);
        packet1[3] = pickDoubleByte(data.pedal, 0);
        packet1[4] = pickDoubleByte(data.tensaoBat, 3);
        packet1[5] = pickDoubleByte(data.tensaoBat, 2);
        packet1[6] = pickDoubleByte(data.tensaoBat, 1);
        packet1[7] = pickDoubleByte(data.tensaoBat, 0);

        // packet2
        // tempObj = float = 4
        // tempAmb = float = 4
        byte packet2[8];

        packet2[0] = pickFloatByte(data.tmpCvt, 3);
        packet2[1] = pickFloatByte(data.tmpCvt, 2);
        packet2[2] = pickFloatByte(data.tmpCvt, 1);
        packet2[3] = pickFloatByte(data.tmpCvt, 0);
        packet2[4] = pickFloatByte(data.tmpAmb, 3);
        packet2[5] = pickFloatByte(data.tmpAmb, 2);
        packet2[6] = pickFloatByte(data.tmpAmb, 1);
        packet2[7] = pickFloatByte(data.tmpAmb, 0);

        // packet3
        // rpm = double = 4
        // vel = double = 4
        byte packet3[8];

        packet3[0] = pickDoubleByte(data.rpm, 3);
        packet3[1] = pickDoubleByte(data.rpm, 2);
        packet3[2] = pickDoubleByte(data.rpm, 1);
        packet3[3] = pickDoubleByte(data.rpm, 0);
        packet3[4] = pickDoubleByte(data.vel, 3);
        packet3[5] = pickDoubleByte(data.vel, 2);
        packet3[6] = pickDoubleByte(data.vel, 1);
        packet3[7] = pickDoubleByte(data.vel, 0);

        // CANMessage frame0;
        // frame0.ext = true;
        // frame0.id = 0x1FFFFFFF;
        // frame0.len = 8;
        // frame0.data = packet0;
        // const bool ok0 = can.tryToSend(frame0);
        // if (!ok0)
        // {
        //     Serial.println("CAN Send failure 0");
        // }

        // CANMessage frame1;
        // frame1.ext = true;
        // frame1.id = 0x11FFFFFF;
        // frame1.len = 8;
        // frame1.data = packet1;
        // const bool ok1 = can.tryToSend(frame1);
        // if (!ok1)
        // {
        //     Serial.println("CAN Send failure 1");
        // }

        // CANMessage frame2;
        // frame2.ext = true;
        // frame2.id = 0x111FFFFF;
        // frame2.len = 8;
        // frame2.data = packet2;
        // const bool ok2 = can.tryToSend(frame2);
        // if (!ok2)
        // {
        //     Serial.println("CAN Send failure 2");
        // }

        // CANMessage frame3;
        // frame3.ext = true;
        // frame3.id = 0x1111FFFF;
        // frame3.len = 8;
        // frame3.data = packet3;
        // const bool ok3 = can.tryToSend(frame3);
        // if (!ok3)
        // {
        //     Serial.println("CAN Send failure 3");
        // }

        // CAN.beginPacket(0x12, 8);
        // for (int i = 0; i <= 7; i++)
        // {
        //     CAN.write(packet0[i]);
        // }
        // CAN.endPacket();

        // CAN.beginPacket(0x13, 8);
        // for (int i = 0; i <= 7; i++)
        // {
        //     CAN.write(packet1[i]);
        // }
        // CAN.endPacket();

        // CAN.beginPacket(0x14, 8);
        // for (int i = 0; i <= 7; i++)
        // {
        //     CAN.write(packet2[i]);
        // }
        // CAN.endPacket();

        // CAN.beginPacket(0x15, 8);
        // for (int i = 0; i <= 7; i++)
        // {
        //     CAN.write(packet3[i]);
        // }
        // CAN.endPacket();

        // int dlc, rtr;
        // CAN.beginPacket(receiverId, dlc, rtr);

        return;
    }

    Comunicacao(Comunicacao &outro) = delete;

    Comunicacao()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
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
Comunicacao *Comunicacao::Setup()
{
    if (instance == NULL)
    {
        instance = new Comunicacao();
    }

    // TODO:
    // setupTelemetria();
    // setupCanBus();

    return instance;
}

#endif //_COMUNICACAO_H