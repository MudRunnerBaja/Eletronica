/**
 * Project Classes Placa Central
 */

#ifndef _TEMPERATURACVT_H
#define _TEMPERATURACVT_H

#include "Setupable.h"
#include <Adafruit_MLX90614.h>
#include "Constantes.h"

/*
    REVISAR PINOUT E SETUP
*/

class TemperaturaCVT : public Setupable
{
public:
    static TemperaturaCVT *instance;
    static TemperaturaCVT *Setup();

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

    TemperaturaCVT(TemperaturaCVT &outro) = delete;

    TemperaturaCVT()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    static Adafruit_MLX90614 mlx;
    float temperaturaObjeto = 0.0;
    float temperaturaAmbiente = 0.0;
};

Adafruit_MLX90614 TemperaturaCVT::mlx = Adafruit_MLX90614();
TemperaturaCVT *TemperaturaCVT::instance{nullptr};
TemperaturaCVT *TemperaturaCVT::Setup()
{
    if (instance == nullptr)
    {
        instance = new TemperaturaCVT();
    }

    // mlx = Adafruit_MLX90614();

    mlx.begin();

    return instance;
}

#endif //_TEMPERATURACVT_H