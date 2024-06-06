#include "MPU9250.h"

float rpm = 0;
const byte interruptPin = 19;
long told, tpulse;
int deltaTime;
int prevTime;
const int period = 1;
unsigned long repetitions = 0;
int average;
int deltaTimeSum;
bool hasFailed = false;

MPU9250 mpu;

void setup() {
    Serial.begin(2000000);
    Wire.begin();
    pinMode(interruptPin, INPUT_PULLUP);
    Serial.println("INCIALIZANDO");
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

    // if(mpu.update() && !hasFailed){
    //     print_acc();
    // }
    // else{
    //     Serial.println("nao :(");
    //     hasFailed = true;
    // }

    mpu.update_accel_gyro();
    print_acc();

    // print_acc();

     if (micros() >= told + 1000000){
     rpm = 0;
   }
//     if (mpu.update()) {
//         static uint32_t prev_ms = millis();
//         if (millis() > prev_ms + period) {
//             //print_roll_pitch_yaw();
//             print_acc();
//             prev_ms = millis();
//         }
//     }
}

void print_acc(){
    // int millisVar = millis();
    // deltaTime = millisVar - prevTime;
    Serial.print(millis());
    // Serial.print(",");
    // Serial.print(deltaTime);

    Serial.print(",");
    Serial.print(rpm);

    // Serial.print(",");
    // repetitions++;
    // if (deltaTime < 20){
    //     deltaTimeSum += deltaTime;
    // }
    // average = deltaTimeSum/repetitions;
    // Serial.print(average);

    Serial.print(",");
    Serial.print(mpu.getAccX(), 4);
    Serial.print(", ");
    Serial.print(mpu.getAccY(), 4);
    Serial.print(", ");
    Serial.println(mpu.getAccZ(), 4);

    // prevTime = millis();
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
