#include <RPi_Pico_TimerInterrupt.h> // Interrupção por tempo
#include <RPi_Pico_ISR_Timer.h>
#include <RPi_Pico_ISR_Timer.hpp>


#include "include/temp.c" // Temperatura CVT
#include "include/comb.c" // Níveis de combustível
#include "include/rpm.c" // RPM do carro
#include "include/gps.c" // GPS 
#include "include/sdcard.c" // Modulo SD
#include "include/comunication.c" // Comunicação entre bibliotecas e serial

bool setupCompleto = false;

#define TIMER_INTERVAL_MS 1000


RPI_PICO_Timer ITimer(0);
RPI_PICO_Timer Core1Timer(1);

// Interrupt callback functions Core0
bool TimerHandler(struct repeating_timer *t)
{
  UpdateData();
  Serial.println("Nucleo 0 - Dados Atualizados");
  return true;
}

// Interrupt callback functions Core1
bool WriteSD(struct repeating_timer *t)
{
  float vel = gpsSpdFloat();
  int rpm = getRpm();
  float tempCvt = getTempCvt();
  int comb = getNivelComb();
  // Escrita em cartao SD
  writeData(vel, rpm, tempCvt, comb);
  Serial.println("Nucleo 1 - Dados escritos");
  return true;
}

void setup()
{
  Serial.begin(9600);
  /*
      // Esperando pela resposta do monitor serial. 
      // Comentar quando for para o carro.
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

  DisplaySetup();
  setupGps();
  combSetup();
  cvtSetup();
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
  /*
  if (Core1Timer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, WriteSD))
    Serial.println("Starting ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");
  */
  Serial.print("Setup finalizado.");
}

void loop()
{

}

void loop1()
{
  gpsencoding();
}

// Programação Multicore
// https://arduino-pico.readthedocs.io/en/latest/multicore.html
// Loop e Loop1 são loops em núcleos separados;
// Setup e Setup1 são setups separados;
// Setups ocorrem simultaneamente;