/**
 * Project Classes Placa Central
 */

#ifndef _CONSTANTES_H
#define _CONSTANTES_H

#define DEBUG 0 // 0 Para não usar serial, 1 para usar serial

#if DEBUG
#define D_SerialBegin(...) Serial.begin(__VA_ARGS__); // Substitui Serial.begin
#define D_print(...) Serial.print(__VA_ARGS__)        // Substitui Serial.print
#define D_write(...) Serial.print(__VA_ARGS__)        // Substitui Serial.write
#define D_println(...) Serial.println(__VA_ARGS__)    // Substitui Serial.println
#else
#define D_SerialBegin(bauds)
#define D_print(...)
#define D_write(...)
#define D_println(...)
#endif

// -- Constantes --

#define INTERVALO_TIMER_MS 1000
#define TEMPERATURA_CRITICA_CVT 200
#define RAIO_PNEU 22
#define QTD_SENSORES_PNEU 4
#define MINUTO_EM_MICROSSEGUNDOS 60000000

static const long MINUTO = 60 * (1000 / INTERVALO_TIMER_MS);
// static const bool DEBUG_MODE = true;

enum Nivel
{
    BAIXO,
    MEDIO,
    ALTO
};

#define SERIAL_BAUD 115200 // SERIAL DEBUG

// TELEMETRIA SERIAL1 UART
#define TELEMETRIA_RX 1 // PINO RX UART LORA
#define TELEMETRIA_TX 0 // PINO TX UART LORA

// TEMP CVT


    // 4 E 5 SÃO DO MLX, REVISAR PINOUT E SETUP


// GPIO Livre
#define GPIO2_P4_LIVRE 2

// I2C
#define I2C_SDA 4
#define I2C_SCL 5

// GPS SERIAL1 UART
#define GPS_TX 8 // PINO TX UART GPS
#define GPS_RX 9 // PINO RX UART GPS
#define GPS_BAUD 9600

// SD SPI1
#define SD_RXPIN 12 // MISO
#define SD_CSPIN 13
#define SD_SCKPIN 10
#define SD_TXPIN 11 // MOSI 

// COMBUSTIVEL
#define COMB_INFERIOR 14
#define COMB_SUPERIOR 15

// CAN SPI1
#define CAN_SCKPIN 18
#define CAN_TXPIN 19 // MOSI/TX CAN
#define CAN_RXPIN 16 // MISO/RX CAN
#define CAN_CSPIN 17
#define CAN_INPIN 3

// FREIO
#define NIVEL_FREIO 20
#define PRESSAO_FREIO 27

// DIVISOR TENSAO
#define DIV_TENSAO 26
#define BATERIA_TENSAO_MAX 13.3

// RPM
#define RPM_INTERRUPT_PIN 21

// VELOCIDADE
#define VEL_INTERRUPT_PIN 22

// PEDAL ACELERADOR
#define PEDAL_ACELERADOR 28

struct _DadosCompartilhamento
{
    short nivelComb;
    int nivelFreio;
    float pressaoFreio;
    float pedal;
    float tensaoBat;
    double tmpCvt;
    double tmpAmb;
    double rpm;
    double vel;
    float latitude;
    float longitude;
};

struct _DadosLight
{
    double rpm;
    double vel;
    double tensaoBat;
};

typedef struct _DadosLight DadosLight;


typedef struct _DadosCompartilhamento DadosCompartilhamento;

#endif //_CONSTANTES_H