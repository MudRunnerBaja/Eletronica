#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

long timer, timer2;
int counter;
int data = 0;

int REFRESH_DISPLAY = 100; //Tempo em ms
int POLLING_RATE_DATA = 1000; //Tempo em ms

void setup() {
  Serial.begin(9600);             // Porta serial para o arduino
  Serial1.begin(9600);            // Porta serial para o HC12
  lcd.begin(16,2);
}

void loop() {
  hc12Read();
  hc12Send();
  lcdRefresh();
}


void lcdRefresh(){
  if(millis()>timer2){
    lcd.print("Recived:");
    lcd.write(data);
    lcd.setCursor(0,1);
    lcd.print("Sent:");
    lcd.print(counter);

    timer2 = millis()+REFRESH_DISPLAY;
  }
}

int hc12Read(){
  while(Serial1.available()){
    data = Serial1.read();
    Serial.write(data);
  }
}


int hc12Send(){
  if(millis()>timer){
    Serial1.println(counter);
    counter++;

    timer = millis() + POLLING_RATE_DATA;
  }
}