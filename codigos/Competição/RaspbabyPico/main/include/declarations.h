#ifndef MAIN_BOARD_DECLARATIONS
#define MAIN_BOARD_DECLARATIONS

    // BIBLIOTECAS
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h> // Manipuladores de Interrupção
#include <RPi_Pico_ISR_Timer.hpp> // Manipuladores de Interrupção
#include <Arduino.h>
#include <max6675.h>    // Modulo Termopar
#include <TinyGPS.h> // Documentação: http://arduiniana.org/libraries/tinygps/
#include <SPI.h>    // SPI para cartão SD
#include <SD.h>     // SD Filesystem
#include <Wire.h>   // Comunicação I2C

    // CONSTANTES
#define TIMER_INTERVAL_MS 200
#define TEMPERATURA_CRITICA_CVT 80
#define CAR_NAME "MV-22"
const long MINUTO = 60 * (1000 / TIMER_INTERVAL_MS); // Valor referente a um minuto em função do intervalo de atualização

    // VARIÁVEIS GLOBAIS
bool setupCompleto = false; // Flag Setup core 0
unsigned long tempoTotal = 0, tempoInicial = 0;

    // OUTROS ARQUIVOS
#include <temperatura_cvt.h> // Temperatura CVT
#include <nivel_combustivel.h> // Níveis de combustível
#include <rpm_motor.h> // RPM do carro
#include <gps.h> // GPS 
#include <cvt_tunning.h> // CVT Tuning
#include <sdcard.h> // Modulo SD
#include <communication.h> // Comunicação entre bibliotecas e serial

    // FUNÇÕES
void WaitSerial(bool wait);
bool UpdateTimer(struct repeating_timer *t);
bool WriteSD(struct repeating_timer *t);

    // TIMERS
RPI_PICO_Timer Core0Timer0(0);
RPI_PICO_Timer Core1Timer1(1);

#endif