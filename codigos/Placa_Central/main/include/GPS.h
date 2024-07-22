/**
 * Project Classes Placa Central
 */

#ifndef _GPS_H
#define _GPS_H

#include "Setupable.h"
#include "Constantes.h"
#include <TinyGPSPlus.h> // http://arduiniana.org/libraries/tinygps/

class GPS : public Setupable
{
public:
    static GPS *instance;
    static GPS *Setup();

    TinyGPSPlus gps;
    bool possuiData;

    bool Loop()
    {
        gpsEncoding();
        return true;
    }

    bool Debug()
    {
        // Não há GPS_INVALID_AGE na TinyGPSPlus?
        // if (age == TinyGPSPlus::GPS_INVALID_AGE) {
        //     Serial.println("No fix detected");
        // }

        if (!Serial)
            return false;

        String s = String("Lat: ");
        latitude = gps.location.lat();
        s = String(s + latitude + " | Lon: ");
        longitude = gps.location.lng();
        s = String(s + longitude + "\nAge: ");
        fix_age = gps.location.age();
        s = String(s + fix_age + " | Vel: ");
        speed = gps.speed.kmph();
        s = String(s + speed + " | Sat: ");
        sat = gps.satellites.value();
        s = String(s + sat + "\ngpstime: ");
        gpstime = gps.time.value();
        s = String(s + gpstime + "\ndate: ");
        date = gps.date.value();
        s = String(s + date);

        if (fix_age > 5000)
        {
            Serial.println("AVISO! GPS possivelmente desatualizado!");
        }
        else
        {
            Serial.println("GPS OK");
        }
        return true;
    }

    void gpsEncoding()
    {
        while (Serial2.available())
        {
            unsigned int t0 = millis();
            unsigned int tf;
            char c = Serial2.read();
            if (gps.encode(c))
                newData = true;

            tf = millis();
            // unsigned int tTotal = tf - t0;
        }
        return;
    }

    bool updateGPS()
    {
        gpsEncoding();

        if (newData)
        {
            gpsOn = true;
            latitude = gps.location.lat();
            longitude = gps.location.lng();
            fix_age = gps.location.age();
            speed = gps.speed.kmph();
            sat = gps.satellites.value();
            gpstime = gps.time.value();

            // Docs sugerem que existe, compilador diz que nao
            // gps.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centissegundos, &fix_age);

            if (!possuiData)
            {

                datahj = String("");
                datahj = String(dia);
                datahj += "/";
                datahj += String(mes);
                datahj += "/";
                datahj += String(ano);
            }

            newData = false;
            return true;
        }
        else
        {
            if (fix_age > 5000)
            {
                gpsOn = false;
            }
            else
            {
                gpsOn = true;
            }
            return false;
        }
    }

    double getSpeed()
    {
        return speed;
    }

    double getLatitude()
    {
        return latitude;
    }

    double getLongitude()
    {
        return longitude;
    }

    String getDataHoje()
    {
        if (possuiData)
        {
            return datahj;
        }
        else
        {
            return "";
        }
    }

    GPS()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    double speed;
    double latitude;
    double longitude;
    unsigned long fix_age;
    unsigned long gpstime;
    unsigned long date;
    unsigned long sat;
    unsigned long milisec;
    unsigned short dia, mes, hora, minuto, segundo, centissegundos;
    unsigned int ano;
    String datahj;

    bool newData;
    bool gpsOn;
};

GPS *GPS::instance{nullptr};

GPS *GPS::Setup()
{
    if (instance == nullptr)
    {
        instance = new GPS();
    }

    Serial2.setTX(GPS_TX);
    Serial2.setRX(GPS_RX);
    Serial2.begin(GPS_BAUD);

    if (!Serial2)
    {
        Serial.println("Falha Serial GPS");
    }
    else
    {
        Serial.println("Inicializado Serial do GPS");
    }

    return instance;
}
#endif //_GPS_H