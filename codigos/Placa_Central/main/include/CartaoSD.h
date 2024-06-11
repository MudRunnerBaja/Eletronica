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

class CartaoSD : public Setupable
{
public:
    static CartaoSD *instance;
    static CartaoSD *Setup();

    bool possuiNome = false;
    bool arquivoCriado = false;

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

        Serial.println("=== CARTÃO SD ===");
        if (!arquivoCriado)
        {
            Serial.println("Não há arquivo criado.");
            return true;
        }

        if (!SD.exists(nomeArquivo))
        {
            Serial.println("O sistema acredita que o arquivo foi criado, mas não detecta o arquivo pelo nome.");
            return false;
        }

        arquivoDados = SD.open(nomeArquivo, O_READ);

        if (!arquivoDados)
        {
            Serial.println("O sistema encontrou o arquivo pelo nome, mas não conseguiu abrí-lo.");

            arquivoDados.close();
            return false;
        }

        arquivoDados.close();
        Serial.println("A gravação no cartão SD parece normal.");
        return true;
    }

    /**
     * @param int
     * @param int
     * @param int
     * @param float float
     */
    void writeData(int a, int b, int c, float d, float e)
    {
        if (!arquivoCriado)
        {
            return;
        }

        return;
    }

    bool testarCartaoSD()
    {
        return true;
    }

    CartaoSD(CartaoSD &outro) = delete;

    CartaoSD()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    String nomeArquivo;
    File arquivoDados;
    String getNomeArquivo();
    const char *HEADER_STRING = "data;tempo(ms);velo;rpm;tempcvt;comb;movida;latitude;longitude";

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
                Serial.println("Erro ao criar o arquivo.");
                arquivoCriado = false;
                return;
            }

            if (Serial)
            {
                Serial.print("Arquivo ");
                Serial.print(nomeArquivo);
                Serial.println(" criado.");
            }

            if (arquivoDados)
            {
                arquivoCriado = true;
                arquivoDados.println(HEADER_STRING);

                t2 = micros();
                unsigned long t = t2 - t1;
                String dt = String(t, DEC);
                Serial.println("Feito. Tempo para criar: " + dt);

                arquivoDados.close();
            }
            else
            {
                Serial.println("Erro ao abrir o arquivo.");
                return;
            }
        }
    */
};

CartaoSD *CartaoSD::instance{nullptr};
CartaoSD *CartaoSD::Setup()
{
    if (instance == NULL)
    {
        instance = new CartaoSD();
    }

    SPI1.setRX(SD_RXPIN); // MISO
    SPI1.setTX(SD_TXPIN); // MOSI
    SPI1.setSCK(SD_SCKPIN);
    SPI1.setCS(SD_CSPIN);

    SPI1.begin(true);

    if (!SD.begin(SD_CSPIN, SPI1))
    {
        Serial.println("Erro inicialização SD");
        return instance;
    }
    return instance;
}

#endif //_CARTAOSD_H