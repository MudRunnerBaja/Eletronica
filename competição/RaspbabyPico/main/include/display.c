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
int tabela_digitos[10][8] =
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
        {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LB}, // 8
        {0, 0, 0, 0, 1, 0, 0, LB}  // 9
};
int tabela_pinos[8][8] =
    {
        {1, 0, 0, 0, 0, 0, 0, 0}, // A
        {0, 1, 0, 0, 0, 0, 0, 0}, // B
        {0, 0, 1, 0, 0, 0, 0, 0}, // C
        {0, 0, 0, 1, 0, 0, 0, 0}, // D
        {0, 0, 0, 0, 1, 0, 0, 0}, // E
        {0, 0, 0, 0, 0, 1, 0, 0}, // F
        {0, 0, 0, 0, 0, 0, 1, 0}, // G
        {0, 0, 0, 0, 0, 0, 0, 1} // LED
};

int regis[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setLedBox()
{ // Chamar função pelo interrupt do led de chamada
    LB = !LB;
    for (int i = 0; i < 10; i++)
    {
        tabela_digitos[i][7] = LB;
    }
}

// Apaga os displays de 7 segmentos
void limparRegistrador(){

    digitalWrite(STCP, LOW);
    for(int i = 7; i >= 0; i--)
    {
        if (i == 7) digitalWrite(DS, LB);
        else digitalWrite(DS, HIGH);
        
        digitalWrite(SHCP, HIGH);
        delayMicroseconds(10);
        digitalWrite(SHCP, LOW);
    }
    digitalWrite(STCP, HIGH);
}

// Atualiza os displays e segmentos
void atualizarDisplay(int display, int valor)
{
    valor = valor > 9 ? 9 : valor;

    // Acende o display correto e apaga os demais
    for (int i = 0; i < 4; i++)
    {
        if (i == display)
            digitalWrite(displays[display], HIGH);
        else
            digitalWrite(displays[i], LOW);
    }

    for(int i = 0; i < 8; i++) {
        regis[i] = tabela_pinos[i][i];
    }

    // Armazena os bits no registrador
    digitalWrite(STCP, LOW);
    for(int i = 7; i >=  0; i--)
    {
        int val = regis[i];
        delayMicroseconds(5);
        digitalWrite(DS, val);

        digitalWrite(SHCP, LOW);
        delayMicroseconds(5);
        digitalWrite(SHCP, LOW);
    }
    digitalWrite(STCP, HIGH);
}

void setupDisplay()
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        pinMode(displays[i], OUTPUT);
        digitalWrite(displays[i], LOW);
    }

    pinMode(DS,OUTPUT);
    pinMode(STCP,OUTPUT);
    pinMode(SHCP,OUTPUT);

    limparRegistrador();
    delay(400);
}

float cont = 0;
float vel = 0;
float rpm = 0;

void mostraDados()
{
//   vel += 0.01;
//   rpm += 1;
//
//   // int vel = int(getVel());
//   // int rpm = getRpm();
//
//   valores[0] = int(rpm / 1000); // RPM_Milhar
//   valores[1] = (int(rpm) % 1000 / 100); // RPM_Centena
//   valores[2] = int(vel / 10); // Vel_Dezena
//   valores[3] = (int(vel) % 10); // Vel_Unidade
//
//   for (int i = 0; i < 4; i++)
//   {
//       Serial.println("\nMostrando dados...");
//       atualizarDisplay(i, 8);
//       delay(1);
//   }
//    atualizarDisplay(0, 1);
    int val = int(cont) % 8;
    atualizarDisplay(1, val);
    Serial.println(val);
    delay(10);
    cont += 0.005;
}