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
    TemperaturaCVT()
    {
        return;
    }

    float setTemperaturaCvt()
    {
        return 0.0;
    }

    float getTemperaturaCvt()
    {
        return 0.0;
    }

    bool Setup()
    {
        mlx.begin();
        return true;
    }

    bool Loop()
    {
        return false;
    }

    bool Debug()
    {
        return false;
    }

    Adafruit_MLX90614 getTermopar()
    {
        return mlx;
    }

private:
    Adafruit_MLX90614 mlx = Adafruit_MLX90614();
    float temperaturaCvt;
};

#endif //_TEMPERATURACVT_H