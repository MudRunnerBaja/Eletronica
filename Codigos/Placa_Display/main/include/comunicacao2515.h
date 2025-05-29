#include <ACAN2515.h>


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
  SP1.setTX(MCP2515_MOSI);
  SPI.setRX(MCP2515_MISO);
  SPI.setCS(MCP2515_CS);
  SPI.begin ();
  
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 125UL * 1000UL) ; // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::ListenOnlyMode ;
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;
}

static void receiveMessage() {
  CANMessage frame ;
  if (can.available ()) {
    if (can.receive (frame)){
        ;
    }
    
    // gReceivedFrameCount ++ ;
    // Serial.print ("Received: ") ;
    // Serial.println (gReceivedFrameCount) ;
  }
}