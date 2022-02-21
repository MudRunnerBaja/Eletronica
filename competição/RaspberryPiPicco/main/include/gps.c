#include <TinyGPS++.h>
TinyGPSPlus gps;

void setupGps()
{
    Serial2.begin(9600);
}

TinyGPSPlus getGps()
{
    return gps;
}

// bool isGpsReady()
// {
//     while (Serial2.available() > 0)
//         if (gps.encode(Serial2.read()))
//             return true;
//     return false;
// }

void updateGps()
{
    while (Serial2.available() > 0)
        gps.encode(Serial2.read());
}