/*
        Implementação do módulo do cartão SD
*/
#ifndef CARTAO_SD
#define CARTAO_SD

#include <declarations.h>

        // CARTAO SD
#define SCKPIN 10
#define TXPIN 11 // MOSI
#define RXPIN 12 // MISO
#define CSPIN 13

String arq = "dados000.csv";
String checkCard = "check.txt";
byte tipoFalha = 0;
File arquivoDados;

bool erro = false;
unsigned long tempo = 0, tempobase = 0;
unsigned long t2, t1;

void falha(int i);
void CriarArquivoDados();

void sdcardSetup()
{
    // Testes de velocidade de escrita
    t1 = micros();

    // Pinos e bibliotecas
    SPI1.setRX(RXPIN);
    SPI1.setTX(TXPIN);
    SPI1.setSCK(SCKPIN);
    SPI1.setCS(CSPIN);
    SPI1.begin(true);
    SD.begin(CSPIN, SPI1);

    File checkSD = SD.open(checkCard, FILE_WRITE);
    checkSD.close();
    if (!SD.exists(checkCard))
    {
        falha(1);
        return;
    }

    void CriarArquivoDados();

    tempo = tempobase = millis();
}


void writeData(float vel, int rpm, float tempcvt, int comb, int rpmMvd)
{
    if (tipoFalha % 2)
    {
        sdcardSetup();
        return;
    }
    
    if (tipoFalha > 1)
    {
        CriarArquivoDados();
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
    falha(3);
    }
}

void falha(int i)
{
    erro = true;
    switch (i)
    {
    case 1:
        Serial.println("===== NO SD CARD =====");
        tipoFalha = tipoFalha | 1;
        break;
    case 2:
        Serial.println("===== Erro ao criar o arquivo =====");
        tipoFalha = tipoFalha | 2;
        break;
    case 3:
        Serial.println("===== Erro ao abrir o arquivo =====");
        tipoFalha = tipoFalha | 4;
        break;
    default:
        Serial.println("====== FALHA SD CARD DESCONHECIDA ======");
        break;
    }
}

void CriarArquivoDados()
{
    // Retorna se não há cartão sd detectado
    if((tipoFalha % 2)) return;

    if((tipoFalha > 1))
    {
        // Criando os arquivos txt
        int i = 0;  // ele ira aumentar um numero no nome do arquivo, e ira verificar de novo, até que não haja um arquivo do mesmo nome
        char unidade;
        while ((SD.exists(arq)) && (i < 100))
        {
            i++;
            int unidade = (i % 10), dezena = ((i / 10) % 10), centena = (i/100);
            char y[1];
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
            falha(2);
            return;
        }
        Serial.print("Arquivo "); Serial.print(arq); Serial.println(" criado.");
    }

    if (arquivoDados) {
        arquivoDados.println("data;tempo(ms);velo;rpm;tempcvt;comb;movida;latitude;longitude");
        t2 = micros();
        unsigned long t = t2 - t1;
        String dt = String(t, DEC);
        Serial.println("Feito. Tempo para criar: " + dt);
    }
    else {
        Serial.println("Erro ao abrir o arquivo.");
        falha(3);
        return;
        }
    
    if (!tipoFalha) erro = false;

}
#endif

// https://arduino-pico.readthedocs.io/en/latest/fs.html
// https://docs.arduino.cc/learn/communication/spi
// Checar datasheet da placa SD