#include <Wire.h>
int LED = 13;
int x = 0;

void setup() 
{
  pinMode (LED, OUTPUT);
  Wire.begin(9); 
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void receiveEvent(int bytes) 
{
  x = Wire.read();
  Serial.println(x);
}

void loop() 
{
  if (x <= 3) 
  {
    digitalWrite(LED, HIGH);
  }
  else 
  {
    digitalWrite(LED, LOW);
  }
}
