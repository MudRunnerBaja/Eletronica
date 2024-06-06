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

    float setTemperaturaObjeto()
    {
        temperaturaObjeto = mlx.readObjectTempC();
        return temperaturaObjeto;
    }

    float setTemperaturaAmbiente()
    {
        temperaturaAmbiente = mlx.readAmbientTempC();
        return temperaturaAmbiente;
    }

    float getTemperaturaObjeto()
    {
        return temperaturaObjeto;
    }

    float getTemperaturaAmbiente()
    {
        return temperaturaAmbiente;
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
        if (!Serial)
            return false;

        String s = String("TAmbiente: ");
        s = String(s + temperaturaAmbiente + " | TObjeto: ");
        s = String(s + temperaturaObjeto);
        Serial.println(s);

        return true;
    }

    Adafruit_MLX90614 getTermopar()
    {
        return mlx;
    }

private:
    Adafruit_MLX90614 mlx = Adafruit_MLX90614();
    float temperaturaObjeto = 0.0;
    float temperaturaAmbiente = 0.0;
};

#endif //_TEMPERATURACVT_H