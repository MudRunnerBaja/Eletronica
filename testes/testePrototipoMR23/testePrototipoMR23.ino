#include <CAN.h>

#include <Adafruit_MLX90614.h>

#include <SPI.h>
#include <SD.h>    

#include <TinyGPS++.h>

#define GPS_TX 8 // PINO TX UART GPS
#define GPS_RX 9 // PINO RX UART GPS
const unsigned long GPSBaud = 9600;
//cartao sd
#define SCKPIN 10
#define TXPIN 11 // MOSI
#define RXPIN 12 // MISO
#define CSPIN 13

//can_bus
#define sck0 18
#define rx0 16  //MISO
#define tx0 19  //MOSI
#define cs0 17 

TinyGPSPlus gps;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);  
  Serial.println("INCIALIZANDO");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for (size_t i = 0; i < 10; i++)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  
  SPI1.setRX(RXPIN);
  SPI1.setTX(TXPIN);
  SPI1.setSCK(SCKPIN);
  SPI1.setCS(CSPIN);
  SPI1.begin(true);
  
  if(SD.begin(CSPIN, SPI1)){
    digitalWrite(LED_BUILTIN, HIGH);
  }

  SPI.setSCK(sck0);
  SPI.setRX(rx0);
  SPI.setTX(tx0);

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  CAN.setPins(cs0);


  mlx.begin();
  
  //Serial1.setTX(GPS_TX);
  //Serial1.setRX(GPS_RX);
  //Serial1.begin(GPSBaud);
  Serial.println("INCILIZADO!");
}

void loop() {
  Serial.println("LOOP!");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.println();

  Serial.print("Sending packet ... ");

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();

  Serial.println("done");

  delay(200);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending extended packet ... ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("done");

  delay(500);

  
}
