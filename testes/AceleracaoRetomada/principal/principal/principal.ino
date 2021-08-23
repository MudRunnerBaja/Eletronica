#include <SoftwareSerial.h>
#include <Arduino_JSON.h>

long debouncing_time = 100; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;
int start_time = 0;
int end_time = 0;
int m30_timer_first = 0;
int m30_timer_second = 0;
bool started = false;
bool m30_finish = false; // Controlar para receber apenas 2 dados do 30m

int ir_sensor = 3;

SoftwareSerial m30(4,5);

void setup() {
  Serial.begin(9600);
  m30.begin(9600);

  attachInterrupt(digitalPinToInterrupt(ir_sensor), interruptFunc, RISING);

}

void loop() {
  while (m30.available()) {
    if (m30.read() == '!' && started == true && m30_finish == false) {
      if (m30_timer_first == 0) {
        m30_timer_first = millis() - start_time;
        Serial.println("Primeiro sinal 30m");
      }
      else {
        m30_timer_second = millis() - start_time;
        m30_finish = true;
        Serial.println("Segundo sinal 30m");
      }
    }
  }

}

void interruptFunc() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000)
  {
    // iniciando teste
    if (start_time == 0) {
      start_time = millis();
      started = true;
      Serial.println("Comecou");
    }
    else {
      end_time = millis() - start_time;
      started = false;
      Serial.println("Acabou");
      sendData();
      resetTest();
    }

    last_micros = micros();
  }
}

void sendData() {
  JSONVar json;
  json["m30_first"] = m30_timer_first/1000;
  json["m30_second"] = m30_timer_second/1000;
  json["end"] = end_time/1000;
  Serial.println(json);
}

void resetTest() {
  start_time = 0;
  end_time = 0;
  m30_timer_first = 0;
  m30_timer_second = 0;
  started = false;
  m30_finish = false;
}
