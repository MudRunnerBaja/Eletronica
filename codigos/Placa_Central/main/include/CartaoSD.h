/**
 * Project Classes Placa Central
 */

#ifndef _CARTAOSD_H
#define _CARTAOSD_H

#include "Setupable.h"
#include <SPI.h> // SPI para cartão SD
#include <SD.h>  // SD Filesystem
#include "Constantes.h"

class CartaoSD
{
public:
    CartaoSD() = default;

public:
    static CartaoSD *GetInstance();

    bool possuiNome = false;
    bool arquivoCriado = false;


    bool Loop()
    {
        return arquivoCriado;
    }

    bool Debug()
    {
        return false;
    }


    int getNumFromString(const char name[])
    {
        int numlen = 0;
        bool firstNum = true;
        int definitiveNum;
        for (int i = 0; i < strlen(name); i++)
        {
            if (isdigit(name[i]) && firstNum)
            {
                numlen = strlen(name) - i;
                firstNum = false;
            }
        }

        char namenum[numlen];

        for (int i = 0; i < numlen; i++)
        {
            namenum[i] = name[strlen(name) - numlen + i];
        }
        definitiveNum = atoi(namenum);
        
        return definitiveNum;
    }

    int getHighestNumFromFiles()
    {

        File dir = SD.open("/");
        int highestNumber;
        int currentNumber;
        while (true)
        {

            File entry = dir.openNextFile();
            if (!entry)
            {
                break;
            }
            currentNumber = getNumFromString(entry.name());
            Serial.println(currentNumber);
            if (currentNumber > highestNumber && currentNumber < 1000)
            {
                highestNumber = currentNumber;
            }
            entry.close();
        }
        dir.close();
        return highestNumber;
    }

    void escreverSD(String dados)
    {
        Serial.println("Arquivo escrito sla");
        arquivoDados = SD.open(nomeArquivo, FILE_WRITE);
        arquivoDados.print(millis());
        arquivoDados.print(",");
        arquivoDados.println(dados);
        arquivoDados.close();
    }

    void criarArquivoDados()
    {
        int num = getHighestNumFromFiles();
        Serial.print(">");
        Serial.print(num);
        Serial.println("<");
        nomeArquivo = "test" + String(num + 1) + ".txt";
        Serial.print("nome do arquivo: ");
        Serial.println(nomeArquivo);
        Serial.println("final do nome do arquivo");
        
        arquivoDados = SD.open(nomeArquivo, FILE_WRITE);
        if (arquivoDados)
        {
            Serial.println("Arquivo Criado");
            arquivoDados.println("tempo(ms);velo;rpm;tempcvt;comb;nivelFreio;pressaoFreio;TensaoBat;");
            arquivoDados.close();
        }
    }

private:
    String nomeArquivo;
    File arquivoDados;
    static CartaoSD *instance;

    static String getNomeArquivo();

};

CartaoSD *CartaoSD::instance{nullptr};
CartaoSD *CartaoSD::GetInstance()
{
    if (instance == NULL)
    {
        instance = new CartaoSD();

        SPI1.setRX(SD_RXPIN); // MISO
        SPI1.setTX(SD_TXPIN); // MOSI
        SPI1.setSCK(SD_SCKPIN);
        SPI1.setCS(SD_CSPIN);

        SPI1.begin(true);

        if (!SD.begin(SD_CSPIN, SPI1))
        {
            D_println("Erro inicialização SD");
        }
    }
    return instance;
}

#endif //_CARTAOSD_H