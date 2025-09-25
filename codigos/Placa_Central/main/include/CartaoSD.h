/**
 * Project Classes Placa Central
 */

#ifndef _CARTAOSD_H
#define _CARTAOSD_H

#include "Setupable.h"
#include <SPI.h> // SPI para cartão SD
#include <SD.h>  // SD Filesystem
// #include "GPS.h" // GPS
#include "Constantes.h"

class CartaoSD
{
public:
    CartaoSD() = default;

public:
    static CartaoSD *GetInstance();

    bool possuiNome = false;
    bool arquivoCriado = false;

    // void escreverSD(DadosCompartilhamento dados)
    // {
    //     if (!arquivoCriado)
    //     {
    //         return;
    //     }

    //     return;
    // }

    bool Loop()
    {
        if (!arquivoCriado)
        {
            // criarArquivoDados();
        }

        return arquivoCriado;
    }

    bool Debug()
    {
        if (!Serial)
        {
            return true;
        }

        D_println("=== CARTÃO SD ===");
        if (!arquivoCriado)
        {
            D_println("Não há arquivo criado.");
            return true;
        }

        if (!SD.exists(nomeArquivo))
        {
            D_println("O sistema acredita que o arquivo foi criado, mas não detecta o arquivo pelo nome.");
            return false;
        }

        arquivoDados = SD.open(nomeArquivo, O_READ);

        if (!arquivoDados)
        {
            D_println("O sistema encontrou o arquivo pelo nome, mas não conseguiu abrí-lo.");

            arquivoDados.close();
            return false;
        }

        arquivoDados.close();
        D_println("A gravação no cartão SD parece normal.");
        return true;
    }

    /**
     * @param int
     * @param int
     * @param int
     * @param float float
     */
    /*
void writeData(int a, int b, int c, float d, float e)
{
    if (!arquivoCriado)
    {
        return;
    }

    return;
}
*/
    bool testarCartaoSD()
    {
        return true;
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
        // Serial.print(">");
        // Serial.print(definitiveNum);
        // Serial.println("<");
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
            arquivoDados.println("tempo(ms);velo;rpm;tempcvt;comb;nivelFreio;pressaoFreio;TensaoBat;latitude;longitude");
            arquivoDados.close();
        }
    }

private:
    String nomeArquivo;
    File arquivoDados;
    static CartaoSD *instance;

    static String getNomeArquivo();
    // static constexpr const char HEADER_STRING = "tempo(ms);velo;rpm;tempcvt;comb;nivelxFreio;pressaoFreio";

    /*
        void criarArquivoDados()
        {
            // TODO/WIP
            // Lógica de criação dos arquivos csv
            // O nome dos arquivos sem referência de tempo serão dados000.csv, onde 000 representam números.
            // O nome de arquivos com referência de tempo serão datahoje no formato dd-mm-aaaa

            if (gps.possuiData)
            {
                nomeArquivo = String("");
                nomeArquivo = String(gps.getDataHoje().replace('/', '-'));
                nomeArquivo = String(nomeArquivo)
            }
            else
            {
                int i = 0; // Incremetará o dígito no nome do arquivo até que não haja um arquivo com mesmo nome
                char *nomeTemporario = "dados000";
                while ((SD.exists(nomeTemporario)) && i < 1000)
                {
                    int count = i.toInt();
                    count++;

                    int unidade = (i % 10),
                        dezena = ((i / 10) % 10),
                        centena = (i / 100);
                    char y[1]; // Buffer. itoa converte um int em char e posiciona em um endereço de memória.

                    itoa(centena, y, 10);
                    nomeTemporario[5] = y[0];
                    itoa(dezena, y, 10);
                    nomeTemporario[6] = y[0];
                    itoa(unidade, y, 10);
                    nomeTemporario[7] = y[0];
                }
                nomeArquivo = String(nomeTemporario);
            }

            File arquivoDados = SD.open(nomeArquivo, FILE_WRITE);

            if (!SD.exists(nomeArquivo))
            {
                D_println("Erro ao criar o arquivo.");
                arquivoCriado = false;
                return;
            }

            if (Serial)
            {
                D_print("Arquivo ");
                D_print(nomeArquivo);
                D_println(" criado.");
            }

            if (arquivoDados)
            {
                arquivoCriado = true;
                arquivoDados.println(HEADER_STRING);

                t2 = micros();
                unsigned long t = t2 - t1;
                String dt = String(t, DEC);
                D_println("Feito. Tempo para criar: " + dt);

                arquivoDados.close();
            }
            else
            {
                D_println("Erro ao abrir o arquivo.");
                return;
            }
        }
    */
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