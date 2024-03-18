/**
 * Project Classes Placa Central
 */


#ifndef _COMBUSTIVEL_H
#define _COMBUSTIVEL_H

#include "Setupable.h"
#include "Constantes.h"


class Combustivel: public Setupable {
public: 
    
bool Setup();

bool Test();

bool Debug();

bool TestChosen(int escolhido);
    
short setNivelAtual();
    
short getNivelAtual();
    
private: 
    short nivelAtual;
};

#endif //_COMBUSTIVEL_H