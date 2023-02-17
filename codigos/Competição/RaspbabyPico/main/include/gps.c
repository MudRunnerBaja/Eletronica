/*
    Implementação do GPS no carro
    A ser revisado e testado
*/
#ifndef GPS_LIB
#define GPS_LIB

//#include <TinyGPS++.h>
//#include <TinyGPSPlus.h>
#include <TinyGPS.h> // Documentação: http://arduiniana.org/libraries/tinygps/

#define GPS_TX 0 // PINO TX UART GPS
#define GPS_RX 1 // PINO RX UART GPS

const unsigned long GPSBaud = 9600;

int year = 0, speedInt = 0;
float flat = 0, flon = 0, speed = 0, altitude = 0;
unsigned long age, date, gpstime, milisec;
short dia = 0, mes = 0, ano = 0;
String datahj;
bool newData = false;

TinyGPS gps;

void setupGps()
{ // CHECAR PINAGEM     Serial1 -> UART0 // Serial2 -> UART1
  Serial1.setTX(GPS_TX);
  Serial1.setRX(GPS_RX);
  Serial1.begin(GPSBaud);
  datahj = String(dia); datahj += "/"; 
  datahj += String(mes); datahj += "/";
  datahj += String(ano);
}

TinyGPS getGps()
{
    return gps;
}

int gpsSpdInt()
{
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
    dia = date /1000; mes = (date /100) % 10; ano = date % 10;
    datahj = String(dia + "/"); datahj += String(mes + "/");
    datahj += String(ano);
    newData = false;
    return true;
  } else { return false; }
}
#endif