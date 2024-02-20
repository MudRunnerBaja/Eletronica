/**
 * Project Classes Placa Central
 */


#ifndef _GPS_H
#define _GPS_H

#include "Setupable.h"
#include <TinyGPSpp.h>

class GPS: public Setupable {
public: 
    
bool setup();

bool test();

bool testChosen(int escolhido);
    
TinyGPSPlus getGps();
    
float getSpeed();
    
void gpsEncoding();
    
bool updateGPS();
    
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
    String datehj;
    bool newData;
    bool gpsOn;
    TinyGPSPlus gps;
};

#endif //_GPS_H