#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

long timer, timer2;
int data = 0;

String sentData = "TESTETESTE123456789123456789TESTETESTE"; //Dado a ser enviado ao hc12
int REFRESH_DISPLAY = 100; //Tempo em ms
int POLLING_RATE_DATA = 1000; //Tempo em ms

void setup() {
  Serial.begin(9600);             // Porta serial para o arduino

  Serial1.setRX(1); // 17 | 1
  Serial1.setTX(0); // 16 | 0
  Serial1.begin(9600);            // Porta serial para o HC12

  Serial2.setRX(5);
  Serial2.setTX(4);
  Serial2.begin(9600);

  lcd.begin(16,2);
}

void loop() {
  // int bytesRead = hc12Read(); // Chamando dentro de lcdRefresh
  // int bytesSent = hc12Send(); // Chamando dentro de lcdRefresh
  lcdRefresh();
}


void lcdRefresh(){
  if(millis()>timer2) {
    int bytesSent = hc12Send(sentData);
    Serial.print("No of bytes Sent:");
    Serial.println(bytesSent); //

    lcd.setCursor(0,1);

    int bytesReceived = hc12Read();
    Serial.print("No of bytes Received: ");
    Serial.println(bytesReceived); //

    Serial.print("\n--------\n");
    timer2 = millis()+2000;
  }
}

int hc12Read(){                   //RETORNA QUANTIDADE DE BITS QUE FOI ENVIADO
  String rData = "";
  Serial.print("Received Data: ");

  while(Serial1.available()){
    
    Serial.print("Serial1 SOCORRO");
    rData += Serial1.readString();
  }
  
  while(Serial2.available()){
    
    Serial.print("Serial2 SOCORRO");
    rData += Serial2.readString();
  }

  while(Serial.available()){
    
    Serial.print("Serial0 SOCORRO");
    rData += Serial.readString();
  }

  Serial.print(rData);
  return sizeof(rData);
}


int hc12Send(String sData){                   //RETORNA A QUANTIDADE DE BITS QUE FOI RECIBIDA
  
  int size = Serial2.write(sData.c_str()); // Como está dentro do lcdRefresh, ele respeita o timer do lcdRefresh
  Serial.print("Sent Data: ");
  Serial.println(sData);

  /* if(millis()>timer){
    Serial1.println(sentData);
    timer = millis() + 1000;
  }*/

  return  size;
}