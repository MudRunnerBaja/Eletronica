#include <RPi_Pico_TimerInterrupt.h> // Interrupção por tempo
#include <RPi_Pico_ISR_Timer.h>
#include <RPi_Pico_ISR_Timer.hpp>

#include "include/temp.c" // Temperatura CVT
#include "include/comb.c" // Níveis de combustível
#include "include/vel.c" // Velocidade do carro
#include "include/rpm.c" // RPM do carro
#include "include/display.c" // Placa do display
#include "include/sdcard.c"
#include "include/comunication.c" // Comunicação entre bibliotecas e serial

bool setupCompleto = false;

#define TIMER_INTERVAL_MS 1000

RPI_PICO_Timer ITimer(0);

// Interrupt callback functions Core0
bool TimerHandler(struct repeating_timer *t)
{
  sendData();
  return true;
}

// Interrupt callback functions Core1
bool WriteSD(struct repeating_timer *t)
{
  int vel = getVel();
  int rpm = getRpm();
  float tempCvt = getTempCvt();
  int comb = getNivelComb();
  // Escrita em cartao SD
  writeData(vel, rpm, tempCvt, comb);
  return true;
}

void setup()
{
  Serial.begin(9600);

      // Esperando pela resposta do monitor serial. 
      // Comentar quando for para o carro.
  /*
  while (!Serial) {
    yield();
  }
  delay(1000);

  Serial.println(F("Type any character to start"));
  while (!Serial.available()) {
    yield();
  }
  */
  Serial.println("Iniciando setup...");
  // setupGps();
  combSetup();
  displaySetup();
  cvtSetup();
  velSetup();
  rpmSetup();
  sdcardSetup();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
  delay(1000);
  digitalWrite(ledTempCvt, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  // Interval in unsigned long microseconds
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");

  setupCompleto = true;
}

void setup1()
{
  while (!setupCompleto)
  {
    delay(1);
  }

  delay(50);

  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, WriteSD))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");

  Serial.print("Setup finalizado.");

}

void loop()
{
  // updateGps(); // ainda não implementado no receptor
}

void loop1()
{
  mostraDados();
}
