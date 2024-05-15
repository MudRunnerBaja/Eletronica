

#include <U8g2lib.h>
#include <SPI.h>
#include <SoftwareSerial.h>

int SCKPIN = 10, CSPIN = 13;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, SCKPIN, TXPIN, CSPIN);


void loadScreen(){

    u8g2.firstPage();
     do {
        u8g2.setDrawColor(0);
        u8g2.drawXBM( 0, 0, 128, 64, mud_xbm);
        u8g2.setDrawColor(1);
        u8g2.setFont(u8g2_font_t0_13_te);
        u8g2.drawButtonUTF8(16, 62, U8G2_BTN_INV|U8G2_BTN_BW1, 0, 0, 0, "Inicializando...");
        u8g2.setFont(u8g2_font_5x8_tf);
        u8g2.drawButtonUTF8(2, 7, U8G2_BTN_INV|U8G2_BTN_BW1, 0, 0, 0, "Eletronica MudRunner 2023");
  } while (u8g2.nextPage());
}

void setupDisplay(){
    u8g2.begin();
    loadScreen();
}
