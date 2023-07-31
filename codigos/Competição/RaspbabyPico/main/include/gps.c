/*
    Implementação do GPS no carro
    A ser revisado e testado
*/
#ifndef GPS_LIB
#define GPS_LIB

#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
//#include <TinyGPS.h> // Documentação: http://arduiniana.org/libraries/tinygps/

#define GPS_TX 0 // PINO TX UART GPS
#define GPS_RX 1 // PINO RX UART GPS

const unsigned long GPSBaud = 9600;

float  speed = 0;
double flat = 0, flon = 0;
uint32_t age, gpstime, date, sat;
unsigned long milisec;
unsigned int dia = 0, mes = 0, ano = 0;
String datahj;
bool newData = false;
bool gpsOn = false;

TinyGPSPlus gps;

void setupGps()
{ // CHECAR PINAGEM     Serial1 -> UART0 // Serial2 -> UART1
  Serial1.setTX(GPS_TX);
  Serial1.setRX(GPS_RX);
  Serial1.begin(GPSBaud);
  flat = gps.location.lat();
  flon = gps.location.lng();
  age = gps.location.age();
}

TinyGPSPlus getGps()
{
    return gps;
}

int gpsSpdInt()
{
  return (int) speed;
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
  }
}

bool updateGps()
{
  gpsencoding();

  if (newData)
  {
    gpsOn = true;
    flat = gps.location.lat();
    flon = gps.location.lng();
    age = gps.location.age();
    speed = gps.speed.kmph();
    sat = gps.satellites.value();
    gpstime = gps.time.value();
    date = gps.date.value();

    dia = date / 100000; mes = (date /10000) % 100; ano = date % 10000;

    datahj = String(dia); datahj += "/";
    datahj += String(mes); datahj += "/";
    datahj += String(ano);

    newData = false;
    return true;
  } else { 
    /*if (age == TinyGPSPlus::GPS_INVALID_AGE) {
      gpsOn = false;
     // Serial.println("No fix detected");
    }
    else*/ if (age > 5000) {
      gpsOn = false;
    //  Serial.println("Warning: possible stale data!");
    }
    else { gpsOn = true; }
    return false; }
}
#endif