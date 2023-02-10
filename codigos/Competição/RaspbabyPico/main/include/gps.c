/*
    Implementação do GPS no carro
    A ser revisado e testado
*/
//#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
#include <TinyGPS.h> // Documentação original: http://arduiniana.org/libraries/tinygps/

static const uint32_t GPSBaud = 9600;
int year = 0, speedInt = 0;
float flat = 0, flon = 0, speed = 0, altitude = 0;
unsigned long age, date, gpstime, milisec;
bool newData = false;

TinyGPS gps;

void setupGps()
{ // CHECAR PINAGEM
  Serial1.setTX(0);
  Serial1.setRX(1);
  Serial1.begin(GPSBaud);
}

TinyGPS getGps()
{
    return gps;
}

int gpsSpdInt(){
  return speedInt;
}

float gpsSpdFloat(){
  return speed;
}

void gpsencoding()
{
  while (Serial1.available()) {
    unsigned int t0 = millis(); unsigned int tf;
    char c = Serial1.read();
    if (gps.encode(c)) newData = true;

    tf = millis();
    unsigned int tTotal = tf - t0;
    //Serial.print("\nTempo total de encoding: ");Serial.println(tTotal);
  }
}

bool updateGps()
{
  gpsencoding();

  if (newData)
  {
    gps.f_get_position(&flat, &flon, &age);
    speed = gps.f_speed_kmph();
    speedInt = (int) speed;
    altitude = gps.altitude();
    gps.get_datetime(&date, &gpstime, &milisec);
    //gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &milsec);
    newData = false;
    return true;
  } else { return false; }
}