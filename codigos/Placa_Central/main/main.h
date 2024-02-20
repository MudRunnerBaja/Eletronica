/**
 * Project Classes Placa Central
 */


#ifndef _MAIN_H
#define _MAIN_H

class Main {
public: 
    bool setupCompleto;
    ulong tempoTotal;
    ulong tempoInicial;
    RPI_PICO_Timer Core0Timer0;
    RPI_PICO_Timer Core1Timer1;
    Instancia instancia;
    
/**
 * @param repeating_timer
 */
bool UpdateData(void repeating_timer);
    
/**
 * @param repeating_timer
 */
bool WriteSD(void repeating_timer);
    
void setup();
    
void setup1();
    
void loop();
    
void loop1();
    
/**
 * @param bool
 */
Instancia gerarInstancia(void bool);
};

#endif //_MAIN_H