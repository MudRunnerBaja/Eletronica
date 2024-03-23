/**
 * Project Classes Placa Central
 */

#ifndef _SETUPABLE_H
#define _SETUPABLE_H

class Setupable
{
public:
    virtual bool Setup() = 0;

    virtual bool Debug() = 0;

    virtual bool Loop() = 0;
};

#endif //_SETUPABLE_H