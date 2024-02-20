/**
 * Project Classes Placa Central
 */


#ifndef _SETUPABLE_H
#define _SETUPABLE_H

class Setupable {
public: 
    
virtual bool setup() = 0;
    
virtual bool test() = 0;
    
/**
 * @param int
 */
virtual bool testChosen(int escolhido) = 0;
};

#endif //_SETUPABLE_H