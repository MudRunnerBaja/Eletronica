#include <Wire.h>

int LED = 13;
int signal = LOW;

void receiveEvent(int bytes)
{
  while (Wire.available()) {
    signal = Wire.read();
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Wire.begin(9);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
  digitalWrite(LED, signal);
  
  
  
}
