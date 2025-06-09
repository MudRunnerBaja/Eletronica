#include <ACAN2515.h>

typedef union {
  float f;
  uint32_t u32;
} FloatUnion;

typedef union {
  double d;
  uint32_t u32;
} DoubleUnion;

typedef union {
  int i;
  uint8_t u8;
} IntUnion;

typedef union {
  short s;
  uint8_t u8;
} ShortUnion;

uint32_t gather4bytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3){
  return (b0 | (b1 << 8)) | ((b2 | (b3 << 8)) << 16);
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
  settings.mRequestedMode = ACAN2515Settings::ListenOnlyMode ;
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;
}

static void receiveMessage(bool debug = false) {
  CANMessage frame ;
  if (can.available ()) {
    if (can.receive (frame)){

      //frame0 -> 
      // nivelCombustível = short = 2
      // nivelAtualFreio = int = 2
      // pressaoAtualFreio = double = 4
      if (frame.id == 0x1FFFFFFF){
        ;
      }
      //frame1 ->
      // pedalAcel = double = 4
      // tensaoBat = double = 4
      else if (frame.id == 0x11FFFFFF){
        DoubleUnion dAcel;
        DoubleUnion dBat;

        uint32_t u32Acel = gather4bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3]);
        dAcel.u32 = u32Acel;
        double pedalAcel = dAcel.d;

        uint32_t u32Bat = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        dBat.u32 = u32Bat;
        double tensaoBat = dBat.d;
      }
      //frame2
      // tempObj = float = 4
      // tempAmb = float = 4
      else if (frame.id == 0x111FFFFF){
        FloatUnion dObj;
        FloatUnion dAmb;

        uint32_t u32Obj = gather4bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3]);
        dObj.u32 = u32Obj;
        double tempObj = dObj.f;

        uint32_t u32Amb = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        dAmb.u32 = u32Amb;
        double tempAmb = dAmb.f;
      }
      //frame0
      // rpm = double = 4
      // vel = double = 4
      else if (frame.id == 0x1111FFFF){
        DoubleUnion dRpm;
        DoubleUnion dVel;

        uint32_t u32Rpm = gather4bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3]);
        dRpm.u32 = u32Rpm;
        double pedalAcel = dRpm.d;

        uint32_t u32Vel = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        dVel.u32 = u32Vel;
        double vel = dVel.d;
      }
    }
    
    // gReceivedFrameCount ++ ;
    // Serial.print ("Received: ") ;
    // Serial.println (gReceivedFrameCount) ;
  }
  if (debug){
    Serial.println(vel);
  }
}