#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

long timer, timer2;
int data = 0;

String sentData = "TESTETESTE123456789123456789TESTETESTE"; //Dado a ser enviado ao hc12
int REFRESH_DISPLAY = 100; //Tempo em ms
int POLLING_RATE_DATA = 1000; //Tempo em ms

void setup() {
  Serial.begin(9600);             // Porta serial para o arduino
  Serial1.begin(9600);            // Porta serial para o HC12
  lcd.begin(16,2);
}

void loop() {
  int bytesRead = hc12Read();
  int bytesSent = hc12Send();
  lcdRefresh(bytesRead, bytesSent);
}


void lcdRefresh(int bytesRead, int bytesSent){
  if(millis()>timer2){
    Serial.print("Recived:");
    Serial.println(bytesRead);//
    lcd.setCursor(0,1);
    Serial.print("Sent:");
    Serial.println(bytesSent);//

    timer2 = millis()+1000;
  }
}

int hc12Read(){                   //RETORNA QUANTIDADE DE BITS QUE FOI ENVIADO
  int bytesRead = 0;
  while(Serial1.available()>0){
    data = Serial1.read();
    bytesRead++;
  }
  return sizeof(data);
}


int hc12Send(){                   //RETORNA A QUANTIDADE DE BITS QUE FOI RECIBIDA
  if(millis()>timer){
    Serial1.println(sentData);
    timer = millis() + 1000;
  }
  return  sizeof(sentData);
}