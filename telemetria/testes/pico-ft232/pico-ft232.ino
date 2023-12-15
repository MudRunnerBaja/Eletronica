
// INCLUSÃO DE BIBLIOTECAS
#include <SoftwareSerial.h>

// DEFINIÇÕES
#define msg1 "OK"
#define msg2 "ajuda"

// DECLARAÇÃO DE FUNÇÕES
void enviaMensagem();
String recebeMensagem();
String createTestCsv();

// DECLARAÇÃO DE VARIÁVEIS
int funcao = 0;



void setup() {
  Serial.begin(9600);

  Serial1.setRX(1);
  Serial1.setTX(0);
  Serial1.begin(9600);

  delay(2000);
  Serial.println("Fim Setup");
}

void loop() {
  enviaMensagem();
  Serial.print("Recebido:");
  Serial.println(recebeMensagem());
  delay(250);
}

void enviaMensagem() {
  Serial1.println(createTestCsv());
  delay(250);
}

String recebeMensagem() {
  return Serial1.readString();
}

String createTestCsv() {
  int rpm = random(4800);
  float tCvt  = random(100, 10000) / 100.0; 
  float vel  = random(100, 3750) / 100.0; 
  short comb = random(1, 3);
  int mvd = random(4800);

  String csvHeader = String("rpm,tCvt,vel,comb,mvd\n");
  String data = String(rpm);
  data = String(data + ",");
  data = String(data + tCvt);
  data = String(data + ",");
  data = String(data + vel);
  data = String(data + ",");
  data = String(data + comb);
  data = String(data + ",");
  data = String(data + mvd);
  data = String(csvHeader + data);

  char* toSend;

  data.toCharArray(toSend, 128);

  Serial.print("Data:");
  Serial.println(data);

  Serial.print("charArray:");
  Serial.print(toSend);

  return data;
}