#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
int data = 31052023;
int dia, mes, ano;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);   // Serial port to HC12
  HC12.println("Testing HC-12 module range...");
  dia = data/1000000;
  mes = (data/10000) % 100;
  ano = data % 10000;
}

void loop() {

  // Increment the distance counter and print the result to the serial monitor
  //Serial.print("ABCDEFGHIJ");
  Serial.print("123456789");

  // Wait for one second before sending the next message
  delay(1000);

  //HC12.println("ABCDEFGHIJ");
  HC12.print("Data: ");
  HC12.println(data);
  HC12.print("Dia: ");
  HC12.print(dia);
  HC12.print(" | mes: ");
  HC12.print(mes);
  HC12.print(" | ano: ");
  HC12.println(ano);
}