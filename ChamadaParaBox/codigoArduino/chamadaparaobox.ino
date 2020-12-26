const int BUTTON = 2;
int BUTTONstate = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON,INPUT);

}

void loop() {
  Serial.println("DASDAASDASDASDSADSD");
  delay(1000);
  BUTTONstate = digitalRead(BUTTON);

  if (BUTTONstate == HIGH)
     Serial.println("K2PQ"); 
  
}
