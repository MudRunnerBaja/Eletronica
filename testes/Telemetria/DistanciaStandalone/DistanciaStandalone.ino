#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

String sentData = "Testes"; //Dado a ser enviado ao hc12
int REFRESH_DISPLAY = 100; //Tempo em ms
int POLLING_RATE_DATA = 1000; //Tempo em ms

void setup() {
  Serial.begin(9600);             // Porta serial para o arduino
  Serial1.begin(9600);            // Porta serial para o HC12
  lcd.begin(16,2);
}

void loop() {
  int bytesSent = hc12Send();
  int bytesRead = hc12Read();
  lcdRefresh(bytesRead, bytesSent);
}


void lcdRefresh(int bytesRead, int bytesSent){
  static long timer = 0;

  if(millis()>timer){

    Serial.print("Recived:");
    Serial.print(bytesRead);
    Serial.print("  ||   Sent:");
    Serial.println(bytesSent);

    lcd.clear();
    lcd.print("Recived:");
    lcd.println(bytesRead);
    lcd.setCursor(0,1);
    lcd.print("Sent:");
    lcd.println(bytesSent);

    timer = millis()+1000;
  }
}

int hc12Read(){                   //RETORNA QUANTIDADE DE BITS QUE FOI ENVIADO
  static int receivedBytes = 0;
  while(Serial1.available()){
    Serial1.read();
    receivedBytes++;
  }
  return receivedBytes;
}


int hc12Send(){                   //RETORNA A QUANTIDADE DE BITS QUE FOI RECIBIDA
  static int sentBytes = 0;
  static long timer = 0;

  if(millis()>timer){
    sentBytes += Serial1.println(sentData);
    timer = millis() + 1000;
  }
  return  sentBytes;
}