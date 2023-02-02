#include <Wire.h>

int UnoLCD = 9;
int SDApin = 8;
int SCLpin = 9;

int counter = 0;
int testvel = 0;
int testrpm = 0;

byte data[4];

int ld = LOW;

unsigned int tf, t0, t1;

void setup() {
  // put your setup code here, to run once:
  Wire.setSDA(SDApin);
  Wire.setSCL(SCLpin);
  Wire.begin();

  pinMode(21, OUTPUT);
  pinMode(20, OUTPUT);

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
    testrpm += 100;
    if (testvel > 99) { testvel = 0;}
    if (testrpm > 6000) { testrpm = 0;}
    Serial.print("\ntestvel: "); Serial.println(testvel);
    Serial.print("\ntestrpm: "); Serial.println(testrpm);
    t1 = millis();
  }

  if (tf - t0 >= 250){
    unsigned int tmp = millis();

    data[0] = highByte(testvel);
    data[1] = lowByte(testvel);
    data[2] = highByte(testrpm);
    data[3] = lowByte(testrpm);
    
    Wire.beginTransmission(UnoLCD);
    int c = Wire.write(data, 4);
    Wire.endTransmission();
    
    tmp = millis() - tmp;
    ld = !ld;
    digitalWrite(21, ld);
    digitalWrite(20, ld);
    Serial.print(c); Serial.print(" bytes done in");Serial.println(tmp);
    t0 = millis();
  }
}
