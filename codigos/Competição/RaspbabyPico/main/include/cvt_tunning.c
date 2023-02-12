/*
      Implementação da contagem de rpm da movida
*/
int rpmMovida;
int hallMovida = 22, falha;
int cfg;
volatile byte pulsos = 0;
unsigned int pulsos_por_volta_mvd = 4; // Quantidade de imas na polia
unsigned int minuto = 60 * (1000 / TIMER_INTERVAL_MS); // 60000 ms (1 minuto) em funcao do timer da interrupcao

// REFRESH RATE EM ms
const int refresh_rate = 250; //ms

void contador(); // Contador de pulsos da motriz
void error(); // Vai emitir um sinal no led da placa de acordo com o codigo do erro
void criarArquivo(); // Função para criar o arquivo e verificar o nome dele, caso o nome do arquivo ja exista
void config();


void TuningSetup()
{
  attachInterrupt(digitalPinToInterrupt(hallMovida), contador2, RISING);

  Serial.println("CVT Tuning inicializado");
}

int setRpmMovida()
{ 
  rpmMovida = (pulsos * minuto) / pulsos_por_volta_mvd;
  pulsos = 0;
  return rpmMovida;
}

void contador(){                             //Contador de pulsos da motriz
    pulsos++;
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