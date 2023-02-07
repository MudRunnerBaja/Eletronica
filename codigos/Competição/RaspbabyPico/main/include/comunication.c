/* 
    !! Comunicação entre as demais bibliotecas !!
*/

#pragma region DECLARATIONS

#include <Wire.h>
int UnoLCD = 9, SDApin = 8, SCLpin = 9; // Pico-Uno I2C
byte data[12];  // I2C data transfer
                // (0-3 vel) (4-5 rpm) (6-9 tempCvt) (10-11 comb)

#define CAR_NAME "MV-22"

void writeData(float vel, int rpm, float tempcvt, int comb);
void SendI2CDataTo(int slave);

#pragma endregion

void DisplaySetup() {
    Wire.setSDA(SDApin);
    Wire.setSCL(SCLpin);
    Wire.begin(); // Inicia a comunicação i2c0 como master
}

void UpdateData()
{
    float vel = gpsSpdFloat();
    int rpm = setRpm();
    float tempCvt = setCvtTemperature();
    int comb = setComb();

    // Envia os dados por i2c
    SendI2CDataTo(UnoLCD);

    // Escrita em cartao SD -> Feita por interrupção
    // writeData(speed, rpm, tempCvt, comb);

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

    Serial.print(date);
    Serial.print("  ");
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

    // (0-3 vel) (4-5 rpm) (6-9 tempCvt) (10-11 comb)
    memcpy(data, &speed, sizeof(data));
    memcpy(&data[4], &rpmGlobal, sizeof(data));
    memcpy(&data[6], &temperaturaCVT, sizeof(data));
    memcpy(&data[10], &nivelComb, sizeof(data));

    Wire.beginTransmission(slave);
    int c = Wire.write(data, 12);
    Wire.endTransmission();
    
    tmp = millis() - tmp;
    Serial.print(c); Serial.print(" bytes done in");Serial.println(tmp);
}
