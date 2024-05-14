#include "MPU9250.h"
#include "LiquidCrystal.h"
#define plus30 33
#define minus45 31
#define safe 32

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

double speed;
MPU9250 mpu;
int currentLed;

void setup() {
    pinMode(plus30, OUTPUT);
    pinMode(minus45, OUTPUT);
    pinMode(safe, OUTPUT);
    Serial.begin(115200);
    Wire.begin();
    lcd.begin(16,2);
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
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            //print_roll_pitch_yaw();
            print_acc();
            levelWarningHandler();
            get_speed();
            prev_ms = millis();
        }
    }
}

void ledSwitcher(int newLed){
    if (newLed != currentLed){
        digitalWrite(newLed, HIGH);
        digitalWrite(currentLed, LOW);
        currentLed = newLed;
    }
}

void levelWarningHandler(){
    double angle = mpu.getPitch();
    if (angle > 30){ledSwitcher(plus30);};
    if (angle < 30 && angle > -45){ledSwitcher(safe);};
    if (angle < -45){ledSwitcher(minus45);};
    lcd.print(angle);
    lcd.setCursor(0,0);
}

void print_roll_pitch_yaw() {
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.print(mpu.getRoll(), 2);
}

void print_acc(){
    Serial.print("X,Y,Z: ");
    Serial.print(mpu.getAccX(), 2);
    Serial.print(", ");
    Serial.print(mpu.getAccY(), 2);
    Serial.print(", ");
    Serial.print(mpu.getAccZ(), 2);
}

void get_speed(){
    
    if (mpu.getAccX() > 0.06 || mpu.getAccX() < -0.06){
        speed += mpu.getAccX();
    }
    Serial.print("speed: ");
    Serial.println(speed);
}