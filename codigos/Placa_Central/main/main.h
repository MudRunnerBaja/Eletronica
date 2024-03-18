/**
 * Project Classes Placa Central
 */


#ifndef _MAIN_H
#define _MAIN_H

#include <Arduino.h>
#include <RPi_Pico_ISR_Timer.hpp> // Manipuladores de Interrupção
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h> // Manipuladores de Interrupção
#include "include/Instancia.h"
#include "include/Constantes.h"

class Main {
public: 
    bool setupCompleto;
    unsigned long tempoTotal;
    unsigned long tempoInicial;
    RPI_PICO_Timer Core0Timer0;
    RPI_PICO_Timer Core1Timer1;
    Instancia instancia;
    
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
    
/**
 * @param bool
 */
Instancia gerarInstancia(struct repeating_timer *t);
};

#endif //_MAIN_H