/*
 * Project Classes Placa Central
 */

#include <Arduino.h>
#include <RPi_Pico_ISR_Timer.hpp>    // Manipuladores de Interrupção
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h>      // Manipuladores de Interrupção
#include "include/Instancia.h"
#include "main.h"

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
Instancia *myInstance;

void setup()
{
    pinMode(GPIO2_P4_LIVRE, OUTPUT);
    // pinMode(GPIO3_P5_LIVRE, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    digitalWrite(GPIO2_P4_LIVRE, HIGH);
    // digitalWrite(GPIO3_P5_LIVRE, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);

    D_SerialBegin(SERIAL_BAUD);

    // DEBUG é uma constante definida em Constantes.h
    WaitSerial(DEBUG);

    D_println("INCIALIZANDO INSTANCIA");
    D_println("=======================");
    myInstance = Instancia::GetInstance();

    myInstance->InicializarArquivo();

    // randomSeed(756498465497);
    D_println("=======================");
    D_println("INICIALIZACAO CONCLUIDA");

    setupCompleto = true;
    D_println("Setup core0 finalizado.");

    return;
}

void setup1()
{
    while (!setupCompleto)
    {
        delay(1);
    }

    D_println("Setup1 iniciando");
    delay(10);

    if (Core1Timer1.attachInterruptInterval(INTERVALO_TIMER_MS * 200, UpdateData))
        D_println("Core1Timer1 OK. Timer de: " + INTERVALO_TIMER_MS);
    else
        D_println("Falha no Core1Timer1. Sem timer de escrita no SD");

    return;
}

unsigned long tempo = millis();
bool teste = LOW;
void loop()
{
    // myInstance->AtualizarDados();
    // delay(5);
    // myInstance->printarDados();
    // delay(995);
    // if (tempo < millis())
    // {
    //     teste = !teste;
    //     digitalWrite(GPIO2_P4_LIVRE, teste);
    //     tempo = millis() + 20;
    // }
    
}

void loop1()
{
    return;
}

bool UpdateData(struct repeating_timer *t)
{
    myInstance->SetDadosSistemas();
    myInstance->SincronizarDados();
    myInstance->EnviarDadosCanBus();
    myInstance->PrintarDados();
    myInstance->EnviarDadosTelemetria();
    myInstance->EscreverSD();
    // D_println(digitalRead(GPIO3_P5_LIVRE));
    return true;
}
