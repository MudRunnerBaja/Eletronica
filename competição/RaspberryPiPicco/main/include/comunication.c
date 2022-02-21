#define CAR_NAME "MV-22"

void sendData()
{
    float vel = getVel();
    float rpm = getRpm();
    float tempCvt = getCvtTemperature();
    int comb = getComb();
    // TinyGPSPlus gps = getGps();
    Serial1.print(CAR_NAME);
    Serial1.print(",");
    Serial1.print(vel);
    Serial1.print(",");
    Serial1.print(rpm);
    Serial1.print(",");
    Serial1.print(vel);
    Serial1.print(",");
    Serial1.print(tempCvt);
    Serial1.print(",");
    Serial1.println(comb);
    // Ainda não implementado no receptor
    /*Serial1.print(",");
    Serial1.print(gps.location.lat(), 6);
    Serial1.print(gps.location.lng(), 6);
    */
}