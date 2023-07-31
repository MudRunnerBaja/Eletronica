/*
  Microcontrolador: Raspberry Pi Pico
  Biblioteca arduino-pico de Earle Philhower
*/

#include <Wire.h>

int UnoLCD = 9; // ID do slave na comunicação I2C
int SDApin = 8; // Pino SDA I2C0
int SCLpin = 9; // Pino SCL I2C0

int counter = 0; // Contador para fins de teste
int testvel = 0; // Valores de teste para velocidade e RPM
int testrpm = 0;

byte data[4]; // Buffer para envio de dados. Tamanho máximo por transmissão de 32 bytes.

unsigned int tf, t0, t1; // Variaveis para timers

void setup() {
  // Setup para comunicação I2C pela biblioteca Wire - I2C0 para o Pico
  Wire.setSDA(SDApin);
  Wire.setSCL(SCLpin);
  Wire.begin();

  Serial.begin(9600);
  tf = t0 = t1 = millis();
  Serial.println("Setup Finalizado");
}

void loop() {
  tf = millis();
  if (tf - t1 >= 125) { // A cada 125ms

    testvel++;
    testrpm += 100;

    if (testvel > 99) { testvel = 0;}
    if (testrpm > 6000) { testrpm = 0;}

    Serial.print("\ntestvel: "); Serial.println(testvel);
    Serial.print("\ntestrpm: "); Serial.println(testrpm);
    t1 = millis();
  }

  if (tf - t0 >= 250){ // A cada 250ms
    unsigned int tmp = millis();

    data[0] = highByte(testvel);
    data[1] = lowByte(testvel);
    data[2] = highByte(testrpm);
    data[3] = lowByte(testrpm);
    
    Wire.beginTransmission(UnoLCD); // Inicia uma transmissão para o slave passado como parâmetro
    int c = Wire.write(data, 4); // Essa função possui vários formatos de parâmetros. 
          // Esse, em específico, usa um array (data) e o tamanho do array. A função retorna o número de bytes enviados.
    Wire.endTransmission(); // Finaliza a transmissão
    
    tmp = millis() - tmp;
    Serial.print(c); Serial.print(" bytes done in");Serial.println(tmp);
    t0 = millis();
  }
}
