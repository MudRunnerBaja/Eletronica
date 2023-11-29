#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <RotaryEncoder.h>

int vlr;
int ledRed = 0;
int ledYel = 1;
int ledGre = 2;
//Encoder
int S1PIN = 20;
int S2PIN = 21;
int KEY = 22;
RotaryEncoder encoder(S1PIN, S2PIN, RotaryEncoder::LatchMode::FOUR3);

 
// u8g2
int SCKPIN = 10, CSPIN = 13;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO

int newPos;

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCKPIN, TXPIN, CSPIN);
void setup(){
  Serial.begin(9600);
  pinMode (KEY, INPUT);
}
void setup1() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGre, OUTPUT);
  pinMode(ledYel, OUTPUT);
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledYel, HIGH);   
  digitalWrite(ledGre, HIGH);
  delay (1000);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYel, LOW);   
  digitalWrite(ledGre, LOW);
  u8g2.begin();
}

void loop(void) {
  static int pos = 0;
  encoder.tick();

  newPos = encoder.getPosition();
  if (pos != newPos) {
    Serial.print("pos:");
    Serial.println(newPos);
    pos = newPos;   
}
  if (!KEY){ newPos = 0;}
}
void loop1(){
u8g2.firstPage();
  do {
    //######### BARRA ATIVA RPM #########
    u8g2.drawFrame(0,0,128,12);
    u8g2.drawBox(0,0,newPos,12);
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setCursor(0, 64);
    u8g2.print(newPos);
  } while ( u8g2.nextPage() );
  if (newPos > 0 && newPos<=43){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYel, LOW);   
    digitalWrite(ledGre, LOW);
  } else if (newPos >= 44 && newPos<=88){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYel, HIGH);   
    digitalWrite(ledGre, LOW);
  } else if (newPos > 88){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYel, HIGH);   
    digitalWrite(ledGre, HIGH);
  } else {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYel, LOW);   
    digitalWrite(ledGre, LOW);
  }
}