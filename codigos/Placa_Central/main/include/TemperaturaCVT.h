/**
 * Project Classes Placa Central
 */

#ifndef _TEMPERATURACVT_H
#define _TEMPERATURACVT_H

#include "Setupable.h"
#include <Adafruit_MLX90614.h>
#include "Constantes.h"

class TemperaturaCVT : public Setupable
{
public:
    TemperaturaCVT();

    float setTemperaturaCvt();

    float getTemperaturaCvt();

    bool Setup();

    bool Loop();

    bool Debug();

    bool TestChosen(int escolhido);

    Adafruit_MLX90614 getTermopar();

private:
    Adafruit_MLX90614 mlx = Adafruit_MLX90614();
    float temperaturaCvt;
};

#endif //_TEMPERATURACVT_H