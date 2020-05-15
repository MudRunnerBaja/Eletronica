#include<SoftwareSerial.h>
int sensor30;
int sensorfinal = 6;
int vel = 0;
int rpm = 0;
char data;
float tempoant = 0;
float tempoace = 0;
float tempofinal = 0;
float tempoinicial = 0;
bool contado30 = false;
bool contadoinicio = false;
bool inicio = true;
bool final = false;
bool lendorpm = false;

//Declarando as comunicações
SoftwareSerial ace(10, 11);
SoftwareSerial carro(8, 9);

void setup() {
  pinMode(sensorfinal, INPUT_PULLUP);

  ace.begin(9600);
  Serial.begin(9600);

}

void loop() {
  //Recebendo 30m sensor:
  ace.listen();
  while (ace.available()) {
    sensor30 = ace.read();
  }

  //Recebendo velocidade e rpm:
  carro.listen();
  while (carro.available()) {
    data = carro.read();
    if (data == '!' || lendorpm == true) {
      rpm = carro.read();
      lendorpm = true;
    }

    else {
      vel = carro.read();
    }
  }
  lendorpm = false;

  if (sensor30 == '@' && contado30 == false) {

    tempoace = millis();
    tempoant = millis();
    Serial.println("O carro acabou de passar aqui!\n");
    Serial.print("Tempo 30 metros: ");
    Serial.println(tempoace / 1000);
    contado30 = true;
  }

  // Código para passagem final:

  if (digitalRead(sensorfinal) == 0) {
    
    if (inicio) {
      tempoinicial = millis();
      inicio = false;
      Serial.println("Iniciado o teste");
    }

    if (contado30 == true && final == false) {
      tempofinal = millis() - tempoinicial;
      Serial.println("\nTeste finalizado!\n");
      Serial.print("Tempo final: ");
      Serial.println((tempofinal + tempoace) / 1000);
      final = true;
    }
  }
}
