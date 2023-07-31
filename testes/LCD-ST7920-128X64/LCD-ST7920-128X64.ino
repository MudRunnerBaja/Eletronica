#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

// LCD
int SCKPIN = 10, CSPIN = 13;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCKPIN, TXPIN, CSPIN);

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,24,"Hello World!");
  } while ( u8g2.nextPage() );
}
