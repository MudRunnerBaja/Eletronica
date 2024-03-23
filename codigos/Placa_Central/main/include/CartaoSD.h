/**
 * Project Classes Placa Central
 */

#ifndef _CARTAOSD_H
#define _CARTAOSD_H

#include "Setupable.h"
#include <SPI.h> // SPI para cartão SD
#include <SD.h>  // SD Filesystem
#include "Constantes.h"

class CartaoSD : public Setupable
{
public:
    CartaoSD()
    {
        return;
    }

    bool Setup()
    {

        SPI1.setRX(SD_RXPIN); // MISO
        SPI1.setTX(SD_TXPIN); // MOSI
        SPI1.setSCK(SD_SCKPIN);
        SPI1.setCS(SD_CSPIN);

        SPI1.begin(true);

        if (!SD.begin(SD_CSPIN, SPI1))
        {
            Serial.println("Erro inicialização SD");
            return false;
        }
        return true;
    }

    bool Loop()
    {
        return true;
    }

    bool Debug()
    {
        return true;
    }

    void criarArquivoDados()
    {
        return;
    }

    void sdCardSetup()
    {
        return;
    }

    /**
     * @param int
     * @param int
     * @param int
     * @param float float
     */
    void writeData(int a, int b, int c, float d, float e)
    {
        return;
    }

    bool testarCartaoSD()
    {
        return true;
    }

private:
    String nomeArquivo;
    File arquivoDados;

    String getNomeArquivo();
};

#endif //_CARTAOSD_H