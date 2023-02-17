#ifndef MAIN_BOARD_DECLARATIONS
#define MAIN_BOARD_DECLARATIONS

    // BIBLIOTECAS
#pragma region BIBLIOTECAS
#include <RPi_Pico_TimerInterrupt.h> // Interrupção com Timer
#include <RPi_Pico_ISR_Timer.h> // Manipuladores de Interrupção
#include <RPi_Pico_ISR_Timer.hpp> // Manipuladores de Interrupção
#include <Arduino.h>
#include <max6675.h>    // Modulo Termopar
#include <TinyGPS.h> // Documentação: http://arduiniana.org/libraries/tinygps/
#include <SPI.h>    // SPI para cartão SD
#include <SD.h>     // SD Filesystem
#include <Wire.h>   // Comunicação I2C
#pragma endregion

    // CONSTANTES
#pragma region CONSTANTES

#define TIMER_INTERVAL_MS 200
#define TEMPERATURA_CRITICA_CVT 80
#define CAR_NAME "MV-22"
const long MINUTO = 60 * (1000 / TIMER_INTERVAL_MS); // Valor referente a um minuto em função do intervalo de atualização
const long GPSBaud = 9600;

#pragma endregion

    // VARIÁVEIS GLOBAIS
#pragma region VARIAVEIS GLOBAIS

bool setupCompleto = false; // Flag Setup core 0
unsigned long tempoTotal = 0, tempoInicial = 0;

        // RPM DO MOTOR
int rpmCounter = 0; int rpmGlobal;

        // GPS

int year = 0, speedInt = 0;
float flat = 0, flon = 0, speed = 0, altitude = 0;
unsigned long age, date, gpstime, milisec;
short dia = 0, mes = 0, ano = 0;
String datahj;
bool newData = false;

        // CVT TUNING
int rpmMovida; int pulsos = 0;
unsigned int pulsos_por_volta_mvd = 1; // Quantidade de imas na polia

        // CARTAO SD
String arq = "dados000.csv";
String checkCard = "check.txt";
byte tipoFalha = 0;
File arquivoDados;

bool erro = false;
unsigned long tempo = 0, tempobase = 0;
unsigned long t2, t1;

        // I2C  
byte data[5];  // I2C data transfer
                // (0-1 vel) (2-3 rpm) (4 Comb + tempCvt)

#pragma endregion

    // PINAGEM
#pragma region PINAGEM

        // RPM DO MOTOR
#define RPM_INPUT_PIN 28 // PINO DE SINAL DO RPM

        // GPS
#define GPS_TX 0 // PINO TX UART GPS
#define GPS_RX 1 // PINO RX UART GPS

        // CVT TUNING
#define HALL_MOVIDA 22 // PINO SENSOR HALL MOVIDA (TORQUE)

        // CARTAO SD
#define SCKPIN 10
#define TXPIN 11 // MOSI
#define RXPIN 12 // MISO
#define CSPIN 13

        // I2C
#define SLAVE_LCD 9
#define SDApin 16
#define SCLpin 17; // Pico I2C0

#pragma endregion


    // OBJETOS/CONSTRUTORES
#pragma region OBJETOS
TinyGPS gps;

#pragma endregion

    // OUTROS ARQUIVOS
#pragma region OUTROS_ARQUIVOS
#include "include/temp.c" // Temperatura CVT
#include "include/comb.c" // Níveis de combustível
#include "include/rpm.c" // RPM do carro
#include "include/gps.c" // GPS 
#include "include/cvt_tunning.c" // CVT Tuning
#include "include/sdcard.c" // Modulo SD
#include "include/comunication.c" // Comunicação entre bibliotecas e serial
#pragma endregion

    // FUNÇÕES
#pragma region FUNCOES
void WaitSerial(bool wait);
bool UpdateTimer(struct repeating_timer *t);
bool WriteSD(struct repeating_timer *t);
#pragma endregion

    // TIMERS
#pragma region TIMERS
RPI_PICO_Timer Core0Timer0(0);
RPI_PICO_Timer Core1Timer1(1);
#pragma endregion


#endif