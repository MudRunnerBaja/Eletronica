#include <VirtualWire.h> 
#include <Wire.h>
//#include "I2Cdev.h"
#include "MPU6050_tockn.h" 

//#define pinSCL A5
//#define pinSDA A4
#define pinRF  7
#define pinLED 8

MPU6050 mpu6050(Wire);

const unsigned long repeticao = 50;
unsigned long tempoPrecedente = 0;

struct tipoPacote{
  float valor_X;
  float valor_Y;
  float valor_Z; 
};

tipoPacote pacote;

void setup (){
 Serial.begin(9600);

// Inicializa o MPU 6050
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

//  Inicializa o modulo RF
  vw_set_tx_pin(pinRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000); // Velocidade de transmissao
  
  pinMode(pinLED, OUTPUT); 
}

void loop() { 

  unsigned long tempoDomillis = millis ();
   mpu6050.update();

   if(tempoDomillis - tempoPrecedente >= repeticao){
   
      pacote.valor_X = mpu6050.getAccX();
      pacote.valor_Y = mpu6050.getAccY();
      pacote.valor_Z = mpu6050.getAccZ();
    
      vw_send ((uint8_t *)&pacote, sizeof(pacote));
      vw_wait_tx();
      digitalWrite(pinLED, LOW);
  
  
      Serial.println("=======================================================");
      Serial.print("accX : ");Serial.print( pacote.valor_X);
      Serial.print("\taccY : ");Serial.print(pacote.valor_Y);
      Serial.print("\taccZ : ");Serial.println(pacote.valor_Z);
      Serial.println("=======================================================\n");
      tempoPrecedente = tempoDomillis;
    }
}
