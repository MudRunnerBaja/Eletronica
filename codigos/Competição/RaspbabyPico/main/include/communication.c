/* 
    !! Comunicação entre as demais bibliotecas !!
*/
#ifndef COMMUNICATION
#define COMMUNICATION

#include <Wire.h>   // Comunicação I2C

#define SLAVE_LCD 9
#define SDApin 16
#define SCLpin 17 // Pico I2C0

byte data[5];  // I2C data transfer
                // (0-1 vel) (2-3 rpm) (4 Comb + tempCvt)

void writeData(float vel, int rpm, float tempcvt, int comb, int rpmMvd);
void SendI2CDataTo(int slave);

void DisplaySetup() {
    Wire.setSDA(SDApin);
    Wire.setSCL(SCLpin);
    Wire.begin(); // Inicia a comunicação i2c0 como master
}

void UpdateData()
{
    tempo = millis() - tempobase;
    int ivel = gpsSpdInt();
    int rpm = setRpm();
    float tempCvt = setCvtTemperature();
    byte comb = setComb();
    int mvd = setRpmMovida();
    
        // Converte vel e rpm em bytes para transferência
    data[0] = highByte(ivel);
    data[1] = lowByte(ivel);
    data[2] = highByte(rpm);
    data[3] = lowByte(rpm);
    
    // Armazena o nível de combustível e se a temperatura é crítica em um byte
    if (temperaturaCVT > TEMPERATURA_CRITICA_CVT)
        data[4] = 0 + 0x04;
    else { data[4] = 0; }
    data[4] += nivelComb;

    // Envia os dados por i2c
    SendI2CDataTo(SLAVE_LCD);

    // Escrita em cartao SD -> Feita por interrupção core1
    // writeData(speed, rpm, tempCvt, comb, mvd);

    if (Serial) {
        Serial.print(dia);Serial.print("/");
        Serial.print(mes);Serial.print("/");
        Serial.println(ano);
        Serial.print("LAT=");
        Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
        Serial.print(" LON=");
        Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
        Serial.print(" SAT=");
        Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    }
}


void SendI2CDataTo(int slave) {
    unsigned int tmp = millis();

    Serial.print("Comecando transmissao ");Serial.println(slave);
    Wire.beginTransmission(slave);
    int c = Wire.write(data, 5);
    Wire.endTransmission();
    
    tmp = millis() - tmp;
    Serial.print(c); Serial.print(" bytes enviados em ");
    Serial.println(tmp);
}
#endif