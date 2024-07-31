/**
 * Project Classes Placa Central
 *
 * Aquisição do nível do líquido de freio e da pressão de freio
 *
 * Pressão:
 * 0.5V à 4.5V
 * 0 MPa à 60 MPa
 */

#ifndef _FREIO_H
#define _FREIO_H

#include "Setupable.h"
#include "Constantes.h"

class Freio : public Setupable
{
public:
    static Freio *instance;
    static Freio *Setup();

    /**
     * @return bool
     */
    bool Debug()
    {
        return false;
    }

    void setValoresDeTeste()
    {
        pressaoAtual = (((double)random(255) / 146.25) * 2.1428);
        nivelAtual = random(1);
    }

    int setNivelAtual()
    {
        nivelAtual = digitalRead(NIVEL_FREIO);
        return nivelAtual;
    }

    int setPressaoAtual()
    {
        pressaoAtual = calculaPressao();
        return pressaoAtual;
    }

    double calculaPressao()
    {
        // 3.3V = 4095 = 60 MPA
        // < 0.5V? = 0 = 0 MPA
        // +/- 0.1V = 146,25 = 2.1428 MPA

        int leitura = analogRead(PRESSAO_FREIO);

        return (((double)leitura / 146.25) * 2.1428);
    }

    int getNivelAtual()
    {
        return nivelAtual;
    }

    double getPressaoAtual()
    {
        return pressaoAtual;
    }

    Freio(Freio &outro) = delete;

    Freio()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    int nivelAtual;
    double pressaoAtual;
};

Freio *Freio::instance{nullptr};
Freio *Freio::Setup()
{
    if (instance == NULL)
    {
        instance = new Freio();
    }

    pinMode(NIVEL_FREIO, INPUT);
    pinMode(PRESSAO_FREIO, INPUT);

    return instance;
}
#endif //_FREIO_H