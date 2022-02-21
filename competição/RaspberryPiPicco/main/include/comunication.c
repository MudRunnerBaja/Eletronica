#define CAR_NAME "MV-22"

void sendData()
{
    float vel = getVel();
    float rpm = getRpm();
    float tempCvt = getCvtTemperature();
    int comb = getComb();
    Serial.print(CAR_NAME);
    Serial.print(",");
    Serial.print(vel);
    Serial.print(",");
    Serial.print(rpm);
    Serial.print(",");
    Serial.print(vel);
    Serial.print(",");
    Serial.print(tempCvt);
    Serial.print(",");
    Serial.println(comb);
}