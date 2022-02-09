// Teste Termopar tipo k

#include <max6675.h>
  
/* Definições: GPIOs do Arduino utilizado na comunicação com o 
   MAX6675 */
#define GPIO_SO       2
#define GPIO_CS       3  
#define GPIO_CLK      4
 
/* Definição: baudrate da comunicação com Serial Monitor */
#define BAUDRATE_SERIAL_MONITOR    115200
 
/* Definição: tempo entre leituras do MAX6675 */
#define TEMPO_ENTRE_LEITURAS             1000 //ms
 
/* Criação de objeto para comunicação com termopar */
MAX6675 termopar(GPIO_CLK, GPIO_CS, GPIO_SO);
  
void setup()
{
    Serial.begin(BAUDRATE_SERIAL_MONITOR);
}
 
/* Programa principal */
void loop() 
{  
    Serial.print("Temperatura: "); 
    Serial.print(termopar.readCelsius());
    Serial.println("C"); 
    delay(TEMPO_ENTRE_LEITURAS);
}
