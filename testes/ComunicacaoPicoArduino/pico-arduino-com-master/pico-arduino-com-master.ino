#include <Wire.h>

int UnoLCD = 9;
int SDApin = 8;
int SCLpin = 9;

int counter = 0;
byte testvel = 0;

unsigned int tf, t0, t1;

void setup() {
  // put your setup code here, to run once:
  Wire.setSDA(SDApin);
  Wire.setSCL(SCLpin);
  Wire.begin();

  Serial.begin(9600);
  tf = t0 = t1 = millis();
  Serial.println("Setup Finalizado");
}

void loop() {
  // put your main code here, to run repeatedly:
  tf = millis();
  if (tf - t1 >= 125)
  {
    testvel++;
    if (testvel > 99) { testvel = 0; }
    Serial.print("\ntestvel: "); Serial.println(testvel);
    t1 = millis();
  }

  if (tf - t0 >= 250){
    unsigned int tmp = millis();
    Serial.println("Transfering");
    Wire.beginTransmission(UnoLCD);
    Wire.write(testvel);
    Wire.endTransmission();
    tmp = millis() - tmp;
    Serial.print("Done in ");Serial.println(tmp);
    t0 = millis();
  }
}
