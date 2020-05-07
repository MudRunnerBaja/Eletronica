int sensor30 = 6;  

void setup() { 

  // put your setup code here, to run once: 

  pinMode(sensor30, INPUT_PULLUP); 
  Serial.begin(9600); 

} 

void loop() { 

  // Código para pegar tempo de aceleração: 

    //Serial.println("Estado do sensor_30m:"); 
    Serial.println(sensor30); 


} 
