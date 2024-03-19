/**
 * Project Classes Placa Central
 */

#include "GPS.h"

/**
 * GPS implementation
 */

/**
 * @return bool
 */
bool GPS::Setup()
{
    Serial2.setTX(GPS_TX);
    Serial2.setRX(GPS_RX);
    Serial2.begin(GPS_BAUD);

    if (!Serial2)
    {
        Serial.println("Falha Serial GPS");
        return false;
    }
    Serial.println("Inicializado Serial do GPS");
    return true;
}

/**
 * @return bool
 */
bool GPS::Loop()
{
    return false;
}

/**
 * @return bool
 */
bool GPS::TestChosen(int escolhido)
{
    return false;
}

/**
 * @return TinyGPSPlus
 */
TinyGPSPlus GPS::getGps()
{
    return gps;
}

/**
 * @return float
 */
float GPS::getSpeed()
{
    return 0.0;
}

/**
 * @return void
 */
void GPS::gpsEncoding()
{
    return;
}

/**
 * @return bool
 */
bool GPS::updateGPS()
{
    return false;
}
