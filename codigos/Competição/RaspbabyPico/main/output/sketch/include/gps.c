#line 1 "D:\\lucas\\Documents\\GitHub\\Eletronica\\Codigos\\Competição\\RaspbabyPico\\main\\include\\gps.c"
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
short dia = 0, mes = 0, ano = 0;
String datahj;

bool newData = false;

TinyGPS gps;

void setupGps()
{ // CHECAR PINAGEM
  Serial1.setTX(0);
  Serial1.setRX(1);
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