//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode, for ESP32, with no interrupt pin
//——————————————————————————————————————————————————————————————————————————————

#ifndef ARDUINO_ARCH_ESP32
  #error "Select an ESP32 board" 
#endif

//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515.h>

//——————————————————————————————————————————————————————————————————————————————
//  For using SPI on ESP32, see demo sketch SPI_Multiple_Buses
//  Two SPI busses are available in Arduino, HSPI and VSPI.
//  By default, Arduino SPI uses VSPI, leaving HSPI unused.
//  Default VSPI pins are: SCK=18, MISO=19, MOSI=23.
//  You can change the default pin with additional begin arguments
//    SPI.begin (MCP2515_SCK, MCP2515_MISO, MCP2515_MOSI)
//  CS input of MCP2515 should be connected to a digital output port
//  Notes:
//    - GPIOs 34 to 39 are GPIs – input only pins. These pins don’t have internal pull-ups or
//      pull-down resistors. They can’t be used as outputs.
//    - some pins do not support INPUT_PULLUP (see https://www.esp32.com/viewtopic.php?t=439) 
// See https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//——————————————————————————————————————————————————————————————————————————————

static const byte MCP2515_SCK  = 26 ; // SCK input of MCP2515 
static const byte MCP2515_MOSI = 19 ; // SDI input of MCP2515  
static const byte MCP2515_MISO = 18 ; // SDO output of MCP2515 

static const byte MCP2515_CS  = 17 ; // CS input of MCP2515 (adapt to your design) 

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Driver object
//——————————————————————————————————————————————————————————————————————————————

ACAN2515 can (MCP2515_CS, SPI, 255) ; // Last argument is 255 -> no interrupt pin

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 Quartz: adapt to your design
//——————————————————————————————————————————————————————————————————————————————

static const uint32_t QUARTZ_FREQUENCY = 20UL * 1000UL * 1000UL ; // 20 MHz

//——————————————————————————————————————————————————————————————————————————————
//   SETUP
//——————————————————————————————————————————————————————————————————————————————

void setup () {
//--- Switch on builtin led
  pinMode (LED_BUILTIN, OUTPUT) ;
  digitalWrite (LED_BUILTIN, HIGH) ;
//--- Start serial
  Serial.begin (115200) ;
//--- Wait for serial (blink led at 10 Hz during waiting)
  while (!Serial) {
    delay (50) ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
  }
//--- Begin SPI
  SPI.begin (MCP2515_SCK, MCP2515_MISO, MCP2515_MOSI) ;
//--- Configure ACAN2515
  Serial.println ("Configure ACAN2515") ;
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 125UL * 1000UL) ; // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::LoopBackMode ; // Select loopback mode
  const uint16_t errorCode = can.begin (settings, NULL) ; // Second argument is NULL -> no interrupt service routine
  if (errorCode == 0) {
    Serial.print ("Bit Rate prescaler: ") ;
    Serial.println (settings.mBitRatePrescaler) ;
    Serial.print ("Propagation Segment: ") ;
    Serial.println (settings.mPropagationSegment) ;
    Serial.print ("Phase segment 1: ") ;
    Serial.println (settings.mPhaseSegment1) ;
    Serial.print ("Phase segment 2: ") ;
    Serial.println (settings.mPhaseSegment2) ;
    Serial.print ("SJW: ") ;
    Serial.println (settings.mSJW) ;
    Serial.print ("Triple Sampling: ") ;
    Serial.println (settings.mTripleSampling ? "yes" : "no") ;
    Serial.print ("Actual bit rate: ") ;
    Serial.print (settings.actualBitRate ()) ;
    Serial.println (" bit/s") ;
    Serial.print ("Exact bit rate ? ") ;
    Serial.println (settings.exactBitRate () ? "yes" : "no") ;
    Serial.print ("Sample point: ") ;
    Serial.print (settings.samplePointFromBitStart ()) ;
    Serial.println ("%") ;
  }else{
    Serial.print ("Configuration error 0x") ;
    Serial.println (errorCode, HEX) ;
  }
}

//----------------------------------------------------------------------------------------------------------------------

static uint32_t gBlinkLedDate = 0 ;
static uint32_t gReceivedFrameCount = 0 ;
static uint32_t gSentFrameCount = 0 ;

//——————————————————————————————————————————————————————————————————————————————

void loop () {
  can.poll () ; // No interrupt, call this function as often as possible
  CANMessage frame ;
  if (gBlinkLedDate < millis ()) {
    gBlinkLedDate += 2000 ;
    digitalWrite (LED_BUILTIN, !digitalRead (LED_BUILTIN)) ;
    const bool ok = can.tryToSend (frame) ;
    if (ok) {
      gSentFrameCount += 1 ;
      Serial.print ("Sent: ") ;
      Serial.println (gSentFrameCount) ;
    }else{
      Serial.println ("Send failure") ;
    }
  }
  if (can.available ()) {
    can.receive (frame) ;
    gReceivedFrameCount ++ ;
    Serial.print ("Received: ") ;
    Serial.println (gReceivedFrameCount) ;
  }
}

//——————————————————————————————————————————————————————————————————————————————
