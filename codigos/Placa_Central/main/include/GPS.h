/**
 * Project Classes Placa Central
 */

#ifndef _GPS_H
#define _GPS_H

#include "Setupable.h"
#include "Constantes.h"
#include <TinyGPS++.h>

class GPS : public Setupable
{
public:
    TinyGPSPlus gps();

    bool Setup()
    {
        Serial2.setTX(GPS_TX);
        Serial2.setRX(GPS_RX);
        Serial2.begin(GPS_BAUD);

        if (!Serial2)
        {
            Serial.println("Falha Serial GPS");
            return false;
        }
        Serial.println("Inicializado Serial do GPS");
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

    float getSpeed()
    {
        return 0.0;
    }

    void gpsEncoding()
    {
        return;
    }

    bool updateGPS()
    {
        return false;
    }

private:
    double speed;
    double latitude;
    double longitude;
    unsigned long age;
    unsigned long gpstime;
    unsigned long date;
    unsigned long sat;
    unsigned long milisec;
    unsigned short dia;
    unsigned short mes;
    unsigned short ano;
    String datehj;
    bool newData;
    bool gpsOn;
};

#endif //_GPS_H