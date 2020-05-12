#include<SoftwareSerial.h>
int sensor30;
int sensorfinal = 6;
int vel = 0;
int rpm = 0;
float tempoant = 0;
float tempoace = 0;
float tempofinal = 0;
float tempoinicial = 0;
bool contado30 = false;
bool contadoinicio = false;
bool inicio = true;
bool final = false;
bool recebevel = false;
bool receberpm = false;
bool mostrarvel = false;


SoftwareSerial m30(10, 11);

void setup() {

  // put your setup code here, to run once:

  pinMode(sensorfinal, INPUT_PULLUP);

  m30.begin(9600);
  Serial.begin(9600);

}



void loop() {

  // Código para pegar tempo de aceleração:
  if (mostrarvel == true) {
    Serial.print(vel);
    mostrarvel = false;
  }

  if (m30.available()) {
    sensor30 = m30.read();
  }

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
