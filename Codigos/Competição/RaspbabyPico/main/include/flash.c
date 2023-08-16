#include <LittleFS.h>


void flashSetup() {
  LittleFS.begin();
}


void readFlash(){//Função que le o que esta gravado no flash do pico
  char charRead[20];

  File flashRead = LittleFS.open("raw.dt", "r");             //Abre o arquivo como leitura ("r")

  String dataRead = flashRead.readString();                     //Grava o que é lido no flash na string
  dataRead.toCharArray(charRead,20);                            //Transforma a string em char

  sscanf(charRead, "%d %d", &engineTimerCounter, &movingTimerCounter);                //Escaneia a char para guardar os valores lidos em duas int independentes

  Serial.printf("LIDO FLASH: %d %d\n", engineTimerCounter, movingTimerCounter);       //Imprime no serial o valor lido
                                            
  flashRead.close();                                            //Fecha o arquivo
}


void writeFlash(){//Função que grava os dados no flash do pico
  File flashWrite = LittleFS.open("raw.dt", "w");             //Abre o arquivo como escrita

  Serial.printf("IMPRIMINDO FLASH: %d %d\n\n", engineTimerCounter, movingTimerCounter);//Imprime no serial o que sera escrito do flash
  flashWrite.printf("%d %d", engineTimerCounter, movingTimerCounter);                 //Escreve os novos valores no flash do pico

  flashWrite.close();                                           //Fecha o arquivo

  Serial.printf("###########\n\n");
}

void erase(){
  Serial.println("Apagado");
  LittleFS.remove("raw.dt");
  engineTimerCounter = 0;
  movingTimerCounter = 0;
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

