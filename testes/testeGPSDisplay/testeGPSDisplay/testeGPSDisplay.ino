#include <LiquidCrystal.h> 
#include <TinyGPS.h>
#define GPS_RX 4
#define GPS_RX 5
#define GPS_Serial_Baud 9600

//LCD 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup(){
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print ("u");
}

void loop(){}
