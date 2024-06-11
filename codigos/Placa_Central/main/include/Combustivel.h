/**
 * Project Classes Placa Central
 *
 * Aquisição do nível de combustível
 *
 */

#ifndef _COMBUSTIVEL_H
#define _COMBUSTIVEL_H

#include "Setupable.h"
#include "Constantes.h"

class Combustivel : public Setupable
{
public:
    static Combustivel *instance;
    static Combustivel *Setup();

    /**
     * Imprime o nível atual de combustível no momento da chamada.
     * Retorna verdadeiro se o valor não for previsto.
     */
    bool Debug()
    {
        bool erro = false;
        if (Serial.available())
        {
            String s;
            if (nivelAtual == ALTO)
                s = "2 - ALTO";
            else if (nivelAtual == MEDIO)
                s = "1 - MEDIO";
            else if (nivelAtual == BAIXO)
                s = "0 - BAIXO";
            else
            {
                s = "VALOR INESPERADO";
                erro = true;
            }

            Serial.println("Nível de combustível: " + s);
        }
        return erro;
    }

    short setNivelAtual()
    {
        /*
            !!  OS SENSORES CAPACITIVOS  !!
            !!    SÃO NORMAL-FECHADOS    !!
            TRUE/HIGH -> Combustível não detectado
            FALSE/LOW -> Combustível detectado
        */
        int sensorSuperior = digitalRead(COMB_SUPERIOR);
        int sensorInfernior = digitalRead(COMB_INFERIOR);

        if (sensorInfernior == HIGH) // Se o inferior não detecta combustível
        {
            nivelAtual = BAIXO;
            return nivelAtual;
        }
        if (sensorSuperior == LOW) // Se o superior detecta combustível
        {                          // E o inferior TAMBÉM (1º if)
            nivelAtual = ALTO;
            return nivelAtual;
        }
        else // Se o superior não detecta e o inferior detecta
        {
            nivelAtual = MEDIO;
            return MEDIO;
        }
        return 0;
    }

    short getNivelAtual()
    {
        return nivelAtual;
    }

    Combustivel(Combustivel &outro) = delete;

    Combustivel()
    {
        if (instance == nullptr)
        {
            instance = this;
        }
    }

private:
    short nivelAtual;
};

Combustivel *Combustivel::instance{nullptr};
Combustivel *Combustivel::Setup()
{
    if (instance == NULL)
    {
        instance = new Combustivel();
    }

    pinMode(COMB_SUPERIOR, INPUT);
    pinMode(COMB_INFERIOR, INPUT);

    return instance;
}

#endif //_COMBUSTIVEL_H