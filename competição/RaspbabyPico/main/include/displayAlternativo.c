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
int tabela_digitos[11][7] =
{ /*
    Os segmentos são anodo comum:
    Acende no low, apaga no high

    {A, B, C, D, E, F, G}  */
  {0, 0, 0, 0, 0, 0, 1}, // 0
  {1, 0, 0, 1, 1, 1, 1}, // 1
  {0, 0, 1, 0, 0, 1, 0}, // 2
  {0, 0, 0, 0, 1, 1, 0}, // 3
  {1, 0, 0, 1, 1, 0, 0}, // 4
  {0, 1, 0, 0, 1, 0, 0}, // 5
  {0, 1, 0, 0, 0, 0, 0}, // 6
  {0, 0, 0, 1, 1, 1, 1}, // 7
  {0, 0, 0, 0, 0, 0, 0}, // 8
  {0, 0, 0, 0, 1, 0, 0}, // 9
  {1, 1, 1, 1, 1, 1, 1}  // Clear
};

int tabela_segmentos[8][7] =
{ /*
    Os segmentos são anodo comum:
    Acende no low, apaga no high
  */
  {0, 1, 1, 1, 1, 1, 1}, // A 0
  {1, 0, 1, 1, 1, 1, 1}, // B 1
  {1, 1, 0, 1, 1, 1, 1}, // C 2
  {1, 1, 1, 0, 1, 1, 1}, // D 3
  {1, 1, 1, 1, 0, 1, 1}, // E 4
  {1, 1, 1, 1, 1, 0, 1}, // F 5
  {1, 1, 1, 1, 1, 1, 0}, // G 6
  {1, 1, 1, 1, 1, 1, 1}  // Clear 7
};


void setLedBox()
{ // Chamar função pelo interrupt do led de chamada
  LB = !LB;
}

void escreverRegistrador(int valor)
{ 
  if (valor > 9) valor = 9;

  for (int i = 6; i >= 0; i--) {

    if (tabela_digitos[valor][i] == 0)
    {
      digitalWrite(DS, LB);
      delayMicroseconds(3);

      digitalWrite(SHCP, HIGH);
      delayMicroseconds(3);
        
      digitalWrite(SHCP, LOW);
      delayMicroseconds(3);

      for (int j = 6; j >= 0; j--)
      {
        int val = tabela_segmentos[i][j];
        
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

      delay(1); // Delay de permanência do segmento. Afeta o brilho do segmento
    }
  }
  
  
}

// Apaga os displays de 7 segmentos
void limparRegistrador()
{
  digitalWrite(DS, LB);
  delayMicroseconds(3);

  digitalWrite(SHCP, HIGH);
  delayMicroseconds(3);
        
  digitalWrite(SHCP, LOW);
  delayMicroseconds(3);

  for (int j = 6; j >= 0; j--)
  {
    int val = tabela_segmentos[7][j];
       
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

void setupDisplay()
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
    // Ciclos de 16ms representam uma frequência de 62Hz
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
    Serial.println("\nMostrando dados...");
    Serial.print("Valor: "); Serial.println(valores[i]);

    escolherDisplay(i);
    escreverRegistrador(valores[i]);
    limparRegistrador(); // Evita ruídos

    delay(5); // Delay para trocar de display
   }
}