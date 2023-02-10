# 1 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino"
# 2 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2
# 3 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2



# 7 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2
# 8 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2
# 9 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2
# 10 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2
# 11 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2
# 12 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\main.ino" 2

bool setupCompleto = false;




RPI_PICO_Timer Core0Timer0(0);
RPI_PICO_Timer Core1Timer1(1);

// Interrupt callback functions Core0
bool UpdateTimer(struct repeating_timer *t)
{
  Serial.println("Nucleo 0 - Iniciando interrupcao");
  UpdateData();
  Serial.println("Nucleo 0 - Dados Atualizados");
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
  // Escrita em cartao SD
  writeData(vel, rpm, tempCvt, comb);
  Serial.println("Nucleo 1 - Dados escritos");
  return true;
}

void setup()
{
  Serial.begin(9600);

      // Esperando pela resposta do monitor serial. 
      // Comentar quando for para o carro.
  while (!Serial) {
    yield();
  }
  delay(1000);

  Serial.println((reinterpret_cast<const __FlashStringHelper *>(("Type any character to start"))));
  while (!Serial.available()) {
    yield();
  }

  Serial.println("Iniciando setup...");

  DisplaySetup();
  setupGps();
  combSetup();
  cvtSetup();
  rpmSetup();
  sdcardSetup();

  pinMode((25u), OUTPUT);
  digitalWrite((25u), HIGH);

  delay(1000);
  digitalWrite(ledTempCvt, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  // Interval in unsigned long microseconds
  if (Core0Timer0.attachInterruptInterval(1000 * 1000, UpdateTimer))
    Serial.println("Starting Core0Timer0 OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set Core0Timer0. Select another freq. or timer");

  setupCompleto = true;
  Serial.print("Setup core0 finalizado.");
}

void setup1()
{
  while (!setupCompleto)
  {
    delay(1);
  }

  delay(50);

  if (Core1Timer1.attachInterruptInterval(1000 * 1000, WriteSD))
    Serial.println("Starting Core1Timer1 OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set UpdateTimer. Select another freq. or timer");

  Serial.print("Setup core1 finalizado.");
}

void loop()
{
 updateGps();

}

void loop1()
{

}

// Programação Multicore
// https://arduino-pico.readthedocs.io/en/latest/multicore.html
// Loop e Loop1 são loops em núcleos separados;
// Setup e Setup1 são setups separados;
// Setups ocorrem simultaneamente;
