/**
 * Project Classes Placa Central
 */

#include "Freio.h"

/**
 * Freio implementation
 */

/**
 * @return bool
 */
bool Freio::Setup()
{
    pinMode(NIVEL_FREIO, INPUT);
    return;
}

/**
 * @return bool
 */
bool Freio::Loop()
{
    return false;
}

/**
 * @return bool
 */
bool Freio::TestChosen(int escolhido)
{
    return false;
}

/**
 * @return short
 */
short Freio::getNivelAtual()
{
    return 0;
}
