#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

/*
Variaveis e funções "1" são referentes a motriz, variaveis e funcões "2" são referente a movida e variaveis e funções "3" são referentes a velocidade
Exemplo: 
rpm1 = rpm da motriz / rpm2 = rpm da movida
contador1 = contador da motriz / contador2 = contador da movida
*/
File myFile;
TinyGPS gps;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int rpm1, rpm2, velo;
int hall1, hall2, falha, chipSelect = 53;
int cfg;
String arq = "cvt_00.csv";
volatile byte pulsos1, pulsos2;
unsigned long timeold, date, gpstime, milisec;
unsigned int pulsos_por_volta_mtz = 1;            
unsigned int pulsos_por_volta_mvd = 4;          //Quantidade de imas na polia


//REFRESH RATE EM ms
const int refresh_rate = 250; //ms

void contador1(){                             //Contador de pulsos da motriz
    pulsos1++;
}

void contador2(){                             //Contador de pulsos da movida
    pulsos2++;
}


void error(){                               //Vai emitir um sinal no led da placa de acordo com o codigo do erro
  switch (falha)
  {
  case 0:
    lcd.clear();
    lcd.write("Erro no SD");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    break;
  
  case 1:
    lcd.clear();
    lcd.write("Erro no arq.");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(750);
    break;

  case 2:
    lcd.clear();
    lcd.write("SD Cheio");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  error();
}

void criarArquivo(){                        //Função para criar o arquivo e verificar o nome dele, caso o nome do arquivo ja exista
    int i = 0;                              //ele ira aumentar um numero no nome do arquivo, e ira verificar de novo, até que não haja um arquivo do mesmo nome
    char unidade;

    while (SD.exists(arq) == 1)
    {
        i++;
        if(i>99){
          falha = 2;
          Serial.print("Armazenamento cheio");
          error();
        }
        int unidade, dezena;
        if (i > 9)
        {
            char y[0];
            int z;

            z = (i/10);
            itoa(z,y,10);                 //Converte Int em char
            arq[4] = y[0];

            z = (i%10);
            itoa(z,y,10);                 //Converte Int em char
            arq[5] = y[0];
        }
        else{
          char y[0];

          itoa(i, y, 10);
          arq[5] = y[0];
        }
    }

    Serial.print("Arquivo ");
  	Serial.print(arq);
  	Serial.println(" criado");

    File myFile = SD.open(arq, FILE_WRITE);
    if (myFile){
    }else{
      Serial.print("Erro na abertua/criação do arquivo");
      falha = 1;
      error();
    }

    myFile.print("Time;Milisec;RPM Motriz;RPM Movida;km/h; refresh rate: ");
    myFile.print(refresh_rate);
    myFile.print("ms, Config. N: ");
    myFile.print(cfg);
    myFile.println();
    myFile.close();

    lcd.clear();
    lcd.print(arq);
    delay(3000);
}

//MENU DE SELEÇÃO DAS CONFIGURAÇÕES
void config(){
  int botao = 0;

  //INTERFACE DE SELECIONAR AS CONFIGURAÇÕES DA CVT
  while (bool done = false)   
  {
    lcd.clear();
    lcd.print("Config N:");

    int vlr = analogRead(botao);
    if(vlr < 250){cfg++;}
    if(vlr < 450){cfg--;}
    if(vlr < 920){done = true;}

    lcd.setCursor(0,1);
    lcd.print(cfg);
    delay(75);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600);
  lcd.begin(16,2);

  Serial.println("Inicializando...");
  lcd.clear();
  lcd.write("CVT Tunning");
  Serial.println("CVT Tunning V 1.3.1");
  delay(500);

  pinMode(LED_BUILTIN, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("Inicialização do cartão falhou");
    falha = 0;
    error();
  }

  
  config();

  criarArquivo();
  delay(1500);  
  hall1 = 19;                                // Define que o sensor hall da motriz sera ligado na porta 19
  hall2 = 20;                                // Define que o sensor hall da movida sera ligado na porta 20

  attachInterrupt(digitalPinToInterrupt(hall1), contador1, RISING);
  attachInterrupt(digitalPinToInterrupt(hall2), contador2, RISING);

  Serial.println("Finalizada a inicalizacao");
}


void loop()
{ 
  if (millis() - timeold >= refresh_rate)
  {
    detachInterrupt(digitalPinToInterrupt(hall1));
    detachInterrupt(digitalPinToInterrupt(hall2));

    while (Serial1.available() > 0)
      gps.encode(Serial1.read());

    velo = gps.f_speed_kmph();
    gps.get_datetime(&date, &gpstime, &milisec);

    digitalWrite(LED_BUILTIN, HIGH);

    rpm1 = (60 * 1000 / pulsos_por_volta_mtz ) / (millis() - timeold) * pulsos1;
    rpm2 = (60 * 1000 / pulsos_por_volta_mvd ) / (millis() - timeold) * pulsos2;

    timeold = millis();
    pulsos1 = 0;
    pulsos2 = 0;
  
    Serial.print("RPM Motriz = ");          //Imprime os dados de rpm no serial
    Serial.println(rpm1, DEC);
    Serial.print("RPM Movida = ");
    Serial.println(rpm2, DEC);
    Serial.print("Velocidade = ");
    Serial.println(velo, DEC);
    Serial.println();

    File myFile = SD.open(arq, FILE_WRITE);      //Grava os dados no cartão SD
    if (myFile){
    }else{
      Serial.print("Erro na abertua/criação do arquivo");
      falha = 1;
      error();
    }
    myFile.print(gpstime);
    myFile.print(";");
    myFile.print(milisec);
    myFile.print(";");
    myFile.print(rpm1);
    myFile.print(";");
    myFile.print(rpm2);
    myFile.print(";");
    myFile.print(velo);
    myFile.println();
    myFile.close();

    lcd.clear();
    lcd.write("Motriz:     ");
    lcd.print(rpm1);
    lcd.setCursor(0,2);
    lcd.write("Movida:     ");
    lcd.print(rpm2);

    attachInterrupt(digitalPinToInterrupt(hall1), contador1, RISING);
    attachInterrupt(digitalPinToInterrupt(hall2), contador2, RISING);
  }
}
