/* 
    !! Comunicação entre as demais bibliotecas !!
    Todo segundo o pico chama uma interrupção
*/

#define CAR_NAME "MV-22"

void sendData()
{
    updateGps();
    float vel = setVel();
    int rpm = setRpm();
    float tempCvt = setCvtTemperature();
    int comb = setComb();

    // Escrita em cartao SD
    writeData(vel, rpm, tempCvt, comb);

    TinyGPS gps = getGps();
    // Serial1.print(CAR_NAME);
    // Serial1.print(",");
    // Serial1.print(vel);
    // Serial1.print(",");
    // Serial1.print(rpm);
    // Serial1.print(",");
    // Serial1.print(vel);
    // Serial1.print(",");
    // Serial1.print(tempCvt);
    // Serial1.print(0);
    // Serial1.print(",");
    // Serial1.println(comb);

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