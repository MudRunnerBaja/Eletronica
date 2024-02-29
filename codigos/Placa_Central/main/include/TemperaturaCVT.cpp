/**
 * Project Classes Placa Central
 */


#include "TemperaturaCVT.h"

/**
 * TemperaturaCVT implementation
 */


/**
 * @return float
 */
float TemperaturaCVT::setTemperaturaCvt() {
    return 0.0;
}

/**
 * @return float
 */
float TemperaturaCVT::getTemperaturaCvt() {
    mlx.readAmbientTempC();
    mlx.readObjectTempC();
    return 0.0;
}

/**
 * @return bool
 */
bool TemperaturaCVT::setup() {
    mlx.begin();
    return;
}

bool TemperaturaCVT::test() {
    return false;
}

bool TemperaturaCVT::testChosen(int escolhido) {
    return false;
}

/**
 * @return MAX6675
 */
MAX6675 TemperaturaCVT::getTermopar() {
    return termopar;
}