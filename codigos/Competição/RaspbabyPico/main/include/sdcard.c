#include <SPI.h>
#include <SD.h>

pin_size_t RXPIN = 12; // MISO
pin_size_t CSPIN = 13;
pin_size_t SCKPIN = 10;
pin_size_t TXPIN = 11; // MOSI

String arq = "dados000.csv";

File arquivoDados;

bool falha = false;

void falha(){
    digitalWrite(LED_BUILTIN, LOW);
    falha = true;
    Serial.println("==========FALHA==========");
}

void sdcardSetup()
{
    // Testes de velocidade de escrita
    unsigned long t2, t1;
    t1 = micros();

    // Pinos e bibliotecas
    SPI1.setRX(RXPIN);
    SPI1.setTX(TXPIN);
    SPI1.setSCK(SCKPIN);
    SPI1.setCS(CSPIN);
    SPI1.begin();
    SD.begin(CSPIN, SPI1);

    // Criando os arquivos txt
    int i = 0;                              //ele ira aumentar um numero no nome do arquivo, e ira verificar de novo, até que não haja um arquivo do mesmo nome
    char unidade;
    while ((SD.exists(arq)) && (i < 1000))
    {
        i++;
        int unidade = (i % 10), dezena = ((i / 10) % 10), centena = (i/100);
        char y[0];
        itoa(centena,y,10);
        arq[5] = y[0];
        itoa(dezena,y,10);
        arq[6] = y[0];
        itoa(unidade,y,10);
        arq[7] = y[0];
    }

    File arquivoDados = SD.open(arq, FILE_WRITE);

    if (!SD.exists(arq))
    {
        Serial.println("Erro ao criar o arquivo.");
        falha();
        return;
    }
    Serial.print("Arquivo "); Serial.print(arq); Serial.println(" criado.");

    if (arquivoDados) {
        Serial.println("Nomeando colunas como:");
        Serial.println("vel,rpm,tempcvt,comb");

        arquivoDados.println("vel,rpm,tempcvt,comb");
        arquivoDados.close();

        t2 = micros();
        unsigned long t = t2 - t1;
        String dt = String(t, DEC);
        Serial.println("Feito. Tempo para criar: " + dt);
    }
    else {
        Serial.println("Erro ao abrir o arquivo.");
        falha();
        return;
        }
    falha = false;
}


void writeData(float vel, int rpm, float tempcvt, int comb)
{
    if (falha)
    {
        sdcardSetup();
        return;
    }
    
    // Testes de velocidade de escrita
    unsigned long t2, t1;
    t1 = micros();
    String printData = String(vel);
    printData += ",";
    printData += rpm;
    printData += ",";
    printData += tempcvt;
    printData += ",";
    printData += comb;

    arquivoDados = SD.open(arq, FILE_WRITE);
    if (arquivoDados) {
        Serial.print("Escrevendo em ");
        Serial.print(arq);Serial.println("...");

        arquivoDados.println(printData);
        arquivoDados.close();

        Serial.println(printData);

        t2 = micros();
        unsigned long t = t2 - t1;
        String dt = String(t, DEC);
        Serial.println("Feito. Tempo total de escrita (us): " + dt);
    }
    else    {
    Serial.println("Erro ao abrir "); Serial.println(arq);
    falha();
    }
}

// https://arduino-pico.readthedocs.io/en/latest/fs.html
// https://docs.arduino.cc/learn/communication/spi
// Checar datasheet da placa SD
// SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));