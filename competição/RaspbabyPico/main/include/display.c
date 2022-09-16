/*
    Implementação displays de 7 segmentos 
    e do [futuro] led de chamada do box
*/

int DS   = 5; // (SER) Pino Serial, saída do pico e entrada do registrador data
int STCP  = 6; // (RCLK) Protege e permite atualizações na saída do registrador de deslocamento (74HC595) latch
int SHCP = 7; // (SRCLK) Cada "pulso" capta o sinal em DS e armazena na memória do primeiro pino (desloca a memória dos demais pinos) clock

/* Pinos e valores display enables,
    High acende, low apaaga

                {RPM_Mil, RPM_Cent, Vel_Dez, Vel_Un} */
int displays[4] = {14, 15, 16, 17};
int valores[4] =  {0, 0, 0, 0};

int LB = LOW;
int tabela_digitos[11][8] =
{ /*
    Os segmentos são anodo comum:
    Acende no low, apaga no high

    {A, B, C, D, E, F, G, LedBox}  */
  {0, 0, 0, 0, 0, 0, 1, LB}, // 0
  {1, 0, 0, 1, 1, 1, 1, LB}, // 1
  {0, 0, 1, 0, 0, 1, 0, LB}, // 2
  {0, 0, 0, 0, 1, 1, 0, LB}, // 3
  {1, 0, 0, 1, 1, 0, 0, LB}, // 4
  {0, 1, 0, 0, 1, 0, 0, LB}, // 5
  {0, 1, 0, 0, 0, 0, 0, LB}, // 6
  {0, 0, 0, 1, 1, 1, 1, LB}, // 7
  {0, 0, 0, 0, 0, 0, 0, LB}, // 8
  {0, 0, 0, 0, 1, 0, 0, LB}, // 9
  {1, 1, 1, 1, 1, 1, 1, LB}  // Clear
};

void setLedBox()
{ // Chamar função pelo interrupt do led de chamada
  LB = !LB;
  for (int i = 0; i < 10; i++)
  {
    tabela_digitos[i][7] = LB;
  }
}

void escreverRegistrador(int valor)
{ 
  for (int i = 7; i >= 0; i--) {
    int val = tabela_digitos[valor][i];
    digitalWrite(DS, val);
    delayMicroseconds(3);

    digitalWrite(SHCP, HIGH);
    delayMicroseconds(3);
    digitalWrite(SHCP, LOW);
    delayMicroseconds(3);
  }
  
  digitalWrite(STCP, HIGH);
  delayMicroseconds(3);
  digitalWrite(STCP, LOW);
  delayMicroseconds(3);
}

// Apaga os displays de 7 segmentos
void limparRegistrador()
{
  escreverRegistrador(10);
}

// Atualiza os displays e segmentos
void escolherDisplay(int display)
{
  // Acende o display correto e apaga os demais
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(displays[i], LOW);
  }
  Serial.print("Display escolhido: "); Serial.println(display);
  digitalWrite(displays[display], HIGH);
}

void displaySetup()
{
  for (int i = 0; i < 4; i++)
  {
    pinMode(displays[i], OUTPUT);
    digitalWrite(displays[i], LOW);
  }
  pinMode(DS, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  digitalWrite(STCP, LOW);
  digitalWrite(SHCP, LOW);
  digitalWrite(DS, LOW);
}

float cont = 0;
float vel = 0;
float rpm = 0;

void mostraDados()
{
    // Teste
   vel += 0.01;
   rpm += 10;

   // int vel = int(getVel());
   // int rpm = getRpm();

   valores[0] = int(rpm / 1000); // RPM_Milhar
   valores[1] = (int(rpm) % 1000 / 100); // RPM_Centena
   valores[2] = int(vel / 10); // Vel_Dezena
   valores[3] = (int(vel) % 10); // Vel_Unidade

   for (int i = 0; i < 4; i++)
   {
    if (valores[0] % 2 == 0) setLedBox();

    Serial.println("\nMostrando dados...");
    Serial.print("Valor: "); Serial.println(valores[i]);
    escolherDisplay(i);
    escreverRegistrador(valores[i]);
    delay(1);
   }
}