// DECLARAÇÃO DE FUNÇÕES
void enviaMensagem();
void recebeMensagem();
String createTestCsv();

void setup() {
  Serial.begin(9600);

  Serial1.setRX(1);
  Serial1.setTX(0);
  Serial1.setFIFOSize(128);
  Serial1.begin(9600);

  delay(2000);
  Serial.println("Fim Setup");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  enviaMensagem();
  recebeMensagem();
}

void enviaMensagem() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial1.println(createTestCsv());
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(500);
}

void recebeMensagem() {
  int avlb = Serial1.available();
  delay(10);
  if (avlb > 0){
    Serial.println(Serial1.available());
  }
  /*
  Serial.print("=====RECEBIDO=====\n");
  Serial.println(Serial1.readStringUntil('\n'));
  Serial.println("");
  */
  return;
}

String createTestCsv() {
  int rpm = random(4800);
  float tCvt  = random(100, 10000) / 100.0; 
  float vel  = random(100, 3750) / 100.0; 
  short comb = random(1, 3);
  int mvd = random(4800);

  String csvHeader = String("rpm,tCvt,vel,comb,mvd\n");
  String data = String(rpm);
  data = String(data + ",");
  data = String(data + tCvt);
  data = String(data + ",");
  data = String(data + vel);
  data = String(data + ",");
  data = String(data + comb);
  data = String(data + ",");
  data = String(data + mvd);
  // data = String(csvHeader + data);

  char* toSend;

  data.toCharArray(toSend, 128);

  Serial.print("=====ENVIADO=====");
  Serial.println("");
  Serial.println(data);
  Serial.println("");
  return data;
}