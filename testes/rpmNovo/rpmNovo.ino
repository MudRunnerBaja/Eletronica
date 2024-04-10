#include <LiquidCrystal.h>

const byte ledPin = 13;
const byte interruptPin = 19;
volatile byte state = LOW;
long told, tpulse, tlcd;
float rpm = 1000;
bool refresh;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.println(rpm);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() {
  if (micros() >= told + 1000000){
    rpm = 0;
    refresh = true;
  }
  if (millis()>= tlcd + 100){
  lcd.clear();
  lcd.println(rpm);
  Serial.println(rpm);
  tlcd = millis();
  refresh = false;
  }
}

void blink() {
  tpulse = micros() - told;
  rpm = 60000000 / tpulse; 
  told = micros();
  refresh = true;
}
