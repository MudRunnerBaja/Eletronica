/**
 * Project Classes Placa Central
 */


#ifndef _TEMPERATURACVT_H
#define _TEMPERATURACVT_H

#include "Setupable.h"
#include <max6675.h>
#include <Adafruit_MLX90614.h>

class TemperaturaCVT: public Setupable {
public: 
    
float setTemperaturaCvt();
    
float getTemperaturaCvt();
    
bool setup();

bool test();

bool testChosen(int escolhido);
    
MAX6675 getTermopar();
private: 
    Adafruit_MLX90614 mlx = Adafruit_MLX90614();
    float temperaturaCvt;
    MAX6675 termopar;
};

#endif //_TEMPERATURACVT_H