/*
      Implementação da contagem de rpm da movida
*/
int rpmMovida;
int hallMovida = 22;
int cfg;
volatile byte pulsos = 0;
unsigned int pulsos_por_volta_mvd = 4; // Quantidade de imas na polia
unsigned int minuto = 60 * (1000 / TIMER_INTERVAL_MS); // 60000 ms (1 minuto) em funcao do timer da interrupcao

// REFRESH RATE EM ms
const int refresh_rate = 250; //ms

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

void contador(){                             //Contador de pulsos da motriz
    pulsos++;
}