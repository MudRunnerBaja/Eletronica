#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);               // Serial port to HC12
  lcd.begin(16,2);                // Inicializa o display
}

void loop() {
  
  while (HC12.available()) {        // If HC-12 has data
    Serial.write(HC12.read());      // Send the data to Serial monitor
    lcd.write(HC12.read());         // Exibe informações recebidas no display
  }
}
