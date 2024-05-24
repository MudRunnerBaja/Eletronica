#include <LittleFS.h>
int tMotor, tRodagem;

void setup() {
  Serial.begin(115200);
  delay(5000);
  LittleFS.begin();
}

void loop() {
  static long timer;

  commands();                     //Função para ler comandos na porta serial para modificar o arquivo

  if(millis() > timer + 1000){    //A cada um segundo inicia a leitura e gravação (no codigo principal deve-se adicionar condicionais que atendam para cada indicador)
    leitura();                    //Função que le o que esta gravado no flash do pico
    escrita();                    //Função que grava os dados no flash do pico

    timer = millis();
  }
}


void leitura(){
  char charRead[20];

  File flashRead = LittleFS.open("raw.dt", "r");             //Abre o arquivo file.txt como leitura ("r")


  String dataRead = flashRead.readString();                     //Grava o que é lido no flash na string
  dataRead.toCharArray(charRead,20);                            //Transforma a string em char

  sscanf(charRead, "%d %d", &tMotor, &tRodagem);                //Escaneia a char para guardar os valores lidos em duas int independentes

  Serial.printf("LIDO FLASH: %d %d\n", tMotor, tRodagem);       //Imprime no serial o valor lido
  tMotor++;                                                     //Adiciona valores arbitrarios
  tRodagem += 2;                                            

  flashRead.close();                                            //Fecha o arquivo
}


void escrita(){
  File flashWrite = LittleFS.open("raw.dt", "w");            //Abre o arquivo file.txt como escrita


  Serial.printf("IMPRIMIDO FLASH: %d %d\n\n", tMotor, tRodagem);//Imprime no serial o que sera escrito do flash
  flashWrite.printf("%d %d", tMotor, tRodagem);                 //Escreve os novos valores no flash do pico
  flashWrite.close();                                           //Fecha o arquivo

  Serial.printf("###########\n\n");
}



void commands(){
  String entry; 

  while (Serial.available()) {
    entry = Serial.readString();
  }
  entry.trim();

  if (entry == "/erase"){
    erase();
  }
  if (entry == "/save")
  {
    save();
  }
  if (entry == "/backup")
  {
    backup();
  }
  if (entry == "/format"){
    erase();
    LittleFS.format();
  }
}

void erase(){
  Serial.println("Apagado");
  LittleFS.remove("raw.dt");
  tMotor = 0;
  tRodagem = 0;
}

void save(){
  Serial.println("Salvo no backup");
  File flashRead = LittleFS.open("raw.dt", "r");
  File flashWrite = LittleFS.open("backup.dt", "w");

  flashWrite.print(flashRead.readString());
}

void backup(){
  File flashWrite = LittleFS.open("backup.dt", "r");
  Serial.println(flashWrite.readString());
}