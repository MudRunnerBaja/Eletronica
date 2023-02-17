/*
      Implementação da contagem de rpm da movida
*/

#include <declarations.h>

void contador(); // Contador de pulsos da motriz

void TuningSetup()
{
  attachInterrupt(digitalPinToInterrupt(HALL_MOVIDA), contador, RISING);

  Serial.println("CVT Tuning inicializado");
}

int setRpmMovida()
{ 
  rpmMovida = (pulsos * minuto) / pulsos_por_volta_mvd;
  pulsos = 0;
  return rpmMovida;
}

int getRpmMovida()
{
  return rpmMovida;
}

void contador(){                             //Contador de pulsos da motriz
    pulsos++;
}