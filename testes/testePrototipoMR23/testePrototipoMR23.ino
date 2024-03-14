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
float tensaoMaxBat = 13.3;//VOLTS
bool sd_init = false;

File myFile;

TinyGPSPlus gps;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);  
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
      digitalWrite(LED_BUILTIN, HIGH);//LED ACESO = CARTAO SD INCIALIZADO
      sd_init = true;
  }else{
    Serial.println("Erro inicialização SD");
    sd_init = false;
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
  } else {
    Serial.println("Inicializado CAN");
    }

  //INICALIZA O SENSOR DE TEMPERATURA INFRAVERMELHO
  mlx.begin();
  Serial.println("Inicializado MLX");

  voltPerBit = tensaoMaxBat / 1023;

  //SETANDO PORTA DO GPS / INICIALIZANDO
  Serial2.setTX(GPS_TX);
  Serial2.setRX(GPS_RX);
  Serial2.begin(GPSBaud);
  Serial.println("Inicializado Serial do GPS");
  
  
  Serial.println("INCILIZADO!");
}

bool fluido_baixo;
void loop() {
  long t_inicial = millis();
  Serial.println("\n###############################\nLOOP!");
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


  if(!sd_init){
    if(SD.begin(CSPIN, SPI1)){
      sd_init = true;
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }

  Serial.println("Conteudo no SD: ");
  myFile = SD.open("test.txt");

  if(myFile){
  while (myFile.available()) {
      Serial.write(myFile.read());
    }
  }else{
    Serial.print("ERRO!");
  }
  myFile.close();
  Serial.print("\nGPS Caracteres processados: ");
  gps.encode(Serial2.read());

  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected"));
  } else {
    Serial.println(gps.time.value());

   /* Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.println(gps.date.year());*/
  }


  long t_final = millis();
  long t_total = t_final - t_inicial;
  Serial.print("\n\nTempo de processamento: ");
  Serial.println(t_total);
}
