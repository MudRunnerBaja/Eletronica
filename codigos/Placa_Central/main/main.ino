/**
 * Project Classes Placa Central
 */

// #include "main.h"
#include <Instancia.h>

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
RPI_PICO_Timer Core0Timer0;
RPI_PICO_Timer Core1Timer1;
Instancia instancia;

/**
 * IMPLEMENTAÇÃO
 */

bool UpdateData(struct repeating_timer *t)
{
    return false;
}

bool WriteSD(struct repeating_timer *t)
{
    return false;
}

void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.println("INCIALIZANDO");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    instancia = new Instancia(false, true);

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
