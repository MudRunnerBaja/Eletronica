/*
    Implementação displays de 7 segmentos 
    e do [futuro] led de chamada do box
*/

int DS   = 5; // (SER) Pino Serial, saída do pico e entrada do registrador
int STCP  = 6; // (RCLK) Cada "pulso" capta o sinal em DS e armazena na memória do primeiro pino (desloca a memória dos demais pinos)
int SHCP = 7; // (SRCLK) Protege e permite atualizações na saída do registrador de deslocamento (74HC595)

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
        {0, 0, 0, 0, 0, 0, 0, LB}, // 8
        {0, 0, 0, 0, 1, 0, 0, LB}  // 9
};

void setLedBox()
{ // Chamar função pelo interrupt do led de chamada
    LB = !LB;
    for (int i = 0; i < 10; i++)
    {
        tabela_digitos[i][7] = LB;
    }
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

    // Armazena os bits no registrador
    digitalWrite(STCP, LOW);

    for(int i = 7; i >=  0; i--)
    {
        digitalWrite(SHCP, LOW);
        int val = tabela_digitos[valor][i];
        digitalWrite(DS, val);
        digitalWrite(SHCP, HIGH);
    }
    digitalWrite(STCP, HIGH);
}

void mostraDados()
{
    int vel = int(getVel());
    int rpm = getRpm();

    valores[0] = rpm / 1000; // RPM_Milhar
    valores[1] = (rpm % 1000) / 100; // RPM_Centena
    valores[2] = vel / 10; // Vel_Dezena
    valores[3] = vel % 10; // Vel_Unidade

    for (int i = 0; i < 4; i++)
    {
        atualizarDisplay(displays[i], valores[i]);
        i++;
        delay(1);
    }
}

// Apaga os displays de 7 segmentos
void limparRegistrador(){

    digitalWrite(STCP, LOW);

    for(int i = 7; i >= 0; i--)
    {
         digitalWrite(SHCP, LOW);
         if (i == 7) digitalWrite(DS, LB);
         else digitalWrite(DS, HIGH);
         digitalWrite(SHCP, HIGH);
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
}