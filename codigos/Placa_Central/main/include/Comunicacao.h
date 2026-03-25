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
LoRa_E32 e32ttl100(&serialTelemetria, TELEMETRIA_AUX, UART_BPS_RATE_9600);  
static uint16_t errorCode;                       

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
        ResponseStatus rs = e32ttl100.sendFixedMessage(0, 0 , 0x17, &d, sizeof(DadosLight));
        Serial.println(rs.getResponseDescription());
    }

    void updateData()
    {
        return;
    }

    bool getErrorCan(){
        if (errorCode == 0){
            return true;
        }
        
        return false;
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
        frame0.idx = 1;

        // frame0.data64 = data.vel;

        frame0.data[0] = pickDoubleByte(data.vel, 0);
        frame0.data[1] = pickDoubleByte(data.vel, 1);
        frame0.data[2] = pickDoubleByte(data.vel, 2);
        frame0.data[3] = pickDoubleByte(data.vel, 3);
        frame0.data[4] = pickDoubleByte(data.vel, 4);
        frame0.data[5] = pickDoubleByte(data.vel, 5);
        frame0.data[6] = pickDoubleByte(data.vel, 6);
        frame0.data[7] = pickDoubleByte(data.vel, 7);

        const bool ok0 = can.tryToSend(frame0);
        if (!ok0)
        {
            Serial.println("CAN Send failure 0");
        }

        // packet1
        // tensaoBat = double = 4
        CANMessage frame1;
        frame1.ext = false;
        frame1.rtr = false;
        frame1.id = 2;
        frame1.len = 8;
        frame1.idx = 2;

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
        if (!ok1)
        {
            Serial.println("CAN Send failure 1");
        }

        // packet2
        // tempObj = float = 4
        // tempAmb = float = 4

        CANMessage frame2;
        frame2.ext = false;
        frame2.rtr = false;
        frame2.id = 3;
        frame2.len = 8;
        frame2.idx = 1;

        frame2.data[0] = pickFloatByte(data.tmpCvt, 3);
        frame2.data[1] = pickFloatByte(data.tmpCvt, 2);
        frame2.data[2] = pickFloatByte(data.tmpCvt, 1);
        frame2.data[3] = pickFloatByte(data.tmpCvt, 0);
        frame2.data[4] = pickFloatByte(data.tmpAmb, 3);
        frame2.data[5] = pickFloatByte(data.tmpAmb, 2);
        frame2.data[6] = pickFloatByte(data.tmpAmb, 1);
        frame2.data[7] = pickFloatByte(data.tmpAmb, 0);

        

        const bool ok2 = can.tryToSend(frame2);
        if (!ok2)
        {
            Serial.println("CAN Send failure 2");
        }
        // packet3
        // rpm = double = 4

        CANMessage frame3;
        frame3.ext = false;
        frame3.rtr = false;
        frame3.id = 4;
        frame3.len = 8;
        frame3.idx = 0;

        frame3.data[0] = pickDoubleByte(data.rpm, 0);
        frame3.data[1] = pickDoubleByte(data.rpm, 1);
        frame3.data[2] = pickDoubleByte(data.rpm, 2);
        frame3.data[3] = pickDoubleByte(data.rpm, 3);
        frame3.data[4] = pickDoubleByte(data.rpm, 4);
        frame3.data[5] = pickDoubleByte(data.rpm, 5);
        frame3.data[6] = pickDoubleByte(data.rpm, 6);
        frame3.data[7] = pickDoubleByte(data.rpm, 7);
        const bool ok3 = can.tryToSend(frame3);
        if (!ok3)
        {
            Serial.println("CAN Send failure 3");
        }

        //packet4
        //nivelDeFreio
        CANMessage frame4;
        frame4.ext = false;
        frame4.rtr = false;
        frame4.id = 5;
        frame4.len = 4;
        frame4.idx = 0;

        frame4.data[0] = pickIntByte(data.nivelFreio, 0);
        frame4.data[1] = pickIntByte(data.nivelFreio, 1);
        frame4.data[2] = pickIntByte(data.nivelFreio, 2);
        frame4.data[3] = pickIntByte(data.nivelFreio, 3);

        const bool ok4 = can.tryToSend(frame4);


        //packet5
        //latitude
        CANMessage frame5;
        frame5.ext = false;
        frame5.rtr = false;
        frame5.id = 6;
        frame5.len = 8;
        frame5.idx = 0;

        frame5.data[0] = pickIntByte(data.latitude, 0);
        frame5.data[1] = pickIntByte(data.latitude, 1);
        frame5.data[2] = pickIntByte(data.latitude, 2);
        frame5.data[3] = pickIntByte(data.latitude, 3);
        frame5.data[4] = pickIntByte(data.latitude, 4);
        frame5.data[5] = pickIntByte(data.latitude, 5);
        frame5.data[6] = pickIntByte(data.latitude, 6);
        frame5.data[7] = pickIntByte(data.latitude, 7);

        const bool ok5 = can.tryToSend(frame5);
        
        //packet4
        //longitude
        CANMessage frame6;
        frame6.ext = false;
        frame6.rtr = false;
        frame6.id = 7;
        frame6.len = 8;
        frame6.idx = 0;

        frame6.data[0] = pickDoubleByte(data.longitude, 0);
        frame6.data[1] = pickDoubleByte(data.longitude, 1);
        frame6.data[2] = pickDoubleByte(data.longitude, 2);
        frame6.data[3] = pickDoubleByte(data.longitude, 3);
        frame6.data[4] = pickDoubleByte(data.longitude, 4);
        frame6.data[5] = pickDoubleByte(data.longitude, 5);
        frame6.data[6] = pickDoubleByte(data.longitude, 6);
        frame6.data[7] = pickDoubleByte(data.longitude, 7);

        const bool ok6 = can.tryToSend(frame6);

        //packet7
        //sdrw
        //fix_gps
        CANMessage frame7;
        frame7.ext = false;
        frame7.rtr = false;
        frame7.id = 8;
        frame7.len = 8;
        frame7.idx = 1;

        frame7.data[1] = data.sdrw;
        frame7.data[2] = data.fix_gps;

        const bool ok7 = can.tryToSend(frame7);

        //packet8
        //nivelComb
        CANMessage frame8;
        frame8.ext = false;
        frame8.rtr = false;
        frame8.id = 9;
        frame8.len = 8;
        frame8.idx = 2;

        frame8.data[0] = pickIntByte(data.nivelComb, 0);
        frame8.data[1] = pickIntByte(data.nivelComb, 1);
        frame8.data[2] = pickIntByte(data.nivelComb, 2);
        frame8.data[3] = pickIntByte(data.nivelComb, 3);

        // const bool ok8 = can.tryToSend(frame8);

        //packet9
        //pedal
        CANMessage frame9;
        frame9.ext = false;
        frame9.rtr = false;
        frame9.id = 10;
        frame9.len = 8;
        frame9.idx = 2;

        frame9.data[0] = pickIntByte(data.pedal, 0);
        frame9.data[1] = pickIntByte(data.pedal, 1);
        frame9.data[2] = pickIntByte(data.pedal, 2);
        frame9.data[3] = pickIntByte(data.pedal, 3);
        frame9.data[4] = pickIntByte(data.pedal, 4);
        frame9.data[5] = pickIntByte(data.pedal, 5);
        frame9.data[6] = pickIntByte(data.pedal, 6);
        frame9.data[7] = pickIntByte(data.pedal, 7);     
        
        // const bool ok9 = can.tryToSend(frame9);

        //packet10
        //nivelDeFreio
        CANMessage frame10;
        frame10.ext = false;
        frame10.rtr = false;
        frame10.id = 11;
        frame10.len = 8;
        frame10.idx = 2;

        frame10.data[0] = pickIntByte(data.pressaoFreio, 0);
        frame10.data[1] = pickIntByte(data.pressaoFreio, 1);
        frame10.data[2] = pickIntByte(data.pressaoFreio, 2);
        frame10.data[3] = pickIntByte(data.pressaoFreio, 3);
        frame10.data[4] = pickIntByte(data.pressaoFreio, 4);
        frame10.data[5] = pickIntByte(data.pressaoFreio, 5);
        frame10.data[6] = pickIntByte(data.pressaoFreio, 6);
        frame10.data[7] = pickIntByte(data.pressaoFreio, 7);

        const bool ok10 = can.tryToSend(frame10);

        Serial.print("Buffer 0: " );
        Serial.println(can.transmitBufferCount(0));
        Serial.print("Buffer 1: " );
        Serial.println(can.transmitBufferCount(1));
        Serial.print("Buffer 2: " );
        Serial.println(can.transmitBufferCount(2));

        // for (int i = 0; i < 8; i++)
        // {
        //     Serial.print(frame0.data[i]);
        //     Serial.print(", ");
        // }
        // Serial.println("");

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

    static bool getagem(){
        ResponseStructContainer c;
        c = e32ttl100.getConfiguration();
        // It's important get configuration pointer before all other operation
        Configuration configuration = *(Configuration*) c.data;
        Serial.println(c.status.getResponseDescription());
        if (c.status.getResponseDescription() == "Success"){
            c.close();
            return true;
        }
        Serial.println(c.status.code);

        printParameters(configuration);

        // ResponseStructContainer cMi;
        // cMi = e32ttl100.getModuleInformation();
        // // It's important get information pointer before all other operation
        // ModuleInformation mi = *(ModuleInformation*)cMi.data;xxzxxzxxzxxzxxz

        // Serial.println(cMi.status.getResponseDescription());
        // Serial.println(cMi.status.code);

        // printModuleInformation(mi);

        c.close();
        // cMi.close();
        return false;
    }

    static void recebagem(){

	
	if (e32ttl100.available()  > 1){

		ResponseStructContainer rsc = e32ttl100.receiveMessage(sizeof(DadosLight));
		struct _DadosLight message = *(DadosLight*) rsc.data;

		Serial.println((message.rpm));
        Serial.println((message.vel));
        Serial.println((message.tensaoBat));
//		free(rsc.data);
		rsc.close();
	    }
    }

    static void setagem(){
	ResponseStructContainer c;
	c = e32ttl100.getConfiguration();
	// It's important get configuration pointer before all other operation
	Configuration configuration = *(Configuration*) c.data;
	Serial.println(c.status.getResponseDescription());
	Serial.println(c.status.code);

	printParameters(configuration);
	configuration.ADDL = 0x0;
	configuration.ADDH = 0x0;
	configuration.CHAN = 0x17;

	configuration.OPTION.fec = FEC_1_ON;
	configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
	configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
	configuration.OPTION.transmissionPower = POWER_17;
	configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;

	configuration.SPED.airDataRate = AIR_DATA_RATE_011_48;
	configuration.SPED.uartBaudRate = UART_BPS_9600;
	configuration.SPED.uartParity = MODE_00_8N1;

	// Set configuration changed and set to not hold the configuration
	ResponseStatus rs = e32ttl100.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
	Serial.println(rs.getResponseDescription());
	Serial.println(rs.code);
	printParameters(configuration);
	c.close();
}

    static void automotivo(){
        bool insucesso = true;
        int counter = 0;

        while (insucesso){
            if (counter > 15){
                return;
            }
            digitalWrite(4, HIGH);
            digitalWrite(5, HIGH);
            delay(600);
            insucesso = !getagem();
            delay(600);
            digitalWrite(4, LOW);
            digitalWrite(5, LOW);
            delay(600);
            recebagem();
            delay(1000);
            counter++;
        }

        delay(1000);
        digitalWrite(4, HIGH);
        digitalWrite(5, HIGH);

        setagem();

        delay(1000);

        digitalWrite(4, LOW);
        digitalWrite(5, LOW);


        return;
    }

    static bool setupTelemetria()
    {
        delay(300);
        e32ttl100.begin();
        delay(20000);
        Serial.println("AUTOMOTIVO");
        automotivo();
        // ResponseStructContainer c;
        // c = e32ttl100.getConfiguration();
        // Configuration configuration = *(Configuration *)c.data;
        // Serial.println(c.status.getResponseDescription());
        // Serial.println(c.status.code);

        // printParameters(configuration);
        // ResponseStructContainer cMi;
        // cMi = e32ttl100.getModuleInformation();
        // ModuleInformation mi = *(ModuleInformation*)cMi.data;

        // Serial.println(cMi.status.getResponseDescription());
        // Serial.println(cMi.status.code);

        // printModuleInformation(mi);

        // c.close();
        // cMi.close();

        return false;
    }

    static void printParameters(struct Configuration configuration) {
	Serial.println("----------------------------------------");

	Serial.print(F("HEAD BIN: "));  Serial.print(configuration.HEAD, BIN);Serial.print(" ");Serial.print(configuration.HEAD, DEC);Serial.print(" ");Serial.println(configuration.HEAD, HEX);
	Serial.println(F(" "));
	Serial.print(F("AddH BIN: "));  Serial.println(configuration.ADDH, BIN);
	Serial.print(F("AddL BIN: "));  Serial.println(configuration.ADDL, BIN);
	Serial.print(F("Chan BIN: "));  Serial.print(configuration.CHAN, DEC); Serial.print(" -> "); Serial.println(configuration.getChannelDescription());
	Serial.println(F(" "));
	Serial.print(F("SpeedParityBit BIN    : "));  Serial.print(configuration.SPED.uartParity, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTParityDescription());
	Serial.print(F("SpeedUARTDataRate BIN : "));  Serial.print(configuration.SPED.uartBaudRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getUARTBaudRate());
	Serial.print(F("SpeedAirDataRate BIN  : "));  Serial.print(configuration.SPED.airDataRate, BIN);Serial.print(" -> "); Serial.println(configuration.SPED.getAirDataRate());

	Serial.print(F("OptionTrans BIN       : "));  Serial.print(configuration.OPTION.fixedTransmission, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFixedTransmissionDescription());
	Serial.print(F("OptionPullup BIN      : "));  Serial.print(configuration.OPTION.ioDriveMode, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getIODroveModeDescription());
	Serial.print(F("OptionWakeup BIN      : "));  Serial.print(configuration.OPTION.wirelessWakeupTime, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getWirelessWakeUPTimeDescription());
	Serial.print(F("OptionFEC BIN         : "));  Serial.print(configuration.OPTION.fec, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getFECDescription());
	Serial.print(F("OptionPower BIN       : "));  Serial.print(configuration.OPTION.transmissionPower, BIN);Serial.print(" -> "); Serial.println(configuration.OPTION.getTransmissionPowerDescription());

	Serial.println("----------------------------------------");

}

static void printModuleInformation(struct ModuleInformation moduleInformation) {
	Serial.println("----------------------------------------");
	Serial.print(F("HEAD BIN: "));  Serial.print(moduleInformation.HEAD, BIN);Serial.print(" ");Serial.print(moduleInformation.HEAD, DEC);Serial.print(" ");Serial.println(moduleInformation.HEAD, HEX);

	Serial.print(F("Freq.: "));  Serial.println(moduleInformation.frequency, HEX);
	Serial.print(F("Version  : "));  Serial.println(moduleInformation.version, HEX);
	Serial.print(F("Features : "));  Serial.println(moduleInformation.features, HEX);
	Serial.println("----------------------------------------");

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

        ACAN2515Settings settings(20UL * 1000UL * 1000UL, 125UL * 1000UL); // CAN bit rate 125 kb/s
        settings.mRequestedMode = ACAN2515Settings::NormalMode;      // Select loopback mode
        errorCode = can.begin(settings, []
                                             { can.isr(); });
        if (errorCode == 0)
        {
            Serial.print("CAN init success");

            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(2000);
            digitalWrite(LED_BUILTIN, LOW);
            
        }
        else
        {
            Serial.print("CAN Configuration error 0x");
            Serial.println(errorCode, HEX);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);

            digitalWrite(LED_BUILTIN, HIGH);
            delay(100);
            digitalWrite(LED_BUILTIN, LOW);
            delay(100);
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
        setupCanBus();
        setupTelemetria();
    }

    return instance;
}

#endif //_COMUNICACAO_H