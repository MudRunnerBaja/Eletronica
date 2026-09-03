/**
 * Project Classes Placa Central
 */

#ifndef _PEDAL_ACELERADOR_H
#define _PEDAL_ACELERADOR_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

#if defined(ARDUINO_ARCH_ESP32)
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#define PEDAL_ACELERADOR_HAS_FREERTOS 1
#endif

class PedalAcelerador
{
public:
    static PedalAcelerador *instance;
    static PedalAcelerador *Setup();

    double getPedalAcelerador()
    {
    #if !PEDAL_ACELERADOR_HAS_FREERTOS
        return updatePedalAcelerador();
    #else
        lock();
        const double leitura = pedalAcelerador;
        unlock();
        return leitura;
    #endif
    }

    double updatePedalAcelerador()
    {
        const double leitura = static_cast<double>(analogRead(PEDAL_ACELERADOR)) / 4095.0;
        setPedalAcelerador(leitura);
        return leitura;
    }

    bool Debug()
    {
        return false;
    }

    bool Loop()
    {
        return false;
    }

    PedalAcelerador(PedalAcelerador &outro) = delete;

    PedalAcelerador()
    {
        if (instance == nullptr)
        {
            instance = this;
        }

#if PEDAL_ACELERADOR_HAS_FREERTOS
        mutex = xSemaphoreCreateMutex();
        xTaskCreate(taskAtualizacao, "pedal-acelerador", 2048, this, 1, &task);
#endif
    }

private:
    double pedalAcelerador = 0.0;

#if PEDAL_ACELERADOR_HAS_FREERTOS
    SemaphoreHandle_t mutex;
    TaskHandle_t task;

    static void taskAtualizacao(void *contexto)
    {
        auto *pedal = static_cast<PedalAcelerador *>(contexto);

        for (;;)
        {
            pedal->updatePedalAcelerador();
            vTaskDelay(pdMS_TO_TICKS(INTERVALO_TIMER_MS));
        }
    }

    void lock()
    {
        xSemaphoreTake(mutex, portMAX_DELAY);
    }

    void unlock()
    {
        xSemaphoreGive(mutex);
    }
#else
    void lock() {}
    void unlock() {}
#endif

    void setPedalAcelerador(double valor)
    {
        lock();
        pedalAcelerador = valor;
        unlock();
    }
};

PedalAcelerador *PedalAcelerador::instance{nullptr};
PedalAcelerador *PedalAcelerador::Setup()
{
    if (instance == nullptr)
    {
        instance = new PedalAcelerador();
    }

    pinMode(PEDAL_ACELERADOR, INPUT);
    return instance;
}

#endif //_PEDAL_ACELERADOR_H