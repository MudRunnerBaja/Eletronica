#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte sentData = 0xFF; //Dado a ser enviado ao hc12
int REFRESH_DISPLAY = 100; //Tempo em ms
int POLLING_RATE_DATA = 1000; //Tempo em ms
unsigned long timer = 0;
void addPackageData(int amountBytesReceived, int expectedBytesToReceive);
void removePackageData(int momentToRemoveBytes, int expectedBytesToReceive);

struct PackageInfo {
  int dataVector[60];
  unsigned short cont = 0, size = 0;
  unsigned short maxSize = 60;
  unsigned long timeSpan = 1000; // milliseconds. Period is 1000ms * 60 (maxSize+1) -> 1 minute
  unsigned long timer = 0;
  int receivedLastMinute = 0;
  int expectedLastMinute = 0;
  double pctReceivedLastMinute = 0.0f;
  double lostLastMinute = 1 - pctReceivedLastMinute;
} package;

void setup() {
  for (int i = 0; i < package.maxSize; i++)
    package.dataVector[i] = 0;

  Serial.begin(9600);             // Porta serial para o arduino
  Serial1.begin(1200);            // Porta serial para o HC12
  Serial2.begin(1200);            // Porta serial para o HC12
  lcd.begin(16,2);
}

void loop() {

  lcdRefresh();
}


void lcdRefresh(){
  static long timer = 0;
  static float readTotal = 4;
  static float sentTotal;
  

  if(millis()>timer){    
    int read = hc12Read();
    int sent = hc12Send();
    readTotal += read;
    sentTotal += sent;
    
    // float percent = 100 - (readTotal/sentTotal) * 100;
    addPackageData(read, sent);

    Serial.print("Recived:");
    Serial.print(read);
    Serial.print("  ||   Sent:");
    Serial.println(sent);

    lcd.clear();
    lcd.print("S:");
    lcd.print(sent);
    lcd.setCursor(3,0);
    lcd.print("/R:");
    lcd.print(read);
    lcd.setCursor(7,0);
    lcd.print(" Bytes");

    lcd.setCursor(0,1);
    lcd.print("Perda:");
    lcd.print(package.lostLastMinute,6);
    lcd.print("%");

    timer = millis()+900;
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

void addPackageData(int amountBytesReceived, int expectedBytesToReceive) {
  unsigned long timeElapsed = millis();
  while (!(timeElapsed - package.timer < package.timeSpan)) continue;
  Serial.println(timeElapsed - package.timer);
  package.timer = timeElapsed; 
  Serial.print("amtReceived: ");Serial.println(amountBytesReceived);

  if (package.size < package.maxSize) package.size++;
  else if (package.size == package.maxSize) removePackageData(package.cont, expectedBytesToReceive);
  
  package.dataVector[package.cont] = amountBytesReceived;
  package.cont++;
  if(package.cont == package.maxSize) package.cont = 0;

  package.receivedLastMinute += amountBytesReceived;
  package.expectedLastMinute += expectedBytesToReceive;

  package.pctReceivedLastMinute = 100 * (((float)package.receivedLastMinute / (float)package.expectedLastMinute));
  package.lostLastMinute = 100 - package.pctReceivedLastMinute;
  Serial.print("pkg lost: ");Serial.println(package.lostLastMinute);
  Serial.print("pct received: ");Serial.println(package.pctReceivedLastMinute);
  
}

void removePackageData(int momentToRemoveBytes, int expectedBytesToReceive) {
  package.receivedLastMinute -= package.dataVector[momentToRemoveBytes];
  package.expectedLastMinute -= expectedBytesToReceive;


}
