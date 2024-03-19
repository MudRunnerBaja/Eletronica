/**
 * Project Classes Placa Central
 */

#include "TemperaturaCVT.h"

/**
 * TemperaturaCVT implementation
 */

TemperaturaCVT::TemperaturaCVT()
{
    return;
}

/**
 * @return float
 */
float TemperaturaCVT::setTemperaturaCvt()
{
    return 0.0;
}

/**
 * @return float
 */
float TemperaturaCVT::getTemperaturaCvt()
{
    mlx.readAmbientTempC();
    mlx.readObjectTempC();
    return 0.0;
}

/**
 * @return bool
 */
bool TemperaturaCVT::Setup()
{
    mlx.begin();
    return;
}

bool TemperaturaCVT::Loop()
{
    return false;
}

bool TemperaturaCVT::TestChosen(int escolhido)
{
    return false;
}

/**
 * @return Adafruit_MLX90614
 */
Adafruit_MLX90614 TemperaturaCVT::getTermopar()
{
    return mlx;
}