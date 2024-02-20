/**
 * Project Classes Placa Central
 */


#ifndef _COMBUSTIVEL_H
#define _COMBUSTIVEL_H

#include "Setupable.h"


class Combustivel: public Setupable {
public: 
    enum niveis {
        LOW,
        MED,
        HIGH
    };
    
bool setup();

bool test();

bool testChosen(int escolhido);
    
short setNivelAtual();
    
short getNivelAtual();
    
private: 
    short nivelAtual;
};

#endif //_COMBUSTIVEL_H