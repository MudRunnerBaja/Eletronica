#include "RPi_Pico_TimerInterrupt.h"
#define TIMER_INTERVAL_MS        1000
#define WHEEL_RADIUS 26.67
#define SENSOR_QUANTITY 4
#define SENSOR_QUANTITY_RPM 4
#define CAR_NAME "MV-22"


int velRecieverPort = 3;
int rpmRecieverPort = 4;
int combYellowPort = 5;
int combGreenPort = 6;
int velCounter = 0;
int rpmCounter = 0;
int lastTime = 0;
float pi = 3.14;

// Interrupt callback functions
bool TimerHandler(struct repeating_timer *t)
{
  float vel = calcVel();
  float rpm = calcRpm();
  float tempCvt = calcTempCvt();
  int comb = calcComb();
  Serial.print(CAR_NAME);
  Serial.print(",");
  Serial.print(vel);
  Serial.print(",");
  Serial.print(rpm);
  Serial.print(",");
  Serial.print(vel);
  Serial.print(",");
  Serial.print(tempCvt);
  Serial.print(",");
  Serial.println(comb);
  return true;
}

void velCounterFunc() {
  velCounter++;
}

void rpmCounterFunc() {
  rpmCounter++;
}

// Calculation functions
float calcRpm() {
  return rpmCounter * 60 / SENSOR_QUANTITY_RPM;
}

float calcVel() {
  float cmPerSignal = (WHEEL_RADIUS * 2 * pi) / SENSOR_QUANTITY;
  float vel = cmPerSignal * velCounter / 100;
  velCounter = 0;
  return vel;
}

int calcComb() {
  int yellowState = digitalRead(combYellowPort);
  int greenState = digitalRead(combGreenPort);

  if (greenState && yellowState)
    return 2;
  else if (yellowState)
    return 1;

  return 0;
}

float calcTempCvt() {
  // make data aquisition
  return 1.0;
}

// Init RPI_PICO_Timer
RPI_PICO_Timer ITimer(0);

void setup()
{
  Serial.begin(9600);

  pinMode(combYellowPort, INPUT);
  pinMode(combGreenPort, INPUT);

  attachInterrupt(digitalPinToInterrupt(velRecieverPort), velCounterFunc, RISING);
  attachInterrupt(digitalPinToInterrupt(rpmRecieverPort), rpmCounterFunc, RISING);

  // Interval in unsigned long microseconds
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");
}
void loop() {
  // put your main code here, to run repeatedly:

}
