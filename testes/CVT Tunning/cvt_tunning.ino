#include <SPI.h>
#include <SD.h>
/*
Variaveis e funções "1" são referentes a motriz, variaveis e funcões "2" são referente a movida e variaveis e funções "3" são referentes a velocidade
Exemplo: 
rpm1 = rpm da motriz / rpm2 = rpm da movida
contador1 = contador da motriz / contador2 = contador da movida
*/
File myFile;

int rpm1, rpm2, velo;
int hall1, hall2, hall3;
String arq = "cvt_tunning00.csv";
volatile byte pulsos1, pulsos2, pulsos3, pulsohora;
unsigned long timeold;
unsigned int pulsos_por_volta = 1;            //Quantidade de imas na polia
unsigned int pulsos_por_volta_velo = 4;       //Quantidade de imas no disco de freio
unsigned long circunferencia_pneu = 167.4876; //EM CM

void contador1(){                             //Contador de pulsos da motriz
    pulsos1++;
}

void contador2(){                             //Contador de pulsos da movida
    pulsos2++;
}

void contador3(){                            //Contador de pulsos da velocidade
    pulsos3++;
}

void criarArquivo(){                        //Função para criar o arquivo e verificar o nome dele, caso o nome do arquivo ja exista
    int i = 0;                              //ele ira aumentar um numero no nome do arquivo, e ira verificar de novo, até que não haja um arquivo do mesmo nome
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
  hall1 = 2;                              // Define que o sensor hall da motriz sera ligado na porta 2
  hall2 = 3;                              // Define que o sensor hall da movida sera ligado na porta 3
  hall3 = 18;                             // Define que o sensor hall da velocidade sera ligado na porta 18
  pulsos1 = 0;
  pulsos2 = 0;
  pulsos3 = 0;
  rpm1 = 0;
  rpm2 = 0;
  velo = 0;
  timeold = 0;
  attachInterrupt(digitalPinToInterrupt(hall1), contador1, FALLING);
  attachInterrupt(digitalPinToInterrupt(hall2), contador2, FALLING);
  attachInterrupt(digitalPinToInterrupt(hall3), contador3, FALLING);
  Serial.println("Finalizada a inicalizacao");
}


void loop()
{
  if (millis() - timeold >= 1000)
  {
    detachInterrupt(digitalPinToInterrupt(hall1));
    detachInterrupt(digitalPinToInterrupt(hall2));
    detachInterrupt(digitalPinToInterrupt(hall3));
    rpm1 = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos1;
    rpm2 = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos2;
    pulsohora = (360 * 1000 / pulsos_por_volta_velo ) / (millis() - timeold) * pulsos3;
    velo = (circunferencia_pneu * 100000) * pulsohora;                                    //transforma pulsos por hora em km/h
    timeold = millis();
    pulsos1 = 0;
    pulsos2 = 0;
    pulsos3 = 0;
    Serial.println();
    Serial.print("RPM Motriz = ");
    Serial.println(rpm1, DEC);
    Serial.print("RPM Movida = ");
    Serial.println(rpm2, DEC);
    Serial.print("Velocidade = ");
    Serial.println(velo, DEC);
    myFile = SD.open(arq, FILE_WRITE);
    myFile.println(rpm1);
    myFile.print(",");
    myFile.print(rpm2);
    myFile.print(",");
    myFile.print(velo);
    myFile.close();
    digitalWrite(LED_BUILTIN, HIGH);
    attachInterrupt(digitalPinToInterrupt(hall1), contador1, FALLING);
    attachInterrupt(digitalPinToInterrupt(hall2), contador2, FALLING);
  }
}
