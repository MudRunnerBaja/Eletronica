/*
      Implementação da contagem de rpm da movida
*/
#ifndef CVT_TUNING
#define CVT_TUNING


#define HALL_MOVIDA 22 // PINO SENSOR HALL MOVIDA (TORQUE)

int rpmMovida; int pulsos = 0;
unsigned int pulsos_por_volta_mvd = 1; // Quantidade de imas na polia

void contador(); // Contador de pulsos da motriz

void TuningSetup()
{
  attachInterrupt(digitalPinToInterrupt(HALL_MOVIDA), contador, RISING);

  Serial.println("CVT Tuning inicializado");
}

int setRpmMovida()
{ 
  rpmMovida = (pulsos * MINUTO) / pulsos_por_volta_mvd;
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
#endif