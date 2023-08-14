#include <LittleFS.h>


long timer;


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
  String entry; 
  while (Serial.available()) {
    entry = Serial.readString();
  }
  entry.trim();


  if (entry == "/erase"){
    Serial.print("APAGADO");
    LittleFS.remove("file1.txt");
  }
}

int c = 66;
int lida;

void escrita(){

  String de = String(c,DEC);
  File i = LittleFS.open("file1.txt", "w");
  i.print(c);
  i.close();
}

String conv;

void leitura(){
   File s = LittleFS.open("file1.txt", "r");
    /*while (s.available()) {
      Serial.write(s.read());
    }*/
    //Serial.println(s.readString());
    Serial.println("---------------");
    conv = s.readString();
    c = conv.toInt();
    Serial.print(c);
    c++;
    s.close();
}