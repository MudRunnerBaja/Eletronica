/*
    Implementação (não implementada) do GPS no carro
    A ser revisado e testado
*/
//#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
#include <TinyGPS.h>

static const uint32_t GPSBaud = 9600;
int year;
byte month, day, hour, minute, second, milsec;
float flat, flon, speed, altitude;
unsigned long age;

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
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    gps.f_get_position(&flat, &flon, &age);
    speed = gps.f_speed_kmph();
    altitude = gps.f_course();
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &milsec);
  }
}