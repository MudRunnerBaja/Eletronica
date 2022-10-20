//display 7 segmentos
//Define os pinos de saida
int SER   = 5; // Serial
int RCLK  = 7; // Clock
int SRCLK = 6; // Latch

// Array de limpeza
int regis[] = {1,1,1,1,1,1,1,1};

int displays[] = {14, 15, 16, 17}; // Pinos enables
int LB = HIGH;

int tabela_7seg[10][8] =
    {
       //LB A B C D E F G
        {LB, 0, 0, 0, 0, 0, 0, 1}, // 0
        {LB, 1, 0, 0, 1, 1, 1, 1}, // 1
        {LB, 0, 0, 1, 0, 0, 1, 0}, // 2
        {LB, 0, 0, 0, 0, 1, 1, 0}, // 3
        {LB, 1, 0, 0, 1, 1, 0, 0}, // 4
        {LB, 0, 1, 0, 0, 1, 0, 0}, // 5
        {LB, 0, 1, 0, 0, 0, 0, 0}, // 6
        {LB, 0, 0, 0, 1, 1, 1, 1}, // 7
        {LB, 0, 0, 0, 0, 0, 0, 0}, // 8
        {LB, 0, 0, 0, 0, 1, 0, 0}  // 9
};

// Escolhe o display a ser ativado, pelo contaDisplay
void escolherDisplay(int contador)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (i == contador)
            digitalWrite(displays[contador], HIGH);
        else
            digitalWrite(displays[i], LOW);
    }
}

// Acende os segmentos em cada display
void converteValorDisplay(int valor)
{
  valor = valor > 9 ? 9 : valor;
  
  // "SRCLK High" permite a atualização do setup de pinos,
  // Iniciando a sequencia no "clock" 0
  digitalWrite(SRCLK, HIGH);

  // Limpa o setup de pinos, apagando todos os segmentos
  for(int i=7; i >= 0; i--){

    // Funcionamento similar ao shiftOut() do arduino.
    // Cada pulso em RCLK atualiza o contador dos pinos
    // A sequeêcia é do final do array para o início
    digitalWrite(RCLK, HIGH);

    int PIN = regis[i];
    digitalWrite(SER, PIN);

    digitalWrite(RCLK, LOW);
  }

  digitalWrite(SRCLK, LOW);


  digitalWrite(SRCLK, HIGH);

  // Usa a tabela para acender os segmentos certos
  for(int i=7; i >= 0; i--){

    digitalWrite(RCLK, HIGH);
    
    if (i == 0) tabela_7seg[valor][i] = LB;

    int PIN = tabela_7seg[valor][i];
    digitalWrite(SER, PIN);

    digitalWrite(RCLK, LOW);
  }
  
  // "SRCLK Low" conclui a atualização e indica que o sinal 
  // pode ser enviado com os pinos atualizados
  digitalWrite(SRCLK, LOW);
}

void setup(){
  //configurando pinos como saida
  pinMode(SER,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SRCLK,OUTPUT);
}

float vtest = 00;
int rpmtest = 00;

void mostraDados()
{
    int contaDisplay = 0;
    // float vel = getVelValue();
    // int rpm = getRpmValue();

    float vel = vtest;
    int rpm = rpmtest;

    // RPM
    int milhar = rpm / 1000;
    converteValorDisplay(milhar);
    escolherDisplay(contaDisplay);
    contaDisplay++;
    delay(5);
    int centesimo = (rpm % 1000) / 100;
    converteValorDisplay(centesimo);
    escolherDisplay(contaDisplay);
    contaDisplay++;
    delay(5);

    // Velocidade
    int decimal = vel / 10;
    converteValorDisplay(decimal);
    escolherDisplay(contaDisplay);
    contaDisplay++;
    delay(5);

    int unitario = int(vel) % 10;
    converteValorDisplay(unitario);
    escolherDisplay(contaDisplay);
    contaDisplay++;
    delay(5);

  vtest += 0.02;
  rpmtest += 1;
  if (rpmtest % 100 == 0) LB = !LB;
}

void loop(){
  mostraDados();
}