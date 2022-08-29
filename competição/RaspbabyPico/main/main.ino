#include "RPi_Pico_TimerInterrupt.h" // Interrupção por tempo

#include "include/temp.cpp" // Temperatura CVT
#include "include/comb.cpp" // Níveis de combustível
#include "include/vel.cpp" // Velocidade do carro
#include "include/rpm.cpp" // RPM do carro
#include "include/display.cpp" // Placa do display
#include "include/comunication.cpp" // Comunicação entre bibliotecas e serial
// #include "include/gps.cpp" // GPS (Não implementado)

#define TIMER_INTERVAL_MS 1000

RPI_PICO_Timer ITimer(0);

// Interrupt callback functions
bool TimerHandler(struct repeating_timer *t)
{
  sendData(); // communication.cpp <- atualiza os dados
  return true;
}

void setup()
{
  Serial.begin(9600);  // debug
  Serial1.begin(9600); // send data;
  // setupGps();
  combSetup();
  setupVel();
  setupRpm();
  setupDisplay();
  cvtSetup();

  // Interval in unsigned long microseconds
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");
}
void loop()
{
  // updateGps(); // ainda não implementado no receptor
  mostraDados();
}
