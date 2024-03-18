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
bool GPS::Setup() {
    return;
}

/**
 * @return bool
 */
bool GPS::Test() {
    return false;
}

/**
 * @return bool
 */
bool GPS::TestChosen(int escolhido) {
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