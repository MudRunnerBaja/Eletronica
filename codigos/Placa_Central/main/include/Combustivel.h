/**
 * Project Classes Placa Central
 */


#ifndef _COMBUSTIVEL_H
#define _COMBUSTIVEL_H

#include "Setupable.h"


class Combustivel: public Setupable {
public: 
    enum niveis;
    
void combSetup();
    
short setNivelAtual();
    
short getNivelAtual();
    
bool testarCombustivel();
private: 
    short nivelAtual;
};

#endif //_COMBUSTIVEL_H