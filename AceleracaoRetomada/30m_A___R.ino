int sensor30 = 6;

void setup() {
  pinMode(sensor30, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(sensor30) == 0) {
    Serial.println('@');
    delay(2000);
  }
}
