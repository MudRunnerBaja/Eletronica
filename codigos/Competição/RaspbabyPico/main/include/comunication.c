/* 
    !! Comunicação entre as demais bibliotecas !!
*/

#pragma region DECLARATIONS

#include <Wire.h>
int UnoLCD = 9, SDApin = 16, SCLpin = 17; // Pico I2C0             
byte data[5];  // I2C data transfer
                // (0-1 vel) (2-3 rpm) (4 Comb + tempCvt)

#define CAR_NAME "MV-22"

void writeData(float vel, int rpm, float tempcvt, int comb);
void SendI2CDataTo(int slave);

#pragma endregion

void DisplaySetup() {
    Wire1.setSDA(SDApin);
    Wire1.setSCL(SCLpin);
    Wire1.begin(); // Inicia a comunicação i2c0 como master
}

void UpdateData()
{
    float vel = gpsSpdFloat();
    int rpm = setRpm();
    float tempCvt = setCvtTemperature();
    int comb = setComb();
    int mvd = setRpmMovida();

    // Envia os dados por i2c
    SendI2CDataTo(UnoLCD);

    // Escrita em cartao SD -> Feita por interrupção
    writeData(speed, rpm, tempCvt, comb);

    // // debug
    // // TinyGPSPlus gps = getGps();
    /*
    Serial.print(CAR_NAME);
    Serial.print(",");
    Serial.print(vel);
    Serial.print(",");
    Serial.print(rpm);
    Serial.print(",");
    Serial.print(vel);
    Serial.print(",");
    Serial.print(tempCvt);
    Serial.print("°C");
    Serial.print(",");
    Serial.println(comb);
    */

    Serial.print(dia);Serial.print("/");
    Serial.print(mes);Serial.print("/");
    Serial.println(ano);
    Serial.print(gpstime);
    Serial.print("  ");
    Serial.println(milisec);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    // */
}


void SendI2CDataTo(int slave) {
    unsigned int tmp = millis();
    int vel = speedInt;
    int rpm = rpmGlobal;
    // (0-1 vel) (2-3 rpm) (4 Comb + CVT)
    data[0] = highByte(vel);
    data[1] = lowByte(vel);
    data[2] = highByte(rpm);
    data[3] = lowByte(rpm);

    if (temperaturaCVT > TEMPERATURA_CRITICA_CVT)
        data[4] = 0 + 0x04;
    else { data[4] = 0; }
    data[4] += nivelComb;

    Serial.print("Comecando transmissao ");Serial.println(slave);
    Wire1.beginTransmission(slave);
    int c = Wire1.write(data, 5);
    Wire1.endTransmission();
    
    tmp = millis() - tmp;
    Serial.print(c); Serial.print(" bytes enviados em ");
    Serial.println(tmp);
}
