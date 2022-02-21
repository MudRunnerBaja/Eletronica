#include "RPi_Pico_TimerInterrupt.h"
#include "include/temp.c"
#include "include/comb.c"
#include "include/vel.c"
#include "include/rpm.c"
#include "include/comunication.c"
#define TIMER_INTERVAL_MS 1000

RPI_PICO_Timer ITimer(0);

// Interrupt callback functions
bool TimerHandler(struct repeating_timer *t)
{
  sendData();
  return true;
}

void setup()
{
  Serial.begin(9600);
  combSetup();
  setupVel();
  setupRpm();

  // Interval in unsigned long microseconds
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");
}
void loop()
{
  // put your main code here, to run repeatedly:
}
