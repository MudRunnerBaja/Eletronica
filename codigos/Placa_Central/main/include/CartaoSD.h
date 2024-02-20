/**
 * Project Classes Placa Central
 */


#ifndef _CARTAOSD_H
#define _CARTAOSD_H

#include "Setupable.h"
#include <SPI.h>    // SPI para cartão SD
#include <SD.h>     // SD Filesystem

class CartaoSD: public Setupable {
public: 
    
void criarArquivoDados();
    
void sdCardSetup();

bool setup();

bool test();

bool testChosen(int escolhido);
    
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