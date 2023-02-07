/*
    Implementação do GPS no carro
    A ser revisado e testado
*/
//#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
#include <TinyGPS.h> // Documentação original: http://arduiniana.org/libraries/tinygps/

static const uint32_t GPSBaud = 9600;
int year;
float flat, flon, speed, altitude;
unsigned long age, date, gpstime, milisec;
bool newData = false;

TinyGPS gps;

void setupGps()
{
  Serial2.setTX(8);
  Serial2.setRX(9);
  Serial2.begin(GPSBaud);
}

TinyGPS getGps()
{
    return gps;
}

int gpsSpdInt(){
  return (int)speed;
}

float gpsSpdFloat(){
  return speed;
}

bool updateGps()
{
  gpsencoding();

  if (newData)
  {
    gps.f_get_position(&flat, &flon, &age);
    speed = gps.f_speed_kmph();
    altitude = gps.altitude();
    gps.get_datetime(&date, &gpstime, &milisec);
    //gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &milsec);
    newData = false;
    return true;
  } else { return false; }
}

void gpsencoding()
{
  // unsigned int t0 = millis(); unsigned int tf = millis();
  // unsigned int tTotal = tf - t0;
  while (Serial2.available()) {
    char c = Serial2.read();
    if (gps.encode(c)) newData = true;

    // tf = millis();
    // tTotal = tf - t0;
  }
  // Serial.print("\nTempo total de encoding: ");Serial.println(tTotal);
}