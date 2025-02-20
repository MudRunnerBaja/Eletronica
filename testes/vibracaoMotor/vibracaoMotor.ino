#include "MPU9250.h"

float rpm = 0;
const byte interruptPin = 19;
long told, tpulse;
unsigned long deltaTime;
unsigned long prevTime;
const int period = 1;
unsigned long repetitions = 0;
int average;
int deltaTimeSum;
bool hasFailed = false;
inline float list[1024];

MPU9250 mpu;

void setup() {
    Serial.begin(2000000);
    Wire.begin();
    pinMode(interruptPin, INPUT_PULLUP);
    Serial.println("INICIALIZANDO");
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
    
    print_acc();

    // if(mpu.update() && !hasFailed){
    //     print_acc();
    // }
    // else{
    //     Serial.println("nao :(");
    //     hasFailed = true;
    // }


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
    unsigned long millisVar = millis();
    deltaTime = millisVar - prevTime;
    prevTime = millis();
    Serial.print(millis());
    Serial.print(",");
    // Serial.print(deltaTime, 4);

    // Serial.print(",");
    // Serial.print(rpm);


    // Serial.print(",");
    // Serial.print(mpu.getAccX(), 4);
    // Serial.print(", ");
    int prevTotal = millis();
    // int i;
    // for (i = 0; i < 1025; i++){
      mpu.update_accel_gyro();
      Serial.print(mpu.getAccX());
      Serial.print(",");
      Serial.print(mpu.getAccY());
      Serial.print(",");
      Serial.println(mpu.getAccZ());
      // list[i] = mpu.getAccX();
    // }


    // for (i = 0; i < 1025; i++){
    //   mpu.update_accel_gyro();
    //   // list[i] = mpu.getAccX();
    // }
    //int totalTime = millis() - prevTotal;
    //Serial.println(totalTime, 4);
    // for (int j = 0; j < 1025; j++){
    //   mpu.update_accel_gyro();
    //   Serial.println(list[j]);
    // }
    // Serial.println(list[400], 4);

    // Serial.print(mpu.getAccY(), 4);
    // Serial.print(", ");
    // Serial.println(mpu.getAccZ(), 4);

    // Serial.print(",");
    // repetitions++;
    // if (deltaTime < 20){
    //     deltaTimeSum += deltaTime;
    // }
    // average = deltaTimeSum/repetitions;
    // Serial.print(average);
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
