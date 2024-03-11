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

int nvl_freio = 22, adc_divtensao = 26;
float voltPerBit, tensao;
float tensaoMaxBat = 13;//VOLTS


TinyGPSPlus gps;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);  
  Serial.println("INCIALIZANDO");
  pinMode(nvl_freio, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  for (size_t i = 0; i < 10; i++)     //CONFIRMAÇÃO VISUAL QUE O PICO ESTA FUNCIONANDO
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  //SETANDO OS PINOS DO MODULO SD(SPI1)
  SPI1.setRX(RXPIN);
  SPI1.setTX(TXPIN);
  SPI1.setSCK(SCKPIN);
  SPI1.setCS(CSPIN);
  SPI1.begin(true);
  //INICIALIZANDO O CARTAO SD / VERIFICANDO A INCIALIZAÇÃO
  if(SD.begin(CSPIN, SPI1)){
    digitalWrite(LED_BUILTIN, HIGH);    //LED ACESO = CARTAO SD INCIALIZADO
  }

  //SETANDO PINOS DO CAN-BUS (SPI0)
  SPI.setSCK(sck0);
  SPI.setRX(rx0);
  SPI.setTX(tx0);
  CAN.setPins(cs0);
  //INCIALIANDO O CAN-BUS
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  //INICALIZA O SENSOR DE TEMPERATURA INFRAVERMELHO
  mlx.begin();
  voltPerBit = tensaoMaxBat / 1023;

  //SETANDO PORTA DO GPS / INICIALIZANDO
  //Serial1.setTX(GPS_TX);
  //Serial1.setRX(GPS_RX);
  //Serial1.begin(GPSBaud);
  
  Serial.println("INCILIZADO!");
}

bool fluido_baixo;
void loop() {
  Serial.println("\nLOOP!");
  int bits_divtensao = analogRead(adc_divtensao);
  tensao = bits_divtensao * voltPerBit;

  if(digitalRead(nvl_freio)){
    fluido_baixo = true;
  } else {
    fluido_baixo = false;
  }
  Serial.print("FLUIDO DE FREIO: ");
  
  if(fluido_baixo){
    Serial.println("BAIXO");
  }else{
    Serial.println("OK!");
  }
  
  Serial.print("Tensao bat: ");
  Serial.println(tensao);
  
  Serial.println("T. Ambiente\t T. Infrared");
  Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\t       "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.println("*C");

  Serial.print("CAN-BUS pacote padrao: ");

  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();

  Serial.println("OK!");

  delay(200);

  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
  Serial.print("CAN-BUS pacote extendido: ");

  CAN.beginExtendedPacket(0xabcdef);
  CAN.write('w');
  CAN.write('o');
  CAN.write('r');
  CAN.write('l');
  CAN.write('d');
  CAN.endPacket();

  Serial.println("OK!");

  delay(500); 
}
