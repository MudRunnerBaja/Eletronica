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
    static Comunicacao *instance;
    static Comunicacao *Setup();

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

    void receberDados(short nivelComb, int nivelFreio, double pressaoFreio){
        nivelComb = nivelComb;
        nivelFreio = nivelFreio;
        pressaoFreio = pressaoFreio;
    }

    unsigned char pickDoubleByte(double d, int index){
        unsigned char *p = (unsigned char *)&d;

        unsigned char byteArr[4];

        for (int i = 0; i != sizeof(double); ++i){
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
     * @param int CAN Id that should receive the message
     * @param byte* Pointer to buffer with data
     * @param int buffer size
     * @return int - Number of bytes written
     */
    void sendCanDataTo(int receiverId, byte buffer[], int length)
    {
        //packet1
        //nivelCombustível = short = 2
        //nivelAtualFreio = int = 2
        //pressaoAtualFreio = double = 4

        //packet2
        //pedalAcel = double = 4
        //tensaoBat = double = 4

        //packet3
        //tempObj = float = 4
        //tempAmb = float = 4

        //packet4
        //rpm = double = 4
        //vel = double = 4

        byte packet0[8];

        packet0[1] = lowByte(nivelComb);
        packet0[0] = highByte(nivelComb);
        packet0[3] = lowByte(nivelFreio);
        packet0[2] = highByte(nivelFreio);
        packet0[4] = pickDoubleByte(pressaoFreio, 3);
        packet0[5] = pickDoubleByte(pressaoFreio, 2);
        packet0[6] = pickDoubleByte(pressaoFreio, 1);
        packet0[7] = pickDoubleByte(pressaoFreio, 0);

        byte packet1[8];

        packet1[0] = pickDoubleByte(pedal, 3);
        packet1[1] = pickDoubleByte(pedal, 2);
        packet1[2] = pickDoubleByte(pedal, 1);
        packet1[3] = pickDoubleByte(pedal, 0);
        packet1[4] = pickDoubleByte(tensaoBat, 3);
        packet1[5] = pickDoubleByte(tensaoBat, 2);
        packet1[6] = pickDoubleByte(tensaoBat, 1);
        packet1[7] = pickDoubleByte(tensaoBat, 0);

        byte packet2[8];

        packet2[0] = pickFloatByte(tmpCvt, 3);
        packet2[1] = pickFloatByte(tmpCvt, 2);
        packet2[2] = pickFloatByte(tmpCvt, 1);
        packet2[3] = pickFloatByte(tmpCvt, 0);
        packet2[4] = pickFloatByte(tmpAmb, 3);
        packet2[5] = pickFloatByte(tmpAmb, 2);
        packet2[6] = pickFloatByte(tmpAmb, 1);
        packet2[7] = pickFloatByte(tmpAmb, 0);

        byte packet3[8];

        packet3[0] = pickDoubleByte(rpm, 3);
        packet3[1] = pickDoubleByte(rpm, 2);
        packet3[2] = pickDoubleByte(rpm, 1);
        packet3[3] = pickDoubleByte(rpm, 0);
        packet3[4] = pickDoubleByte(vel, 3);
        packet3[5] = pickDoubleByte(vel, 2);
        packet3[6] = pickDoubleByte(vel, 1);
        packet3[7] = pickDoubleByte(vel, 0);

        CAN.beginPacket(0x12, length);
        for (int i = 0; i <= 7; i++){
            CAN.write(packet0[i]);
        }
        CAN.endPacket();

        CAN.beginPacket(0x13, length);
        for (int i = 0; i <= 7; i++)
        {
            CAN.write(packet1[i]);
        }
        CAN.endPacket();

        CAN.beginPacket(0x14, length);
        for (int i = 0; i <= 7; i++)
        {
            CAN.write(packet2[i]);
        }
        CAN.endPacket();

        CAN.beginPacket(0x15, length);
        for (int i = 0; i <= 7; i++)
        {
            CAN.write(packet3[i]);
        }
        CAN.endPacket();

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
    short nivelComb;
    int nivelFreio;
    double pressaoFreio;
    double pedal;
    double tensaoBat;
    float tmpCvt;
    float tmpAmb;
    double rpm;
    double vel;

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
        CAN.setPins(CAN_CSPIN);

        if (!CAN.begin(500E3))
        {
            Serial.println("Starting CAN failed!");
            return false;
        }
        return true;
    }
};

Comunicacao *Comunicacao::instance{nullptr};
Comunicacao *Comunicacao::Setup()
{
    if (instance == NULL)
    {
        instance = new Comunicacao();
    }

    // setupTelemetria();
    // setupCanBus();

    return instance;
}

#endif //_COMUNICACAO_H