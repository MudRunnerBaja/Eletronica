/**
 * Project Classes Placa Central
 */


#ifndef _CARTAOSD_H
#define _CARTAOSD_H

#include "Setupable.h"
#include "Setupable.h"


class CartaoSD: public Setupable, public Setupable {
public: 
    void Attribute1;
    
void criarArquivoDados();
    
void sdCardSetup();
    
/**
 * @param int
 * @param int
 * @param int
 * @param float float
 */
void writeData(void int, void int, void int, void float float);
    
bool testarCartaoSD();
    
void Operation1();
private: 
    String nomeArquivo;
    File arquivoDados;
    
string getNomeArquivo();
};

#endif //_CARTAOSD_H