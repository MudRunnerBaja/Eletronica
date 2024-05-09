#include <CAN.h>
#include <CANController.h>
#include <ESP32SJA1000.h>
#include <MCP2515.h>

#include <Adafruit_MLX90614.h>

#include <SPI.h>
#include <SD.h>    
#include <TinyGPS++.h>

#define GPS_TX 0 // PINO TX UART GPS
#define GPS_RX 1 // PINO RX UART GPS
const unsigned long GPSBaud = 9600;

#define SCKPIN 10
#define TXPIN 11 // MOSI
#define RXPIN 12 // MISO
#define CSPIN 13

TinyGPSPlus gps;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  SPI1.setRX(RXPIN);
  SPI1.setTX(TXPIN);
  SPI1.setSCK(SCKPIN);
  SPI1.setCS(CSPIN);
  SPI1.begin(true);
  if(SD.begin(CSPIN, SPI1)){
    digitalWrite(LED_BUILTIN, HIGH);
  }

  Serial.begin(9600);
  mlx.begin();
  
  Serial1.setTX(GPS_TX);
  Serial1.setRX(GPS_RX);
  Serial1.begin(GPSBaud);
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.println();
  
  delay(500);
}
