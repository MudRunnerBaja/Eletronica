#line 1 "D:\\lucas\\Documents\\GitHub\\Eletronica\\Codigos\\Competição\\RaspbabyPico\\main\\include\\74hcCodigo.c"
//display 7 segmentos
//Define os pinos de saida
int DS   = 5; // (SER) Pino Serial, saída do pico e entrada do registrador
int STCP  = 6; // (RCLK) Cada "pulso" capta o sinal em DS e armazena na memória do primeiro pino (desloca a memória dos demais pinos)
int SHCP = 7; // (SRCLK) Protege e permite atualizações na saída do registrador de deslocamento (74HC595)

int pinoTemp = 28;

// Quando encadeando os registradores, o pino SER deve
// ser conectado apenas ao primeiro registrador. Já os
// demais pinos (RCLK e SRCLK) devem ser conectados
// também aos demais registradores. Também devem ser
// conectados Vin e GND.

// Quantidade de registradores (atualizar)
#define number_of_74hc595s 2

// Total de pinos de output (Não atualizar)
#define numOfRegisterPins number_of_74hc595s * 8

int numDisplays = 4; // numero de displays

// Array dos pinos dos registradores
int regis[numOfRegisterPins];

// Estado do led de chamada do box
int LB = HIGH; 

int tabela_7seg[10][8] =
    {
       // A B C D E F G LED BOX
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
int teste[4][8] = 
{
  {1, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0}
};

void regis_init()
{
  for(int i = 0; i < numOfRegisterPins; i++)
  {
    regis[i] = HIGH;
  }
}

// Escolhe o display a ser ativado, pelo contaDisplay
void escolherDisplay(int contador)
{
  int x = 8 + contador;
  for (int i = 8; i < numOfRegisterPins; i++)
  {
    if (i == x)
      regis[i] = LOW;
    else
      regis[i] = HIGH;
  }
}

// Atualiza todos os pinos do registrador individualmenteSet and display registers
// Obs: Não o array, mas os pinos de fato.
void writeRegisters(int display){

  digitalWrite(RCLK, LOW);

  for(int i = 7; i >=  0; i--){
    digitalWrite(SRCLK, LOW);
    
    int val = teste[display][i];

    digitalWrite(SER, val);
    
    digitalWrite(SRCLK, HIGH);
  }

  for(int i = 7; i >=  0; i--){
    digitalWrite(SRCLK, LOW);
    
    int val = regis[i];

    digitalWrite(SER, val);
    
    digitalWrite(SRCLK, HIGH);
  }
  digitalWrite(RCLK, HIGH);
}

// Limpa todo o array de pinos para HIGH
void limparPinos(){
  digitalWrite(RCLK, LOW);

  for(int i = 15; i >= 0; i--){
    digitalWrite(SRCLK, LOW);

    int val = HIGH;

    if (i == 7) digitalWrite(SER, LB);

    else digitalWrite(SER, val);

    digitalWrite(SRCLK, HIGH);
  }
  
  digitalWrite(RCLK, HIGH);
}
// Acende os segmentos em cada display
void converteValorDisplay(int valor, int display)
{
  valor = valor > 9 ? 9 : valor;

  // Usa a tabela para acender os segmentos certos
  tabela_7seg[valor][7] = LB;

  for (int i = 0; i < 8; i++)
  {
    regis[i] = tabela_7seg[valor][i];
  }

  writeRegisters(display);
}

void ledChamada()
{
  LB = !LB;
}

void setup(){
  //configurando pinos como saida
  pinMode(SER,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(pinoTemp,INPUT);

  regis_init();
  limparPinos();
  delay(500);
}

float vtest = 00;
int rpmtest = 0000;

void mostraDados()
{
    int contaDisplay = 0;
    // float vel = getVelValue();
    // int rpm = getRpmValue();

    float vel = vtest;
    int rpm = rpmtest;

    // RPM
    int milhar = rpm / 1000;
    // escolherDisplay(contaDisplay);
    converteValorDisplay(milhar, contaDisplay);
    contaDisplay++;
    delay(1);

    int centesimo = (rpm % 1000) / 100;
    // escolherDisplay(contaDisplay);
    converteValorDisplay(centesimo, contaDisplay);
    contaDisplay++;
    delay(1);

    // Velocidade
    int decimal = vel / 10;
    // escolherDisplay(contaDisplay);
    converteValorDisplay(decimal, contaDisplay);
    contaDisplay++;
    delay(1);

    int unitario = int(vel) % 10;
    // escolherDisplay(contaDisplay);
    converteValorDisplay(unitario, contaDisplay);
    contaDisplay++;
    delay(1);

  vtest += 0.01;
  rpmtest += 1;
  if (rpmtest % 100 == 0) LB = !LB;

  int tempRead = analogRead(pinoTemp);
  float celsius = 1 / (log(1 / (1023. / tempRead - 1)) / 3950 + 1.0 / 298.15) - 273.15;
  if (celsius > 60)
  {
    for (int i = 0; i < 4; i++)
    {
      teste[i][4] = HIGH;
    }
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      teste[i][4] = LOW;
    }
  }
}

void loop(){
  mostraDados();
}