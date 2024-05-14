#include <LiquidCrystal.h>

const byte ledPin = 13;
const byte interruptPin = 19;
volatile byte state = LOW;
long told, tpulse, tlcd;
float rpm = 0;
bool refresh;
int relay = 41, corte = 0;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.clear();
  lcd.println(rpm);
  pinMode(relay, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  digitalWrite(relay, LOW);
  delay(500);
  digitalWrite(relay, HIGH);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);
}

void loop() {
  int vlr = analogRead(0);
  int pot = analogRead(8); 

  corte = map(pot, 0, 1024, 800, 4000);

  if (micros() >= told + 1000000){
    rpm = 0;
    refresh = true;
  }
  if (millis()>= tlcd + 200){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(rpm);
    lcd.setCursor(0,1);
    lcd.print(corte);
    //Serial.println(rpm);
    tlcd = millis();
    refresh = false;
    }
    
    if(rpm >= corte){
    digitalWrite(relay, LOW);
    digitalWrite(ledPin, HIGH);
    Serial.println("CORTE"); 
    delay(200);
    digitalWrite(relay, HIGH);
    }//else{
      //digitalWrite(relay, HIGH);
    //}  
}

void blink() {
  Serial.println("Blink");
  float oldRpm = rpm;
  tpulse = micros() - told;
  rpm = 60000000 / tpulse; 
  if (rpm > 6000){
    rpm = oldRpm;
  }
  told = micros();
  refresh = true;
  /*if(rpm >= 300){
    digitalWrite(relay, LOW);
    digitalWrite(ledPin, HIGH);
    Serial.println("CORTE");

     delay(1000); 
     digitalWrite(relay, HIGH);
    }
  digitalWrite(relay, HIGH);
    digitalWrite(ledPin, LOW);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);*/
}
