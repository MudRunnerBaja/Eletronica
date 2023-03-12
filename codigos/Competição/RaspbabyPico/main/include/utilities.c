#ifndef UTILITIES
#define UTILITIES


void WaitSerial(bool wait) // Esperar pelo serial ou não (testar setup)
{
  if (wait) // Se esperar == true
  {
    while (!Serial) { // Esperar o serial (abrir comunicação com o pc)
      yield();
    }
    delay(100);

    Serial.println(F("Type any character to start")); // Após inicializada a comunicação, aguardar um input do serial
    while (!Serial.available()) { // Enquanto não houver input, esperar
      yield();
    }
  }
  return;
}

#endif