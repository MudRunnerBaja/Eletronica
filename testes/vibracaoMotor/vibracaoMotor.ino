#include "MPU9250.h"

float rpm = 0;
const byte interruptPin = 19;
long told, tpulse;


MPU9250 mpu;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    pinMode(interruptPin, INPUT_PULLUP);
    delay(2000);
    
    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }
    mpu.verbose(true);
    mpu.calibrateAccelGyro();
    mpu.verbose(false);
    attachInterrupt(digitalPinToInterrupt(interruptPin), sinal, RISING);
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            //print_roll_pitch_yaw();
            print_acc();
            prev_ms = millis();
        }
    }
}

void print_acc(){
    Serial.print(millis());
    Serial.print(",");
    Serial.print(rpm);
    Serial.print(",");
    Serial.print(mpu.getAccX(), 4);
    Serial.print(", ");
    Serial.print(mpu.getAccY(), 4);
    Serial.print(", ");
    Serial.println(mpu.getAccZ(), 4);
}

void sinal() {
  float oldRpm = rpm;
  tpulse = micros() - told;
  rpm = 60000000 / tpulse; 
  if (rpm > 6000){
    rpm = oldRpm;
  }
  told = micros();
}
