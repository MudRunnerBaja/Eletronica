// Código para o teste de RPM

/*
 * A simulação foi feita pelo software Proteus com botões para se ter 
 * comportamento equivalente a de sensores magnéticos.
 * 
 */

int correia1, correia2, rpm1, rpm2, rpmMedio;
bool estadoIma1, estadoIma2;

const int ima1 = 2;
const int ima2 = 3;
 
float tempo1 = 1;
float tempo2 = 1;


void setup() {
  Serial.begin(9600);
  
  pinMode(ima1, INPUT);
  pinMode(ima2, INPUT);
}

void loop() {
  estadoIma1 = digitalRead(ima1);
  estadoIma2 = digitalRead(ima2);
  
  if (estadoIma1 == HIGH){
      correia1++;
  } else if (estadoIma2 == HIGH){
      correia2++;
  }
   
  rpm1 = correia1/tempo1;
  rpm2 = correia2/tempo2;
  rpmMedio = (rpm1 + rpm2)/ 2;
    
  Serial.println(rpm1); // Debug
}
