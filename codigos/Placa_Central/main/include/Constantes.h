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

    const long MINUTO = 60 * (1000 / INTERVALO_TIMER_MS);

    #pragma region SLAVES_COMUNICACAO

    #pragma endregion

    #pragma region PINOS

    // SERIAL1
    #define TELEMETRIA_RX 1
    #define TELEMETRIA_TX 0

    // SPI1
    #define SD_SCKPIN 10
    #define SD_TXPIN 11 // MOSI
    #define SD_RXPIN 12 // MISO
    #define SD_CSPIN 13



    #pragma endregion
};

#endif //_CONSTANTES_H