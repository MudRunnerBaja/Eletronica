/**
 * Project Classes Placa Central
 */

#include <Arduino.h>
#include <RPi_Pico_ISR_Timer.hpp>    // Manipuladores de Interrupção
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h>      // Manipuladores de Interrupção
#include "include/Instancia.h"
void WaitSerial(bool wait); // Esperar pelo serial ou não (testar setup)

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
static bool debugMode = true;
static bool callSetup = true;
static Instancia *myInstance;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.begin(SERIAL_BAUD);

    WaitSerial(debugMode);
    Serial.println("INCIALIZANDO INSTANCIA");
    Serial.println("=======================");
    myInstance = new Instancia(debugMode, callSetup);

    pinMode(LED_BUILTIN, OUTPUT);
    randomSeed(756498465497);
    Serial.println("=======================");
    Serial.println("INICIALIZACAO CONCLUIDA");
    return;
}

void setup1()
{
    return;
}

void loop()
{
    myInstance->AtualizarDados();
    delay(5);
    myInstance->printarDados();
    delay(995);
}

void loop1()
{
    return;
}

void WaitSerial(bool wait) // Esperar pelo serial ou não (testar setup)
{
    if (wait) // Se esperar == true
    {
        while (!Serial)
        { // Esperar o serial (abrir comunicação com o pc)
            yield();
        }
        delay(50);

        Serial.println(F("Type any character to start")); // Após inicializada a comunicação, aguardar um input do serial
        while (!Serial.available())
        { // Enquanto não houver input, esperar
            yield();
        }
    }
    return;
}