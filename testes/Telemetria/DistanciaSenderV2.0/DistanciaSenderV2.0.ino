#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

long timer, timer2;
int i;
int data = 0;
char dado[10];


void setup() {
  Serial.begin(9600);             // Serial port to computer
  Serial1.begin(9600);   // Serial port to Serial1
  lcd.begin(16,2);
  //Serial1.println("Testing HC-12 module range...");
}
  int p = 0;
void loop() {
  int newdata = 0;

  // Wait for one second before sending the next message
  
  if(Serial1.available()){
    lcd.clear();
    newdata = 0;
  }

  while(Serial1.available()){
    data = Serial1.read();
    Serial.write(data);
    lcd.write(data);
  }
  

 
  
  if(millis()>timer2){
    //lcd.print("Recived:");
    lcd.setCursor(0,1);
    lcd.print("Sent:");
    lcd.print(i);
    
    timer2 = millis()+100;
  }
  
  if(millis()>timer){
    Serial1.println(i);
    timer = millis() + 1000;
    i++;
    newdata=1;
  }
}
