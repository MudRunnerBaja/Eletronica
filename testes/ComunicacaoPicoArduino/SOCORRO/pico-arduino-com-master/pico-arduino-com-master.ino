#include <Wire.h>
int x = 0;

void setup() 
{
  Wire1.setSDA(20);
  Wire1.setSCL(21);
  Wire1.begin(); 
  Serial.begin(9600);
}

void loop() 
{
  Wire1.beginTransmission(9);
  Wire1.write(x);              
  Wire1.endTransmission();
 
  x++;
  if (x > 6) 
  {
    x = 0;
  }
  delay(200);
}
