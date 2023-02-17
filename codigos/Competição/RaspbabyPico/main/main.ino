#include <declarations.h>

void WaitSerial(bool wait);
bool UpdateTimer(struct repeating_timer *t);
bool WriteSD(struct repeating_timer *t);

RPI_PICO_Timer Core0Timer0(0);
RPI_PICO_Timer Core1Timer1(1);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  
  // Esperar pela resposta do monitor serial?
  WaitSerial(false);
  
  Serial.println("Iniciando setup...");

  DisplaySetup();
  Serial.println("DisplaySetup ok");
  setupGps();
  Serial.println("GPS ok");
  combSetup();
  Serial.println("comb ok");
  rpmSetup();
  Serial.println("rpm ok");
  sdcardSetup();
  Serial.println("sdcard ok");
  TuningSetup();
  Serial.println("cvt tuning ok");
  
  delay(1000);

  // Interval in unsigned long microseconds
  if (Core0Timer0.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, UpdateTimer))
    Serial.println("Core0Timer0 OK. Timer de: " + TIMER_INTERVAL_MS);
  else
    Serial.println("Falha no Core0Timer0. Sem timer de update de dados.");

  setupCompleto = true;
  Serial.print("Setup core0 finalizado.");
}

void setup1()
{
  while (!setupCompleto)
  {
    delay(1);
  }

  delay(5);
  
  if (Core1Timer1.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, WriteSD))
    Serial.println("Core1Timer1 OK. Timer de: " + TIMER_INTERVAL_MS);
  else
    Serial.println("Falha no Core1Timer1. Sem timer de escrita no SD");
  
  Serial.print("Setup core1 finalizado.");
  digitalWrite(LED_BUILTIN, HIGH);
  tempoInicial = millis();
}

void loop()
{
 updateGps();
 digitalWrite(LED_BUILTIN, HIGH);
}

void loop1()
{

}

// Programação Multicore
// https://arduino-pico.readthedocs.io/en/latest/multicore.html
// Loop e Loop1 são loops em núcleos separados;
// Setup e Setup1 são setups separados;
// Setups ocorrem simultaneamente;

// Esperar pelo serial ou não (testar setup)
void WaitSerial(bool wait)
{
  if (wait)
  {
    while (!Serial) {
      yield();
    }
    delay(100);

    Serial.println(F("Type any character to start"));
    while (!Serial.available()) {
      yield();
    }
  }
  return;
}

// Interrupt callback functions Core0
bool UpdateTimer(struct repeating_timer *t)
{
  Serial.println("Nucleo 0 - Iniciando interrupcao");
  UpdateData();
  Serial.println("Nucleo 0 - Dados Atualizados");
  tempoTotal = ((millis() - tempoInicial) / 100) * 100;
  Serial.print("Tempo total de execução: ");Serial.println(tempoTotal);
  return true;
}

// Interrupt callback functions Core1
bool WriteSD(struct repeating_timer *t)
{
  Serial.println("Nucleo 1 - Iniciando interrupcao");
  float vel = gpsSpdFloat();
  int rpm = getRpm();
  float tempCvt = getTempCvt();
  int comb = getNivelComb();
  int mvd = getRpmMovida();

  // Escrita em cartao SD
  writeData(vel, rpm, tempCvt, comb, mvd);
  Serial.println("Nucleo 1 - Dados escritos");
  return true;
}
