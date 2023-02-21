#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>

unsigned int t0, tf; // Timers
char tvel[10]; // String responsável por mostrar o valor da velocidade
char trpm[10]; // String responsável por mostrar o valor do RPM
int vel = 55, rpm = 2700; // Valores arbitrários de teste
bool CVT = true, reserva = false;
short comb = 0;
byte receivedData[5]; // Buffer de dados recebidos. Tamanho máximo de 32 bytes.

// Funções de inicialização do objeto u8g2 do display. Quando usando HW_SPI, apenas o SS precisa ser passado.

void WaitSerial(bool wait);

// I2C
int sdaPin = 20, sclPin = 21;

// LCD
int SCKPIN = 10, CSPIN = 13;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, SCKPIN, TXPIN, CSPIN);
//U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R2, 10);
//U8G2_ST7920_128X64_1_2ND_HW_SPI u8g2(U8G2_R0, 17);



// Setup dos leds do display
int ledVerde = 2, ledAmarelo = 1, ledVermelho = 0, ledCVT = 18;

enum nivel {
    VAZIO,
    MEDIO,
    CHEIO
};

void receiveEvent(int bytesReceived);

void setup(void) 
{ 
  pinMode(ledVermelho,OUTPUT);
  pinMode(ledAmarelo,OUTPUT);
  pinMode(ledVerde,OUTPUT);

  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledAmarelo, HIGH);
  digitalWrite(ledVerde, HIGH);

  WaitSerial(false);
  t0 = tf = millis();
  Wire.setSDA(sdaPin);
  Wire.setSCL(sclPin);
  
  /*
  SPI1.setRX(RXPIN);
  SPI1.setTX(TXPIN);
  SPI1.setSCK(SCKPIN);
  SPI1.setCS(CSPIN);
  SPI1.begin(true);
  */
  
  Serial.begin(9600);
  u8g2.begin();
  
  Wire.begin(9);
  Wire.onReceive(receiveEvent); // Evento -> chama a função receiveEvent quando recebe uma transmissão pelo i2c
  
  // Converte os valores de int para char e insere os chars nas strings declaradas no início.
  itoa(vel/10, &tvel[0], 10);
  itoa(vel%10, &tvel[1], 10);
  itoa(rpm/1000, &trpm[0], 10);
  itoa((rpm/100)%10, &trpm[1], 10);
  itoa((rpm%100)/10, &trpm[2], 10);
  itoa(rpm%10, &trpm[3], 10);
  delay(500);

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);
  
  Serial.println("Funcionando aqui");
}

void UpdateDisplay() {
  u8g2.firstPage();
  do {
    bool warning = false;
    u8g2.setDrawColor(1);
    //######### CONTEUDOS DO DISPLAY #########

    //######### RPM #########
    u8g2.setFont(u8g2_font_lubB19_te);
    u8g2.drawButtonUTF8(2, 22 , U8G2_BTN_INV, 128, 2, 1, trpm);

    //######### VELOCIDADE #########
    u8g2.setFont(u8g2_font_lubB12_te);
    u8g2.drawButtonUTF8(2, 41 , U8G2_BTN_INV|U8G2_BTN_BW2, 32, 0, 0, tvel);

    u8g2.drawTriangle(36,46, 36,28, 54,28);

    //######### NIVEL DE COMBUSTIVEL BAIXO #########
    if (reserva){
      u8g2.setFont(u8g2_font_t0_11b_te);
      u8g2.drawButtonUTF8(100, 62, U8G2_BTN_INV|U8G2_BTN_BW1, 0, 0, 0, "!COMB");
      warning = true;
    }

    //######### TEMPERATURA CVT ALTA #########
   if (CVT){
      u8g2.setFont(u8g2_font_t0_11b_te);
      u8g2.drawButtonUTF8(100, 50, U8G2_BTN_INV|U8G2_BTN_BW1, 0, 0, 0, "!CVT");
      warning = true;
    }

    //######### INDICADOR DE ATENÇÃO #########
    if (warning){
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_streamline_interface_essential_circle_triangle_t);
      u8g2.drawGlyph(100,24, 0x34);
    }
      

  } while (u8g2.nextPage());
  setarCombustivel(comb);
  if (CVT) digitalWrite(ledCVT, HIGH);
  else digitalWrite(ledCVT, LOW);
  
}

void receiveEvent(int bytesReceived) {  // É requisito que essas funções de evento tenham um parâmetro int.
  int b = 0; // Contador de bytes recebidos. Útil pra testar ou limitar a transmissão.
  while(Wire.available()) {
    receivedData[b] = Wire.read();
    Serial.print("byte ");Serial.print(b + " ");Serial.println(receivedData[b]);
    b++;
  }
   // Como recebemos em bytes e int são data types de 2 bytes, precisamos transformar o byte mais alto em int e movê-lo para a esquerda. Um byte são 8 bits.
   // Depois, recebemos o byte mais baixo.
  vel = (int)receivedData[0] << 8 | (int)receivedData[1]; // Transforma byte receivedData[0] em int e o move 8 bits para a esquerda, e depois transforma e recebe o byte receivedData[1].
  rpm = (int)receivedData[2] << 8 | (int)receivedData[3];
  CVT = receivedData[4] >> 2;
  comb = receivedData[4] & 0x03;

  // Converte os valores de int para char e insere os chars nas strings declaradas no início.
  itoa(vel/10, &tvel[0], 10);
  itoa(vel%10, &tvel[1], 10);
  itoa(rpm/1000, &trpm[0], 10);
  itoa((rpm/100)%10, &trpm[1], 10);
  itoa((rpm%100)/10, &trpm[2], 10);
  itoa(rpm%10, &trpm[3], 10);

  Serial.print("Recebido. Vel: ");Serial.println(tvel);
  Serial.print("Recebido. RPM: ");Serial.println(trpm);

}

void setarCombustivel(int nivel)
{
    if (nivel == CHEIO)
    {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledAmarelo, LOW);
        digitalWrite(ledVermelho, LOW);
        reserva = false;

    }
    else if (nivel == MEDIO)
    {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarelo, HIGH);
        digitalWrite(ledVermelho, LOW);
        reserva = false;
    }
    else // VAZIO
    {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarelo, LOW);
        digitalWrite(ledVermelho, HIGH);
        reserva = true;
    }
}

void loop(void) {
    int test = millis();
    
// REMOVER, PARTE SOMENTE PARA TESTE #####################################    
    rpm   = random(4500);
    vel   = random(42);
    comb  = random(3);
    itoa(vel/10, &tvel[0], 10);
    itoa(vel%10, &tvel[1], 10);
    itoa(rpm/1000, &trpm[0], 10);
    itoa((rpm/100)%10, &trpm[1], 10);
    itoa((rpm%100)/10, &trpm[2], 10);
    itoa(rpm%10, &trpm[3], 10);
///////////////////////////////////////////////////////////////////////////
    UpdateDisplay();
    int timetest = millis() - test;
    
    Serial.print("\nTempo Trocando:");Serial.println(timetest);
    Serial.print("vel:");Serial.println(vel);
}

void WaitSerial(bool wait)
{
  if (wait)
  {
    while (!Serial) {
      yield();
    }
    delay(100);

    Serial.println(F("Type any character to start"));
    while (!Serial.available()) {
      yield();
    }
  }
  return;
}
