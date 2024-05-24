//// adicionado para realizar contagem de tempo de rodagem do motor e do carro ////
#include "Arduino.h"
#include "LittleFS.h" // LittleFS is declared

LittleFSConfig cfg;

unsigned int engineElapsedTime;
unsigned int movingElapsedTime;
unsigned long engineTimerCounter = 0;
unsigned long movingTimerCounter = 0;
unsigned long t0 = 0, t1 = 0, conta = 0;

int rpmGlobal = 0;
int velGlobal = 10;

void setup()
{
    Serial.begin(115200);
 
    while (!Serial) {delay(100);}
 
    Serial.println(F("Inizializing FS..."));
    if (LittleFS.begin()){
        Serial.println(F("done."));
    }else{
        Serial.println(F("fail."));
    }
 
    // To format all space in LittleFS
    // LittleFS.format();

    File grabValues = LittleFS.open("/track.txt", "r");
    if (grabValues) {
      String fullStr = grabValues.readString();

      Serial.print("Original string: "); Serial.println(fullStr);
      String strs[6];
      int StringCount = 0;

      // Split the string into substrings
      while (fullStr.length() > 0)
      {
        int index = fullStr.indexOf(',');
        if (index == -1) // No space found
        {
          strs[StringCount++] = fullStr;
          break;
        }
        else
        {
          strs[StringCount++] = fullStr.substring(0, index);
          fullStr = fullStr.substring(index+1);
        }
      }

      Serial.println("\nSubStrings:");
      for (int i = 0; i < 3; i++) {
        Serial.println(strs[i]);
      }
      Serial.println();

      conta = strs[0].toInt();
      engineTimerCounter = strs[1].toInt();
      movingTimerCounter = strs[2].toInt();

      Serial.println("Counting from: ");
      Serial.print("Contador: "); Serial.println(conta);
      Serial.print("engineTimerCounter: "); Serial.print(engineTimerCounter); rpmGlobal > 0? Serial.println(" (Active - rpm > 0)") : Serial.println(" (Inactive - rpm <= 0)");
      Serial.print("movingTimerCounter: "); Serial.print(movingTimerCounter); velGlobal > 0? Serial.println(" (Active - vel > 0)") : Serial.println(" (Inactive - vel <= 0)");


    }
 
    // Get all information of your LittleFS
    FSInfo *info;
    LittleFS.info(*info);
 
    unsigned int totalBytes = info->totalBytes;
    unsigned int usedBytes = info->usedBytes;
    unsigned int freeBytes  = totalBytes-usedBytes;
    unsigned int maxPath = info->maxPathLength;
 
    Serial.println("File sistem info.");
 
    Serial.print("Total space:      ");
    Serial.print(totalBytes);
    Serial.println("byte");
 
    Serial.print("Total space used: ");
    Serial.print(usedBytes);
    Serial.println("byte");
 
    Serial.print("Total space free: ");
    Serial.print(freeBytes);
    Serial.println("byte");
 
    Serial.print("Max path lenght: ");
    Serial.print(maxPath);
    Serial.println("");
 
    Serial.println();
 
    // Open dir folder
    File dir = LittleFS.open("/", "r");
    
  t0 = t1 = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long loopt = micros();
  t1 = millis();
  if ((t1 - t0) > 999) {
    t1 = t0 = millis();
    conta++;
    if (rpmGlobal > 0) engineTimerCounter++;
    if (velGlobal > 0) movingTimerCounter++;

    File f = LittleFS.open("/track.txt", "w+");
    if (!f) { Serial.println("file open failed"); }
    else { 
      f.print(conta);f.print(",");
      f.print(engineTimerCounter);f.print(",");
      f.print(movingTimerCounter);
      Serial.print("Name: "); Serial.println(f.name());
      Serial.print("Size: "); Serial.println(f.size());
    }
    if (f) { f.close(); }

    f = LittleFS.open("/track.txt", "r");
    if(f) {
      Serial.println("\nReading:");

      Serial.println(f.readString());
      f.close();
    }
    Serial.print("Writing time: "); Serial.println(micros() - loopt);
  }
}