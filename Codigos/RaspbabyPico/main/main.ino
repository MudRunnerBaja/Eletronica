#include <RPi_Pico_TimerInterrupt.h> // Interrupção por tempo
#include <RPi_Pico_ISR_Timer.h>
#include <RPi_Pico_ISR_Timer.hpp>

#include "include/temp.c" // Temperatura CVT
#include "include/comb.c" // Níveis de combustível
#include "include/vel.c" // Velocidade do carro
#include "include/rpm.c" // RPM do carro
#include "include/display.c" // Placa do display
#include "include/comunication.c" // Comunicação entre bibliotecas e serial

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
  Serial.begin(9600);
  Serial.print("Iniciando setup...");
  // setupGps();
  combSetup();
  cvtSetup();
  velSetup();
  rpmSetup();
  displaySetup();
  delay(1000);
  digitalWrite(ledTempCvt, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
    
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Interval in unsigned long microseconds
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");

    Serial.print("Funcionando...");
}
void loop()
{
  // updateGps(); // ainda não implementado no receptor
  mostraDados();
}
