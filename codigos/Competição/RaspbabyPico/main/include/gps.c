/*
    Implementação (não implementada) do GPS no carro
    A ser revisado e testado
*/
//#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
#include <TinyGPS.h>

static const uint32_t GPSBaud = 9600;
int year;
float flat, flon, speed, altitude;
unsigned long age, date, gpstime, milisec;

TinyGPS gps;

void setupGps()
{
    Serial1.begin(GPSBaud);
}

TinyGPS getGps()
{
    return gps;
}

void updateGps()
{
  bool newData = false;

  for (unsigned long start = millis(); millis() - start < 100;)
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      if (gps.encode(c)) 
        newData = true;
    }
  }

  if (newData)
  {
    gps.f_get_position(&flat, &flon, &age);
    speed = gps.f_speed_kmph();
    altitude = gps.altitude();
    gps.get_datetime(&date, &gpstime, &milisec);
    //gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &milsec);
  }
}