int sensor30 = 5;
int sensorfinal = 6;
float tempoant = 0;
float tempoace = 0;
float tempofinal = 0;
float tempoinicial = 0;
bool contado30 = false;
bool contadoinicio = false;
bool inicio = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor30, INPUT_PULLUP);
  pinMode(sensorfinal, INPUT_PULLUP);
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  // Código para pegar tempo de aceleração:
  //Serial.print(digitalRead(sensor30));
  if (digitalRead(sensor30) == !HIGH && contado30 == false) {

    tempoace = millis();
    tempoant = millis();
    Serial.println("O carro acabou de passar aqui!\n");
    Serial.print("Tempo: ");
    Serial.print(tempoace / 1000);
    contado30 = true;

  }

  // Código para passagem final:
  if (digitalRead(sensorfinal) == !HIGH) {
    if (inicio == true) {
      tempoinicial = millis();
      inicio = false;
      Serial.println("Iniciado o teste");
    }

    if (contado30 == true) {
      tempofinal = millis() - tempoinicial;
      Serial.println("Teste finalizado!\n");
      Serial.print("Tempo final: ");
      Serial.print(tempofinal);
    }

  }
}
