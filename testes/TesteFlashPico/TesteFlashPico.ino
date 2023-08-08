#include <LittleFS.h>

void setup() {
  Serial.begin(115200);
  delay(5000);
  LittleFS.begin();
  char buff[32];

  File i = LittleFS.open("file1.txt", "w");
  if (i){
    i.write("10\n,10\n,10\n");
  }

  i.close();

  Serial.println("---------------");
  File s = LittleFS.open("file1.txt", "r");
  if (s) {
    while (s.available()) {
      Serial.write(s.read());
    }
    Serial.println("---------------");
    s.close();
  }
}


void loop() {
}