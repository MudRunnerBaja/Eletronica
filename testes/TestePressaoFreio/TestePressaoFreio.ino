const int sensor = A0;
int oldData, valorSensor, psi;
bool newData = false;
float voltPerBit, tensao;


float alimentacaoSensor = 5;


void setup() {
  Serial.begin(9600);
  Serial.print("Os calculos de tensao consideram que \no sensor esta sendo alimentado com 5v\n");
  delay (2000);
  voltPerBit = alimentacaoSensor / 1023;
}

void loop() {
  valorSensor = analogRead(sensor);
  
  psi = map(valorSensor, 102, 920, 0, 1600);
  tensao = valorSensor * voltPerBit;
  
  if (psi != oldData){
    newData = true;
    oldData = psi;
  } else {newData = false;}
  
  if(newData){
    Serial.print("sensor = ");
    Serial.print(tensao, 2);
    Serial.print(" V \t pressao = ");
    Serial.print(psi);
    Serial.print(" PSI \n");
   }
}
