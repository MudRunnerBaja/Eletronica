/**
 * Project Classes Placa Central
 */


#ifndef _SETUPABLE_H
#define _SETUPABLE_H

class Setupable {
public: 
    
virtual bool Setup() = 0;
    
virtual bool Debug() = 0;

virtual bool Test() = 0;
    
/**
 * @param int
 */
virtual bool TestChosen(int escolhido) = 0;
};

#endif //_SETUPABLE_H