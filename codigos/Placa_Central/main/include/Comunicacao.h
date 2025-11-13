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
#include "LoRa_E32.h"

ACAN2515 can(CAN_CSPIN, SPI, CAN_INPIN);

SoftwareSerial serialTelemetria(TELEMETRIA_RX, TELEMETRIA_TX); // RX, TX
LoRa_E32 e32ttl100(&serialTelemetria);                         

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

    void enviarDadosTelemetria(DadosCompartilhamento data)
    {
        DadosCompartilhamento d = data;
        ResponseStatus rs = e32ttl100.sendFixedMessage(0, 3, 0x04, &d, sizeof(DadosCompartilhamento));
    }

    void enviarDadosTelemetria(double data){
        double d = data;
        ResponseStatus rs = e32ttl100.sendFixedMessage(0, 3, 0x04, &d, sizeof(double));
    }

    void enviarDadosTelemetria(DadosLight data){
        DadosLight d = data;
        ResponseStatus rs = e32ttl100.sendFixedMessage(0, 3, 0x04, &d, sizeof(DadosLight));
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

    uint8_t pickDoubleByte(double D, int index)
    {
        double d = D;
        uint8_t b[sizeof(d)];
        memcpy(&b, &d, sizeof(b));

        return b[index];
    }

    uint8_t pickIntByte(int D, int index)
    {
        int d = D;
        uint8_t b[sizeof(d)];
        memcpy(&b, &d, sizeof(b));

        return b[index];
    }

    uint8_t pickFloatByte(float D, int index)
    {
        float d = D;
        uint8_t b[sizeof(d)];
        memcpy(&b, &d, sizeof(b));

        return b[index];
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
        //dados
        //vel
        //
        CANMessage receive;
        can.poll();
        can.receive(receive);
        Serial.println(receive.id);

        // packet0
        // vel
        CANMessage frame0;
        frame0.ext = false;
        frame0.rtr = false;
        frame0.id = 1;
        frame0.len = 8;

        frame0.data[0] = pickDoubleByte(data.vel, 0);
        frame0.data[1] = pickDoubleByte(data.vel, 1);
        frame0.data[2] = pickDoubleByte(data.vel, 2);
        frame0.data[3] = pickDoubleByte(data.vel, 3);
        frame0.data[4] = pickDoubleByte(data.vel, 4);
        frame0.data[5] = pickDoubleByte(data.vel, 5);
        frame0.data[6] = pickDoubleByte(data.vel, 6);
        frame0.data[7] = pickDoubleByte(data.vel, 7);

        const bool ok0 = can.tryToSend(frame0);
        // if (!ok0)
        // {
        //     Serial.println("CAN Send failure 0");
        // }

        // packet1
        // tensaoBat = double = 4
        CANMessage frame1;
        frame1.ext = false;
        frame1.rtr = false;
        frame1.id = 2;
        frame1.len = 8;
        frame1.idx = 1;

        // frame1.data[0] = 10;
        frame1.data[0] = pickDoubleByte(data.tensaoBat, 0);
        frame1.data[1] = pickDoubleByte(data.tensaoBat, 1);
        frame1.data[2] = pickDoubleByte(data.tensaoBat, 2);
        frame1.data[3] = pickDoubleByte(data.tensaoBat, 3);
        frame1.data[4] = pickDoubleByte(data.tensaoBat, 4);
        frame1.data[5] = pickDoubleByte(data.tensaoBat, 5);
        frame1.data[6] = pickDoubleByte(data.tensaoBat, 6);
        frame1.data[7] = pickDoubleByte(data.tensaoBat, 7);

        const bool ok1 = can.tryToSend(frame1);
        // if (!ok1)
        // {
        //     // Serial.println("CAN Send failure 1");
        // }

        // packet2
        // tempObj = float = 4
        // tempAmb = float = 4

        CANMessage frame2;
        frame2.ext = false;
        frame2.rtr = false;
        frame2.id = 3;
        frame2.len = 8;
        frame2.idx = 2;

        frame2.data[0] = pickFloatByte(data.tmpCvt, 3);
        frame2.data[1] = pickFloatByte(data.tmpCvt, 2);
        frame2.data[2] = pickFloatByte(data.tmpCvt, 1);
        frame2.data[3] = pickFloatByte(data.tmpCvt, 0);
        frame2.data[4] = pickFloatByte(data.tmpAmb, 3);
        frame2.data[5] = pickFloatByte(data.tmpAmb, 2);
        frame2.data[6] = pickFloatByte(data.tmpAmb, 1);
        frame2.data[7] = pickFloatByte(data.tmpAmb, 0);

        const bool ok2 = can.tryToSend(frame2);
        // if (!ok2)
        // {
        //     // Serial.println("CAN Send failure 2");
        // }
        // packet3
        // rpm = double = 4

        CANMessage frame3;
        frame3.ext = false;
        frame3.rtr = false;
        frame3.id = 4;
        frame3.len = 8;

        frame3.data[0] = pickDoubleByte(data.rpm, 0);
        frame3.data[1] = pickDoubleByte(data.rpm, 1);
        frame3.data[2] = pickDoubleByte(data.rpm, 2);
        frame3.data[3] = pickDoubleByte(data.rpm, 3);
        frame3.data[4] = pickDoubleByte(data.rpm, 4);
        frame3.data[5] = pickDoubleByte(data.rpm, 5);
        frame3.data[6] = pickDoubleByte(data.rpm, 6);
        frame3.data[7] = pickDoubleByte(data.rpm, 7);
        const bool ok3 = can.tryToSend(frame3);
        // if (!ok3)
        // {
        //     // Serial.println("CAN Send failure 3");
        // }

        //packet4
        //nivelDeFreio
        CANMessage frame4;
        frame1.ext = false;
        frame1.rtr = false;
        frame1.id = 5;
        frame1.len = 8;
        frame1.idx = 1;

        frame4.data[0] = pickIntByte(data.nivelFreio, 0);
        frame4.data[1] = pickIntByte(data.nivelFreio, 1);
        frame4.data[2] = pickIntByte(data.nivelFreio, 2);
        frame4.data[3] = pickIntByte(data.nivelFreio, 3);

        // Serial.print("Buffer 0: " );
        // Serial.println(can.transmitBufferCount(0));
        // Serial.print("Buffer 1: " );
        // Serial.println(can.transmitBufferCount(1));
        // Serial.print("Buffer 2: " );
        // Serial.println(can.transmitBufferCount(2));

        for (int i = 0; i < 8; i++)
        {
            Serial.print(frame0.data[i]);
            Serial.print(", ");
        }
        Serial.println("");

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
        e32ttl100.begin();
        ResponseStructContainer c;
        c = e32ttl100.getConfiguration();
        Serial.println(c.status.getResponseDescription());
        Serial.println(c.status.code);
        Configuration configuration = *(Configuration *)c.data;
        configuration.ADDL = 0x01;
        configuration.ADDH = 0x00;
        configuration.CHAN = 0x02;
        configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
        // e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
        c.close();

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
        SPI.setCS(CAN_CSPIN);
        SPI.begin();
        // CAN.setPins(CAN_CSPIN);

        ACAN2515Settings settings(20UL * 1000UL * 1000UL, 125UL * 1000UL); // CAN bit rate 125 kb/s
        settings.mRequestedMode = ACAN2515Settings::NormalMode;            // Select loopback mode
        const uint16_t errorCode = can.begin(settings, []
                                             { can.isr(); });
        if (errorCode == 0)
        {
            Serial.print("CAN init success");
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
        setupTelemetria();
        setupCanBus();
    }

    return instance;
}

#endif //_COMUNICACAO_H