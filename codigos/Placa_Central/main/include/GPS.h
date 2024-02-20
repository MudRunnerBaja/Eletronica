/**
 * Project Classes Placa Central
 */


#ifndef _GPS_H
#define _GPS_H

#include "Setupable.h"


class GPS: public Setupable {
public: 
    void Attribute1;
    
void setupGps();
    
TinyGPSPlus getGps();
    
float getSpeed();
    
void gpsEncoding();
    
bool updateGPS();
    
bool testarGps();
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
    string datehj;
    bool newData;
    bool gpsOn;
    TinyGPSPlus gps;
};

#endif //_GPS_H