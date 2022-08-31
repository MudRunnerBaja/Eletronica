#include <Ds1302.h>
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

/*
Variaveis e funções "1" são referentes a motriz, variaveis e funcões "2" são referente a movida e variaveis e funções "3" são referentes a velocidade
Exemplo: 
rpm1 = rpm da motriz / rpm2 = rpm da movida
contador1 = contador da motriz / contador2 = contador da movida
*/
File myFile;
Ds1302 rtc(28, 31, 30); // 28 - RST ; 30 - DAT ; 31 - CLK
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


int rpm1, rpm2, velo;
float pulsohora;
int hall1, hall2, hall3, falha, chipSelect = 53;
String arq = "cvt_00.csv";
volatile byte pulsos1, pulsos2, pulsos3, pulsomin;
unsigned long timeold, timeold1;
unsigned int pulsos_por_volta = 4;            //Quantidade de imas na polia
unsigned int pulsos_por_volta_velo = 4;       //Quantidade de imas no disco de freio
const float circunferencia_pneu = 167.4876; //EM CM

void contador1(){                             //Contador de pulsos da motriz
    pulsos1++;
}

void contador2(){                             //Contador de pulsos da movida
    pulsos2++;
}

void contador3(){                            //Contador de pulsos da velocidade
    pulsos3++;
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
    Ds1302::DateTime now;
    /*//                    FUNCÃO PARA SETAR O HORARIO
    now.year = 22;
    now.month = 8;
    now.day = 31;
    now.hour = 18;
    now.minute = 1;
    now.second = 0;    
    rtc.setDateTime(&now);
    */
    rtc.getDateTime(&now);
    File myFile = SD.open(arq, FILE_WRITE);
    if (myFile){
    }else{
      Serial.print("Erro na abertua/criação do arquivo");
      falha = 1;
      error();
    }
    myFile.print("Data ");
    myFile.print(now.day);
    myFile.print("/");
    myFile.print(now.month);
    myFile.print("/20");
    myFile.print(now.year);
    myFile.print(",RPM Motriz,RPM Movida,km/h");
    myFile.println();
    myFile.close();

    lcd.clear();
    lcd.print(arq);
    lcd.setCursor(0,2);
    lcd.print(now.day);
    lcd.write("/");
    lcd.print(now.month);
    lcd.write(" ");
    lcd.print(now.hour);
    lcd.write(":");
    lcd.print(now.minute);
    lcd.write(":");
    lcd.print(now.second);
    delay(3000);
}

void setup()
{
  Serial.begin(115200);
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
  rtc.init();
  criarArquivo();
  delay(1500);  
  hall1 = 19;                                // Define que o sensor hall da motriz sera ligado na porta 19
  hall2 = 20;                                // Define que o sensor hall da movida sera ligado na porta 20
  hall3 = 21;                                // Define que o sensor hall da velocidade sera ligado na porta 21
  pulsos1 = 0;
  pulsos2 = 0;
  pulsos3 = 0;
  rpm1 = 0;
  rpm2 = 0;
  velo = 0;
  timeold = 0;
  timeold1 = 0;
  attachInterrupt(digitalPinToInterrupt(hall1), contador1, RISING);
  attachInterrupt(digitalPinToInterrupt(hall2), contador2, RISING);
  attachInterrupt(digitalPinToInterrupt(hall3), contador3, RISING);
  Serial.println("Finalizada a inicalizacao");
}


void loop()
{ 
  if (millis() - timeold >= 100)
  {
    detachInterrupt(digitalPinToInterrupt(hall1));
    detachInterrupt(digitalPinToInterrupt(hall2));

    digitalWrite(LED_BUILTIN, HIGH);

    rpm1 = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos1;
    rpm2 = (60 * 1000 / pulsos_por_volta ) / (millis() - timeold) * pulsos2;
    

    Ds1302::DateTime now;                   //Coleta os dados do rtc      
    rtc.getDateTime(&now);

    timeold = millis();
    pulsos1 = 0;
    pulsos2 = 0;
    

    Serial.print(now.hour);                 //Imprime o horario no serial
    Serial.print(":");
    Serial.print(now.minute);
    Serial.print(":");
    Serial.print(now.second);
    Serial.println();
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
    myFile.print(now.hour);
    myFile.print(":");
    myFile.print(now.minute);
    myFile.print(":");
    myFile.print(now.second);
    myFile.print(",");
    myFile.print(rpm1);
    myFile.print(",");
    myFile.print(rpm2);
    myFile.print(",");
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

  if (millis() - timeold1 >= 1000)
  {
    detachInterrupt(digitalPinToInterrupt(hall3)); 

    pulsomin = (60 * 1000 / pulsos_por_volta_velo ) / (millis() - timeold1) * pulsos3;
    pulsohora = pulsomin * 60;
    velo = (circunferencia_pneu / 100000) * pulsohora;                                    //transforma pulsos por hora em km/h
    timeold1 = millis();
    pulsos3 = 0; 
    attachInterrupt(digitalPinToInterrupt(hall3), contador3, RISING);
  }
}
