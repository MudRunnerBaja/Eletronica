/**
 * Project Classes Placa Central
 */

#include <Arduino.h>
#include <RPi_Pico_ISR_Timer.hpp>    // Manipuladores de Interrupção
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h>      // Manipuladores de Interrupção
#include "include/Instancia.h"

/**
 * DECLARAÇÕES DE FUNÇÕES
 */
bool UpdateData(struct repeating_timer *t);
bool WriteSD(struct repeating_timer *t);

/**
 * DECLARAÇÕES DE VARIÁVEIS

 */
bool setupCompleto;
unsigned long tempoTotal;
unsigned long tempoInicial;
RPI_PICO_Timer Core0Timer0(0);
RPI_PICO_Timer Core1Timer1(1);
Instancia myInstance(false, true);

void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.println("INCIALIZANDO");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    return;
}

void setup1()
{
    return;
}

void loop()
{
    return;
}

void loop1()
{
    return;
}
