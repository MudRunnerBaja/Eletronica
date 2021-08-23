#include <VirtualWire.h> 
#include <Wire.h>
//#include "I2Cdev.h"
#include "MPU6050_tockn.h" 

//#define pinSCL A5
//#define pinSDA A4
#define pinRF  7
#define pinLED 8

MPU6050 mpu6050(Wire);

long timer = 0;

struct tipoPacote{
  float valor_X;
  float valor_Y;
  float valor_Z; 
};

tipoPacote pacote;

int AcX,AcY,AcZ;

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
   mpu6050.update();

   if(millis() - timer > 1000){
   
      pacote.valor_X = mpu6050.getAccX();
      pacote.valor_Y = mpu6050.getAccY();
      pacote.valor_Z = mpu6050.getAccZ();
    
      vw_send ((uint8_t *)&pacote, sizeof(pacote));
      vw_wait_tx();
      digitalWrite(pinLED, LOW);
  
  
      /*Serial.println("=======================================================");
      Serial.print("accX : ");Serial.print(mpu6050.getAccX());
      Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
      Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());

      Serial.println("=======================================================\n");*/
      timer = millis();
    }
}
