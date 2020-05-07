int sensor30;
int sensorfinal = 6; 
float tempoant = 0; 
float tempoace = 0; 
float tempofinal = 0; 
float tempoinicial = 0; 
bool contado30 = false; 
bool contadoinicio = false; 
bool inicio = true; 
bool final = false; 

  

void setup() { 

  // put your setup code here, to run once: 
 
  pinMode(sensorfinal, INPUT_PULLUP); 
  Serial.begin(9600); 

} 

  

void loop() { 

  // Código para pegar tempo de aceleração: 

if (Serial.available()) { 

// atribuindo o valor do serial.read para o sensor30 

 sensor30 = Serial.read(); 

} 

  if (sensor30 == '0' && contado30 == false) { 

    tempoace = millis(); 
    tempoant = millis(); 
    Serial.println("O carro acabou de passar aqui!\n"); 
    Serial.print("Tempo 30 metros: "); 
    Serial.println(tempoace / 1000); 
    contado30 = true; 

  }

  

  // Código para passagem final: 

  if (digitalRead(sensorfinal) == 0) { 

    if (inicio) { 

      tempoinicial = millis(); 
      inicio = false; 
      Serial.println("Iniciado o teste"); 

    } 

  

    if (contado30 == true && final == false) { 

      tempofinal = millis() - tempoinicial; 
      Serial.println("\nTeste finalizado!\n"); 
      Serial.print("Tempo final: "); 
      Serial.println((tempofinal + tempoace)/1000); 
      final = true; 

    } 

  } 

} 
