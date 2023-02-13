#include <SPI.h>
#include <SD.h>

int SCKPIN = 10;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO
int CSPIN = 13;

String arq = "dados000.csv";

File arquivoDados;

bool erro = false;
unsigned long tempo = 0, tempobase = 0;

void falha(){
    digitalWrite(LED_BUILTIN, LOW);
    erro = true;
    Serial.println("======FALHA SD CARD======");
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
    SPI1.begin(true);
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
        // Serial.println("Nomeando colunas como:");
        //Serial.println("data;tempo;vel;rpm;tempcvt;comb;movida;latitude;longitude");

        //arquivoDados.println("data;month;year;hour;min;seconds;milisecvel;rpm;tempcvt;comb;satelites;latitude;longitude");        arquivoDados.close();
        arquivoDados.println("data;tempo(ms);velo;rpm;tempcvt;comb;movida;latitude;longitude");
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
    erro = false;
    tempo = tempobase = millis();
}


void writeData(float vel, int rpm, float tempcvt, int comb, int rpmMvd)
{
    if (erro)
    {
        sdcardSetup();
        return;
    }
    
    // Testes de velocidade de escrita
    unsigned long t2, t1;
    t1 = micros();


    arquivoDados = SD.open(arq, FILE_WRITE);
    if (arquivoDados) {
        Serial.print("Escrevendo em ");
        Serial.print(arq);Serial.println("...");

        arquivoDados.print(datahj);
        arquivoDados.print(";");
        arquivoDados.print(tempo);
        arquivoDados.print(";");
        arquivoDados.print(vel);
        arquivoDados.print(";");
        arquivoDados.print(rpm);
        arquivoDados.print(";");
        arquivoDados.print(tempcvt);
        arquivoDados.print(";");
        arquivoDados.print(comb);
        arquivoDados.print(";");
        arquivoDados.print(rpmMvd);
        arquivoDados.print(flat, 8);
        arquivoDados.print(";");
        arquivoDados.println(flon, 8);

        t2 = micros();
        unsigned long t = t2 - t1;
        String dt = String(t, DEC);
        // Serial.println("Feito. Tempo total de escrita (us): " + dt);
        arquivoDados.close();
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