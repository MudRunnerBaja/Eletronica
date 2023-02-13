/*
      Implementação da contagem de rpm da movida
*/
int rpmMovida;
int hallMovida = 22;
int pulsos = 0;
unsigned int pulsos_por_volta_mvd = 1; // Quantidade de imas na polia

void contador(); // Contador de pulsos da motriz

void TuningSetup()
{
  attachInterrupt(digitalPinToInterrupt(hallMovida), contador, RISING);

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