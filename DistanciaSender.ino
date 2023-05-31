#include <SoftwareSerial.h>
SoftwareSerial HC12(10, 11); // HC-12 TX Pin, HC-12 RX Pin
int distance = 0;

void setup() {
  Serial.begin(9600);             // Serial port to computer
  HC12.begin(9600);   // Serial port to HC12
  HC12.println("Testing HC-12 module range...");          
}

void loop() {
  
 // Increment the distance counter and print the result to the serial monitor
  distance++;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" meters");

  // Wait for one second before sending the next message
  delay(1000);
 
  HC12.println(distance);
}
