#include <ACAN2515.h>



bool CVT = false, gps_conn = false, sd_rw = false, conn = false;
bool can_conn = false, update = false, nivelFreio = false, setLap = false;
short comb = 0;
double vel, velGps, rpm, rpmMovida, volta;
float tensao = 12, pressFreio, posAcelerador;
long told, tlap, tlapOld, tOn;
double TCvt, TProtecao;


char tvel[10]; // String responsável por mostrar o valor da velocidade
char trpm[10]; // String responsável por mostrar o valor do RPM
char mrpm[10];

// String tvel;
// String trpm;
// String mrpm;


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

uint64_t gather8bytes(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7){
  // uint64_t high;
  // uint32_t high32 = gather4bytes(b0, b1, b2, b3);
  // // int32print(high32);
  // uint64_t high = (uint64_t)high32;

  // // int64print(high);
  // //printf("%i", high);
  // //printf("\n");
  // //printf("%f", high);
  // //printf("\n");
  // uint64_t low;
  // low = gather4bytes(b4, b5, b6, b7);
  // low = low << 32;
  // int64print(low);
  // //printf("%f", low);
  // //printf("\n");
  

  uint64_t value = 
    ((uint64_t)b7 << 56) |
    ((uint64_t)b6 << 48) |
    ((uint64_t)b5 << 40) |
    ((uint64_t)b4 << 32) |
    ((uint64_t)b3 << 24) |
    ((uint64_t)b2 << 16) |
    ((uint64_t)b1 << 8)  |
    ((uint64_t)b0);

  // return  high | low;
  return value;
};


//Ver quais são os pinos
static const byte MCP2515_SCK  = 6; // SCK input of MCP2515
static const byte MCP2515_MOSI = 7 ; // SDI input of MCP2515
static const byte MCP2515_MISO = 4 ; // SDO output of MCP2515

static const byte MCP2515_CS  = 5 ;  // CS input of MCP2515 (adapt to your design)
// static const byte MCP2515_INT = 1 ;  // INT output of MCP2515 (adapt to your design)

ACAN2515 can (MCP2515_CS, SPI, 20) ;

static const uint32_t QUARTZ_FREQUENCY = 20UL * 1000UL * 1000UL ; // 20 MHz

static void setupComunicacao() {
  SPI.setSCK(MCP2515_SCK);
  SPI.setTX(MCP2515_MOSI);
  SPI.setRX(MCP2515_MISO);
  SPI.setCS(MCP2515_CS);
  SPI.begin ();
  
  ACAN2515Settings settings (QUARTZ_FREQUENCY, 125UL * 1000UL) ; // CAN bit rate 125 kb/s
  settings.mRequestedMode = ACAN2515Settings::NormalMode ;
  const uint16_t errorCode = can.begin (settings, [] { can.isr () ; }) ;
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
  frame.id = 10;
  can.tryToSend(frame);
  if (can.available ()) {
    can_conn = true;
    if (can.receive (frame)){

      if (frame.id == 1){
        uint64_t u64vel = gather8bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3],
          frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
  
        memcpy(&vel, &u64vel, sizeof(vel));


      }
      
      else if (frame.id == 10){ 
        uint64_t u64Acel = gather8bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3],
          frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        double pedalAcel;

        memcpy(&pedalAcel, &u64Acel, sizeof(pedalAcel));
        
        uint32_t u32Bat = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);

        
      }
      //frame2
      // tempObj = float = 4
      // tempAmb = float = 4
      else if (frame.id == 333){
        uint32_t u32Obj = gather4bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3]);

        uint32_t u32Amb = gather4bytes(frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
      }
      //frame
      else if (frame.id == 4){
        uint32_t u64Rpm = gather8bytes(frame.data[0], frame.data[1], frame.data[2], frame.data[3],
          frame.data[4], frame.data[5], frame.data[6], frame.data[7]);
        memcpy(&rpm, &u64Rpm, sizeof(u64Rpm));
      }

      else if (frame.id == 8){
        uint8_t uSDRW = frame.data[0];
        uint8_t ufixgps = frame.data[1];

        memcpy(&sd_rw, &uSDRW, sizeof(uSDRW));
        memcpy(&gps_conn, &ufixgps, sizeof(ufixgps));
      }
    }
  }
  if (debug){
    // Serial.println(vel);
  }
  int vel1 = (int)vel;
  int rpm1 = (int)rpm;
  sprintf(tvel, "%i", vel1); 
  sprintf(trpm, "%i", rpm1); 
  // itoa(vel/10, &tvel[0], 10);
        // itoa(vel%10, &tvel[1], 10);

        // itoa(rpm/1000, &trpm[0], 10);
        // itoa((rpm/100)%10, &trpm[1], 10);


        // itoa(rpm/1000, &mrpm[0], 10);
        // itoa((rpm/100)%10, &mrpm[1], 10);
        // itoa((rpm%100)/10, &mrpm[2], 10);
        // itoa(rpm%10, &mrpm[3], 10);
        told = millis();
        update = true;
}