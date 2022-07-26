#include <SPI.h>
#include <SD.h>

// Earle F. Philhower, III Arduino-Pico Documentation
// https://arduino-pico.readthedocs.io/_/downloads/en/latest/pdf/
 
 // Definindo os pinos da interface SPI
#define RXPIN 0 // MISO
#define CSPIN 1
#define SCKPIN 2
#define TXPIN 3 // MOSI

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
    arquivoDados = SD.open("Dados.csv", FILE_WRITE);
    if (arquivoDados) {
        Serial.println("Criando Dados.csv...");

        arquivoDados.println("vel,rpm,tempcvt,comb");
        arquivoDados.close();

        t2 = millis();
        dt = t2 - t1;
        Serial.println("Feito. Tempo para criar: " + dt);
    }
    else    Serial.println("Erro ao abrir Dados.csv");
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

    arquivoDados = SD.open("Dados.csv", FILE_WRITE);
    if (arquivoDados) {
        Serial.println("Escrevendo em dados.csv...");

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