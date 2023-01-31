#include <Wire.h>

int slaveAddress = 9;
int temp = LOW;

void setup() {
  // put your setup code here, to run once:
  
  
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire.begin();

  Serial.begin(9600);

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  Serial.println("looping");
  temp = !temp;

  Wire.beginTransmission(slaveAddress);
  Wire.write(temp);
  Wire.endTransmission();
  
  
}
