#line 1 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\include\\sdcard.c"
#include <SPI.h>
#include <SD.h>

pin_size_t RXPIN = 12; // MISO
pin_size_t CSPIN = 13;
pin_size_t SCKPIN = 10;
pin_size_t TXPIN = 11; // MOSI

String arq = "dados000.csv";

File arquivoDados;

bool erro = false;

void falha(){
    digitalWrite(LED_BUILTIN, LOW);
    erro = true;
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
        //Serial.println("data;month;year;hour;min;seconds;milisecvel;rpm;tempcvt;comb;satelites;latitude;longitude");

        //arquivoDados.println("data;month;year;hour;min;seconds;milisecvel;rpm;tempcvt;comb;satelites;latitude;longitude");        arquivoDados.close();
        arquivoDados.println("data;time;velo;rpm;tempcvt;comb;satelites;latitude;longitude");
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
}


void writeData(float vel, int rpm, float tempcvt, int comb)
{
    if (erro)
    {
        sdcardSetup();
        return;
    }
    
    // Testes de velocidade de escrita
    unsigned long t2, t1;
    t1 = micros();
    String printData = String(date);
    printData += ";";
    printData += String(gpstime);
    printData += ";";
    printData += String(vel);
    printData += ";";
    printData += rpm;
    printData += ";";
    printData += tempcvt;
    printData += ";";
    printData += comb;
    printData += ";";
    printData += gps.satellites(), TinyGPS::GPS_INVALID_SATELLITES, 5;
    printData += ";";

    arquivoDados = SD.open(arq, FILE_WRITE);
    if (arquivoDados) {
        Serial.print("Escrevendo em ");
        Serial.print(arq);Serial.println("...");

       /* arquivoDados.print(day);
        arquivoDados.print(";");
        arquivoDados.print(month);
        arquivoDados.print(";");
        arquivoDados.print(year);
        arquivoDados.print(";");
        arquivoDados.print(hour);
        arquivoDados.print(";");
        arquivoDados.print(minute);
        arquivoDados.print(";");
        arquivoDados.print(second);
        arquivoDados.print(";");
        arquivoDados.print(milsec);
        arquivoDados.print(";");*/
        arquivoDados.print(printData);
        arquivoDados.print(flat, 8);
        arquivoDados.print(";");
        arquivoDados.println(flon, 8);
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