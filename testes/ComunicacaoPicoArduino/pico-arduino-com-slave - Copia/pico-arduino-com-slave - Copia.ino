#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

bool hello = true;
unsigned int t0, tf;
char text[10] = "VEL: ";
byte vel = 0;

//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, 18, 19, 17);
U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, 10);
//U8G2_ST7920_128X64_1_2ND_HW_SPI u8g2(U8G2_R0, 17);

void setup(void) 
{ 
  t0 = tf = millis();
  
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
  SPI.begin();
  Serial.begin(9600);
  u8g2.begin();
}

void loop(void) {
  int test = millis();

    fvel();
    int timetest = millis() - test;
    Serial.print("\nTempo Trocando:");Serial.println(timetest);
    Serial.print("vel:");Serial.println(vel);
}

void fvel() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawStr(0,24,text);
  u8g2.sendBuffer();
}

void receiveEvent(int bytes) { 
  int i = 0;
  while(Wire.available()) {
    vel = Wire.read();
    i++;
  }
  int tvel = (unsigned int) vel;
  itoa(vel/10, &text[4], 10);
  itoa(vel%10, &text[5], 10);
  
  Serial.print("textstring: ");Serial.println(text);
}
