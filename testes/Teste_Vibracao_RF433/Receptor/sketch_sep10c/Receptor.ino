#include <VirtualWire.h>

#define led 8
#define pinRF 7

long timer = 0;

struct tipoPacote{
  float valor_X;
  float valor_Y;
  float valor_Z; 
};

tipoPacote pacote;


void setup(){
  Serial.begin(9600);
  Serial.println("Iniciando a Transmissao");
 
// Iniciando a recepção de dados  
  vw_set_rx_pin(pinRF);
  vw_setup(2000);
  vw_rx_start();
   
  pinMode(led, OUTPUT);
  
}

void loop() {

  uint8_t buf[sizeof(pacote)];
  uint8_t buflen = sizeof(pacote);

  if (vw_have_message()&& millis() - timer > 1000){
    vw_get_message(buf, &buflen);
    memcpy(&pacote,&buf,buflen);
    digitalWrite(led, HIGH);

    Serial.println("");
    Serial.print("ACX = "); Serial.print(pacote.valor_X);
    Serial.print("\tACY = "); Serial.print(pacote.valor_Y);
    Serial.print("\tACZ = "); Serial.print(pacote.valor_Z);

    timer = millis();
    }   
}
