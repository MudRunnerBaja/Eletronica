#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte sentData = 0xFF; //Dado a ser enviado ao hc12
int REFRESH_DISPLAY = 100; //Tempo em ms
int POLLING_RATE_DATA = 1000; //Tempo em ms
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);             // Porta serial para o arduino
  Serial1.begin(9600);            // Porta serial para o HC12
  Serial2.begin(9600);            // Porta serial para o HC12
  lcd.begin(16,2);
}

void loop() {

  lcdRefresh();
}


void lcdRefresh(){
  static long timer = 0;

  if(millis()>timer){
    int read = hc12Read();
    int sent = hc12Send();
    Serial.print("Recived:");
    Serial.print(read);
    Serial.print("  ||   Sent:");
    Serial.println(sent);

    lcd.clear();
    lcd.print("Recived:");
    lcd.println(read);
    lcd.setCursor(0,1);
    lcd.print("Sent:");
    lcd.println(sent);

    timer = millis()+1000;
  }
}

int hc12Read(){                   //RETORNA QUANTIDADE DE BITS QUE FOI ENVIADO
  int receivedBytes = 0;
  byte read[4] = { 0, 0, 0, 0 };
  while(Serial1.available() > 0) {
  receivedBytes = Serial1.readBytes(read, 4);
  }
  int i = 0;
  for(i;i < 4; i++) {
    Serial.print("Byte: ");Serial.print(i);Serial.print(" - ");Serial.println(read[i]);
  }
  return receivedBytes;
}


int hc12Send(){                   //RETORNA A QUANTIDADE DE BITS QUE FOI RECIBIDA
  int sentBytes = 0;

  sentBytes += Serial2.write(sentData);
  sentBytes += Serial2.write(sentData);
  sentBytes += Serial2.write(sentData);
  sentBytes += Serial2.write(sentData);

  return  sentBytes;
}