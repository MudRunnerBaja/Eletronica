#include <ACAN2515.h>


uint32_t gather4bytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3){
  return (b0 | (b1 << 8)) | ((b2 | (b3 << 8)) << 16);
};

void int32print(uint32_t A){
  uint32_t a = A;
  float f;
  
  memcpy(&f, &a, sizeof(f));
  Serial.println(f);
  Serial.println("\n");
}

void int64print(uint64_t I){
  uint64_t i = I;
  double dd;
  memcpy(&dd, &i, 8);
  uint8_t prr [8];
  memcpy(&prr, &dd, 8);
  float um = gather4bytes(prr[0], prr[1], prr[2], prr[3]);
  float dois = gather4bytes(prr[4], prr[5], prr[6], prr[7]);
  Serial.println("---int64print---");
  Serial.println(um);
  Serial.println(dois);
  Serial.println("---------");
}
// uint64_t gather8bytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7){
//   return (b0 | (b1 << 8)) | ((b2 | (b3 << 8)) << 16) | (((b4 | (b5 << 8)) | ((b6 | (b7 << 8)) << 16)) << 32);
// };
uint64_t gather8bytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7){
  uint64_t high;
  uint32_t high32 = gather4bytes(b0, b1, b2, b3);
  int32print(high32);
  memcpy(&high, &high32, 8);
  int64print(high);
  //printf("%i", high);
  //printf("\n");
  //printf("%f", high);
  //printf("\n");
  uint64_t low;
  low = gather4bytes(b4, b5, b6, b7);
  low = low << 32;
  int64print(low);
  //printf("%f", low);
  //printf("\n");
  
  return  high | low;
};


//Ver quais são os pinos
static const byte MCP2515_SCK  = 6; // SCK input of MCP2515
static const byte MCP2515_MOSI = 7 ; // SDI input of MCP2515
static const byte MCP2515_MISO = 4 ; // SDO output of MCP2515

static const byte MCP2515_CS  = 5 ;  // CS input of MCP2515 (adapt to your design)
// static const byte MCP2515_INT = 1 ;  // INT output of MCP2515 (adapt to your design)

ACAN2515 can (MCP2515_CS, SPI, 255) ;

static const uint32_t QUARTZ_FREQUENCY = 20UL * 1000UL * 1000UL ; // 20 MHz

static void setupComunicacao() {
  SPI.setSCK(MCP2515_SCK);
  SPI.setTX(MCP2515_MOSI);
  SPI.setRX(MCP2515_MISO);
  SPI.setCS(MCP2515_CS);
  SPI.begin ();
  
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 125UL * 1000UL) ; // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::NormalMode ;
  const uint16_t errorCode = can.begin (settings, NULL) ;
  CANMessage frame;
  if (errorCode == 0)
        {
            Serial.print("CAN init success");
            frame.id = 10;

            can.tryToSend(frame);
            can.poll();

        }
        else
        {
            Serial.print("CAN Configuration error 0x");
            Serial.println(errorCode, HEX);
        }
}

static void receiveMessage(bool debug = false) {
  can.poll();
  CANMessage frame ;
  if (can.available ()) {
    // Serial.println("available");
    if (can.receive (frame)){
      Serial.print("frame id:");
      Serial.println(frame.id);

      //frame0 -> 
      // nivelCombustível = short = 2
      // nivelAtualFreio = int = 2
      // pressaoAtualFreio = double = 4
      if (frame.id == 1){
        // Serial.println("frame0");
      }
      //frame1 ->
      // pedalAcel = double = 4
      // tensaoBat = double = 4
      else if (frame.id == 2){
        uint64_t u64Acel = gather8bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3],
          frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        int64print(u64Acel);
        double pedalAcel;

        memcpy(&pedalAcel, &u64Acel, sizeof(pedalAcel));
        Serial.println(pedalAcel);
        // dAcel.u32 = u32Acel;
        // double pedalAcel = dAcel.d;
        
        uint32_t u32Bat = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        // dBat.u32 = u32Bat;
        // double tensaoBat = dBat.d;

        Serial.print("frame data: ");
        for (int i = 0; i < 8; i++){
          Serial.print(frame.data[i]);
          Serial.print(", ");
        }
        Serial.print("frame len: ");
        Serial.println(frame.len);
        Serial.print("Valor do pedalAcel:");
        Serial.println(u64Acel);
      }
      //frame2
      // tempObj = float = 4
      // tempAmb = float = 4
      else if (frame.id == 3){
        uint32_t u32Obj = gather4bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3]);
        // dObj.u32 = u32Obj;
        // double tempObj = dObj.f;

        uint32_t u32Amb = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        // dAmb.u32 = u32Amb;
        // double tempAmb = dAmb.f;
      }
      //frame0
      // rpm = double = 4
      // vel = double = 4
      else if (frame.id == 0x1111FFFF){
        uint32_t u32Rpm = gather4bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3]);
        // dRpm.u32 = u32Rpm;
        // double pedalAcel = dRpm.d;

        uint32_t u32Vel = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        // dVel.u32 = u32Vel;
        // double vel = dVel.d;
      }
    }
    
    // gReceivedFrameCount ++ ;
    // Serial.print ("Received: ") ;
    // Serial.println (gReceivedFrameCount) ;
  }
  if (debug){
    // Serial.println(vel);
  }
}