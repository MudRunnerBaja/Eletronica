#include <Wire.h>

int UnoLCD = 9, SDApin = 0, SCLpin = 1; // Pico I2C0             

byte data[5];  // I2C data transfer

void setup() {
  // put your setup code here, to run once:
    Wire.setSDA(SDApin);
    Wire.setSCL(SCLpin);
    Wire.begin(); // Inicia a comunicação i2c0 como master
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
      unsigned int tmp = millis();
    int vel = 20;
    int rpm = 1684;
    // (0-1 vel) (2-3 rpm) (4 Comb + CVT)
    data[0] = highByte(vel);
    data[1] = lowByte(vel);
    data[2] = highByte(rpm);
    data[3] = lowByte(rpm);
    data[4] = 57;
    Serial.print("Comecando transmissao ");Serial.println(9);
    Wire.beginTransmission(9);
    int c = Wire.write(data, 5);
    Wire.endTransmission();
    
    tmp = millis() - tmp;
    Serial.print(c); Serial.print(" bytes enviados em ");
    Serial.println(tmp);
}
