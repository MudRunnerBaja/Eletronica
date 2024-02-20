/**
 * Project Classes Placa Central
 */


#ifndef _RPM_H
#define _RPM_H

#include "ContadorPorIntervalo.h"
#include "Setupable.h"


class RPM: public ContadorPorIntervalo, public Setupable {
public: 
    
void rpmSetup();
    
int getRPM();
    
int updateRPM();
    
bool testarRPM();
};

#endif //_RPM_H