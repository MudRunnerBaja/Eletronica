#include <LittleFS.h>

int c;
long timer;
String entry; 


void setup() {
  Serial.begin(115200);
  delay(5000);
  LittleFS.begin();
}

void loop() {
  commands();
  if(millis() > timer + 1000){
    escrita();
    leitura();
    timer = millis();
  }

}

void commands(){
  while (Serial.available()) {
    entry = Serial.readString();
  }
  entry.trim();


  if (entry == "/erase"){
    Serial.print("APAGADO");
    LittleFS.remove("file1.txt");
  }
}

void escrita(){

  String de = String(c,DEC);
  File i = LittleFS.open("file1.txt", "w");
  i.print("TESTE");
  i.close();
}

void leitura(){
   File s = LittleFS.open("file1.txt", "r");
    while (s.available()) {
      Serial.write(s.read());
    }
    Serial.println("---------------");
    s.close();
}