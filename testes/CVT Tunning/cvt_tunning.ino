#include <SPI.h>
#include <SD.h>
/*
Variaveis e funções "1" são referentes a motriz, variaveis e funcões "2" são referente a movida
Exemplo: 
rpm1 = rpm da motriz / rpm2 = rpm da movida
contador1 = contador da motriz / contador2 = contador da movida
*/
File myFile;

int rpm1, rpm2;
int hall1, hall2;
String arq = "cvt_tunning00.csv";
volatile byte pulsos1, pulsos2;
unsigned long timeold;
unsigned int pulsos_por_volta = 1;

void contador1()
{
    pulsos1++;
}

void contador2(){
    pulsos2++;
}

void criarArquivo(){
    int i = 0;
    while (SD.exists(arq) == 1)
    {
        i++;
        if (i > 9)
        {
            arq[11] = char(i/10);
            arq[12] = char(i%10);
        }
        else arq[12] = char(i);
    }
    Serial.print("Arquivo ");
  	Serial.print(arq);
  	Serial.println(" criado");
    myFile = SD.open(arq);
    myFile.close();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Inicializando...");
  Serial.println("CVT Tunning V 1.0");
  pinMode(LED_BUILTIN, OUTPUT);
  SD.begin();
  criarArquivo();
  hall1 = 2; // Define que o sensor hall da motriz sera ligado na porta 2
  hall2 = 3; // Define que o sensor hall da movida sera ligado na porta 3
  pulsos1 = 0;
  pulsos2 = 0;
  rpm1 = 0;
  rpm2 = 0;
  timeold = 0;
  attachInterrupt(digitalPinToInterrupt(hall1), contador1, FALLING);
  attachInterrupt(digitalPinToInterrupt(hall2), contador2, FALLING);
  Serial.println("Finalizada a inicalizacao");
}


void loop()
{
  if (millis() - timeold >= 1000)
  {
    detachInterrupt(digitalPinToInterrupt(hall1));
    detachInterrupt(digitalPinToInterrupt(hall2));
    rpm1 = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos1;
    rpm2 = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos2;
    timeold = millis();
    pulsos1 = 0;
    pulsos2 = 0;
    Serial.println();
    Serial.print("RPM Motriz = ");
    Serial.println(rpm1, DEC);
    Serial.print("RPM Movida = ");
    Serial.println(rpm2, DEC);
    myFile = SD.open(arq, FILE_WRITE);
    myFile.println(rpm1);
    myFile.print(",");
    myFile.print(rpm2);
    myFile.close();
    digitalWrite(LED_BUILTIN, HIGH);
    attachInterrupt(digitalPinToInterrupt(hall1), contador1, FALLING);
    attachInterrupt(digitalPinToInterrupt(hall2), contador2, FALLING);
  }
}
