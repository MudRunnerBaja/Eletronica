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
bool GPS::setup() {
    return;
}

/**
 * @return bool
 */
bool GPS::test() {
    return false;
}

/**
 * @return bool
 */
bool GPS::testChosen(int escolhido) {
    return false;
}

/**
 * @return TinyGPSPlus
 */
TinyGPSPlus GPS::getGps() {
    return gps;
}

/**
 * @return float
 */
float GPS::getSpeed() {
    return 0.0;
}

/**
 * @return void
 */
void GPS::gpsEncoding() {
    return;
}

/**
 * @return bool
 */
bool GPS::updateGPS() {
    return false;
}