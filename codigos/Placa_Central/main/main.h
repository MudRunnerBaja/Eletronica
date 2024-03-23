/**
 * Project Classes Placa Central
 */

#ifndef _MAIN_H
#define _MAIN_H

#include <Arduino.h>

#include "include/Constantes.h"

class Main
{
public:
    /**
     * @param repeating_timer
     */
    bool UpdateData(struct repeating_timer *t);

    /**
     * @param repeating_timer
     */
    bool WriteSD(struct repeating_timer *t);

    void Setup();

    void setup1();

    void loop();

    void loop1();
};

#endif //_MAIN_H