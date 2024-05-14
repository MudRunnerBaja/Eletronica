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
    TinyGPSPlus gps;

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
        gpsEncoding();
        return true;
    }

    bool Debug()
    {
        // Não há GPS_INVALID_AGE na TinyGPSPlus?
        // if (age == TinyGPSPlus::GPS_INVALID_AGE) {
        //     Serial.println("No fix detected");
        // }

        String s = String("Lat: ");
        latitude = gps.location.lat();
        s = String(s + latitude + " | Lon: ");
        longitude = gps.location.lng();
        s = String(s + longitude + "\nAge: ");
        age = gps.location.age();
        s = String(s + age + " | Vel: ");
        speed = gps.speed.kmph();
        s = String(s + speed + " | Sat: ");
        sat = gps.satellites.value();
        s = String(s + sat + "\ngpstime: ");
        gpstime = gps.time.value();
        s = String(s + gpstime + "\ndate: ");
        date = gps.date.value();
        s = String(s + date);

        if (age > 5000)
        {
            Serial.println("AVISO! GPS possivelmente desatualizado!");
        }
        else
        {
            Serial.println("GPS OK");
        }
        return false;
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
            unsigned int tTotal = tf - t0;
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
            age = gps.location.age();
            speed = gps.speed.kmph();
            sat = gps.satellites.value();
            gpstime = gps.time.value();
            date = gps.date.value();

            dia = date / 100000;
            mes = (date / 10000) % 100;
            ano = date % 10000;

            datahj = String(dia);
            datahj += "/";
            datahj += String(mes);
            datahj += "/";
            datahj += String(ano);

            newData = false;
            return true;
        }
        else
        {
            if (age > 5000)
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
        datahj = String(dia);
        datahj += "/";
        datahj += String(mes);
        datahj += "/";
        datahj += String(ano);
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
    String datahj;
    bool newData;
    bool gpsOn;
};

#endif //_GPS_H