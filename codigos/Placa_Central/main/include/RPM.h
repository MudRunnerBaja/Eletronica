/**
 * Project Classes Placa Central
 */


#ifndef _RPM_H
#define _RPM_H

#include "ContadorPorIntervalo.h"
#include "Setupable.h"


class RPM: public ContadorPorIntervalo, public Setupable {
public: 
    
bool setup();

bool test();

bool testChosen(int escolhido);
    
int getRPM();
    
int updateRPM();

};

#endif //_RPM_H