long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
int ir_sensor = 3;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ir_sensor), interruptFunc, RISING);
}

void loop() {

}

void interruptFunc() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000)
  {
    Serial.print('!');
    last_micros = micros();
  }
}
