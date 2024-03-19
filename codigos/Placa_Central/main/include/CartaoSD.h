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
    bool Setup();

    bool Loop();

    bool Debug();

    bool TestChosen(int escolhido);

    void criarArquivoDados();

    void sdCardSetup();

    /**
     * @param int
     * @param int
     * @param int
     * @param float float
     */
    void writeData(int a, int b, int c, float d, float e);

    bool testarCartaoSD();

private:
    String nomeArquivo;
    File arquivoDados;

    String getNomeArquivo();
};

#endif //_CARTAOSD_H