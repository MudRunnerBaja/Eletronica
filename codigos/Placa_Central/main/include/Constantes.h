/**
 * Project Classes Placa Central
 */


#ifndef _CONSTANTES_H
#define _CONSTANTES_H




class Constantes {
public: 
    #define INTERVALO_TIMER_MS 200
    #define TEMPERATURA_CRITICA_CVT 200
    #define RAIO_PNEU 22
    #define QTD_SENSORES_PNEU 4

    static const long MINUTO = 60 * (1000 / INTERVALO_TIMER_MS);
    static const bool DEBUG_MODE = true;

    enum Nivel {
        BAIXO,
        MEDIO,
        ALTO
    };

    #pragma region SLAVES_COMUNICACAO

    #pragma endregion

    #pragma region PINOS

    // SERIAL DEBUG
    #define SERIAL_BAUD 115200

    // TELEMETRIA SERIAL1 UART
    #define TELEMETRIA_RX 1
    #define TELEMETRIA_TX 0

    // GPS SERIAL1 UART
    #define GPS_TX 8 // PINO TX UART GPS
    #define GPS_RX 9 // PINO RX UART GPS
    #define GPS_BAUD 9600

    // CAN SPI
    #define CAN_SCKPIN 10
    #define CAN_TXPIN 11 // MOSI
    #define CAN_RXPIN 12 // MISO
    #define CAN_CSPIN 13

    // SD SPI1
    #define SD_SCKPIN 10
    #define SD_TXPIN 11 // MOSI
    #define SD_RXPIN 12 // MISO
    #define SD_CSPIN 13

    // FREIO
    #define NIVEL_FREIO 22

    // DIVISOR TENSAO
    #define DIV_TENSAO 26
    #define BATERIA_TENSAO_MAX 13.3

    #pragma endregion
};

#endif //_CONSTANTES_H