#include <LittleFS.h>


long timer;
String conv;


void setup() {
  Serial.begin(115200);
  delay(5000);
  LittleFS.begin();
}

void loop() {
  commands();
  if(millis() > timer + 1000){
    leitura();
    escrita();
    timer = millis();
  }

}

void commands(){
  String entry; 
  while (Serial.available()) {
    entry = Serial.readString();
  }
  entry.trim();


  if (entry == "/erase"){
    Serial.print("APAGADO");
    LittleFS.remove("file1.txt");
  } else if (entry == "/save")
  {
    Serial.print("Salvando");
    File flashRead = LittleFS.open("file1.txt", "r");
    File flashWrite = LittleFS.open("bckp.txt", "w");
    String BCK;
    BCK = flashRead.readString();
    flashWrite.print(BCK);
  }else if (entry == "/backup")
  {
    File flashWrite = LittleFS.open("bckp.txt", "r");
    Serial.println(flashWrite.readString());
  }
}

int c;
int lida;

void escrita(){
  //String de = String(c,DEC);

  File flashWrite = LittleFS.open("file1.txt", "w");

  flashWrite.print(c);
  flashWrite.close();
}


void leitura(){
   File flashRead = LittleFS.open("file1.txt", "r");

    conv = flashRead.readString();

    c = conv.toInt();

    Serial.println(conv);

    c++;

    flashRead.close();
}