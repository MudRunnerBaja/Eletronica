/**
 * Project Classes Placa Central
 */

#ifndef _TENSAOBATERIA_H
#define _TENSAOBATERIA_H

#include <Arduino.h>
#include "Setupable.h"
#include "Constantes.h"

#if defined(ARDUINO_ARCH_ESP32)
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#define TENSAO_BATERIA_HAS_FREERTOS 1
#endif

class TensaoBateria
{
public:
    static TensaoBateria *instance;
    static TensaoBateria *GetInstance();

    double updateTensaoBateria()
    {
        const double leitura = (static_cast<double>(analogRead(DIV_TENSAO)) / 4095.0) * BATERIA_TENSAO_MAX;
        setTensaoBateria(leitura);
        return leitura;
    }

    bool Debug()
    {
        return false;
    }

    double getTensaoBateria()
    {
#if !TENSAO_BATERIA_HAS_FREERTOS
        return updateTensaoBateria();
#else
        lock();
        const double leitura = tensaoBateria;
        unlock();
        return leitura;
#endif
    }

    TensaoBateria(TensaoBateria &outro) = delete;

    TensaoBateria()
    {
        if (instance == nullptr)
        {
            instance = this;
        }

#if TENSAO_BATERIA_HAS_FREERTOS
        mutex = xSemaphoreCreateMutex();
        xTaskCreate(taskAtualizacao, "tensao-bateria", 2048, this, 1, &task);
#endif
    }

private:
    double tensaoBateria = 0.0;

#if TENSAO_BATERIA_HAS_FREERTOS
    SemaphoreHandle_t mutex;
    TaskHandle_t task;

    static void taskAtualizacao(void *contexto)
    {
        auto *sensor = static_cast<TensaoBateria *>(contexto);

        for (;;)
        {
            sensor->updateTensaoBateria();
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

    void setTensaoBateria(double valor)
    {
        lock();
        tensaoBateria = valor;
        unlock();
    }
};

TensaoBateria *TensaoBateria::instance{nullptr};
TensaoBateria *TensaoBateria::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new TensaoBateria();
    }

    pinMode(DIV_TENSAO, INPUT);
    return instance;
}

#endif //_TENSAOBATERIA_H