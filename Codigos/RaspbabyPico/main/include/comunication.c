/* 
    !! Comunicação entre as demais bibliotecas !!
    Todo segundo o pico chama uma interrupção
*/

#define CAR_NAME "MV-22"

void sendData()
{
    float vel = setVel();
    int rpm = setRpm();
    float tempCvt = setCvtTemperature();
    int comb = setComb();

    // Escrita em cartao SD
    // writeData(vel, rpm, tempCvt, comb);

    // TinyGPSPlus gps = getGps();
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
    // // Ainda não implementado no receptor
    // /*Serial1.print(",");
    // Serial1.print(gps.location.lat(), 6);
    // Serial1.print(gps.location.lng(), 6);
    // */
}