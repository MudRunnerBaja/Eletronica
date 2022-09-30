/*
    Escrita de todos os dados no cartão sd
    A ser revisado e testado

    Earle F. Philhower, III Arduino-Pico Documentation
    https://arduino-pico.readthedocs.io/_/downloads/en/latest/pdf/
*/
#include <SPI.h>
#include <SD.h>


 
 // Definindo os pinos da interface SPI
#define RXPIN 16 // MISO
#define CSPIN 17
#define SCKPIN 14
#define TXPIN 15 // MOSI


String arq = "dados00.csv";


File arquivoDados;

void sdcardSetup()
{
    // Pinos e bibliotecas
    SPI.setRX(RXPIN);
    SPI.setTX(TXPIN);
    SPI.setSCK(SCKPIN);
    SPI.setCS(CSPIN);
    // SPI.begin() // ??? Não consigo entender se é necessário
    SD.begin(CSPIN);

    // Testes de velocidade de escrita
    unsigned long t2, t1;
    int dt;
    t1 = millis();

    // Criando os arquivos txt
    int i = 0;                              //ele ira aumentar um numero no nome do arquivo, e ira verificar de novo, até que não haja um arquivo do mesmo nome
    char unidade;
    while (SD.exists(arq) == 1)
    {
        i++;
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

    arquivoDados = SD.open(arq, FILE_WRITE);

    if (arquivoDados) {
        Serial.println("Criando ");
        Serial.print(arq);

        arquivoDados.println("vel,rpm,tempcvt,comb");
        arquivoDados.close();

        t2 = millis();
        dt = t2 - t1;
        Serial.println("Feito. Tempo para criar: " + dt);
    }
    else    Serial.println("Erro ao abrir");
}

void writeData(float vel, int rpm, float tempcvt, int comb)
{
    // Testes de velocidade de escrita
    unsigned long t2, t1;
    int dt;
    t1 = millis();
    String printData = String(vel);
    printData += ",";
    printData += rpm;
    printData += ",";
    printData += tempcvt;
    printData += ",";
    printData += comb;

    arquivoDados = SD.open(arq, FILE_WRITE);
    if (arquivoDados) {
        Serial.println("Escrevendo...");

        arquivoDados.println(printData);
        arquivoDados.close();

        t2 = millis();
        dt = t2 - t1;
        Serial.println("Feito. Tempo total de escrita: " + dt);
    }
    else    Serial.println("Erro ao abrir Dados.csv");
}

// https://docs.arduino.cc/learn/communication/spi
// Checar datasheet da placa SD
// SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));