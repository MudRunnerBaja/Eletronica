#include<SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

#define button 6

bool inicio = false, trintaMetros = false;
float tempoInicial, tempoTotal, tempo30Metros;

void setup() {

  // put your setup code here, to run once:

  pinMode(button, INPUT_PULLUP);
  mySerial.begin(38400);
  mySerial.println("qualquermerda");

  Serial.begin(9600);

}



void loop() {

  if((!digitalRead(button)) and (!inicio)){
    mySerial.println("Iniciado o teste");
    tempoInicial = millis();
    inicio = true;
  }
  if(inicio){
    if((Serial.read()=='1') and (!trintaMetros)){
      tempo30Metros = millis() - tempoInicial;
      mySerial.println("30 metros alcancados!");
      mySerial.print("Tempo percorrido:");
      mySerial.println(tempo30Metros/1000);
      trintaMetros = true;
     }
    if((trintaMetros) and (!digitalRead(button))){
      tempoTotal = millis() - tempoInicial;
      mySerial.println("Fim do teste");
      mySerial.print("Tempo total:");
      mySerial.println(tempoTotal/1000);
      trintaMetros = false; inicio = false;
      delay(500);
      } 
  } 
}
