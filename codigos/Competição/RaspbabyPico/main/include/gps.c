/*
    Implementação (não implementada) do GPS no carro
    A ser revisado e testado
*/
#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 1, TXPin = 2;
static const uint32_t GPSBaud = 4800;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setupGps()
{
    ss.begin(GPSBaud);
}

TinyGPSPlus getGps()
{
    return gps;
}

void updateGps()
{
    while (ss.available() > 0)
        gps.encode(ss.read());
}