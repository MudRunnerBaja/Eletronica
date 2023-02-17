/*
    Implementação dos níveis de combustível do carro
    !!   ALIMENTADOS COM 12V, PODEM QUEIMAR PICO   !!
*/
#ifndef NIVEL_COMBUSTIVEL
#define NIVEL_COMBUSTIVEL

#define COMB_SUPERIOR 27 // PINO COMBUSTIVEL SUPERIOR
#define COMB_INFERIOR 26 // PINO COMBUSTIVEL INFERIOR

int nivelComb = 0;
enum nivel { VAZIO, MEDIO, CHEIO };

void combSetup()
{
    pinMode(COMB_SUPERIOR, INPUT);
    pinMode(COMB_INFERIOR, INPUT);
}

int setComb()
{
    /* 
        !!  OS SENSORES CAPACITIVOS  !!
        !!    SÃO NORMAL-FECHADOS    !!
        TRUE/HIGH -> Combustível não detectado
        FALSE/LOW -> Combustível detectado
    */

    int sensorSup = digitalRead(COMB_SUPERIOR);
    int sensorInf = digitalRead(COMB_INFERIOR);

    if (sensorInf == HIGH) // Se o inferior não detecta combustível
    {               
        // setarCombustivel(VAZIO);
        nivelComb = (int) VAZIO;
        return (int) VAZIO;
    }
    
    if (sensorSup == LOW) // Se o superior detecta combustível
    {                   // E o inferior TAMBÉM (1º if)
        // setarCombustivel(CHEIO);
        nivelComb = (int) CHEIO;
        return (int) CHEIO;
    }

    else // Se o superior não detecta e o inferior detecta
    {
        // setarCombustivel(MEDIO);
        nivelComb = (int) MEDIO;
        return (int) MEDIO;
    }
}

int getNivelComb()
{
    return nivelComb;
}

/*  DESATUALIZADO

void setarCombustivel(int nivel)
{
    nivelComb = nivel;
    if (nivel == CHEIO)
    {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledAmarelo, LOW);
        digitalWrite(ledVermelho, LOW);
    }
    else if (nivel == MEDIO)
    {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarelo, HIGH);
        digitalWrite(ledVermelho, LOW);
    }
    else // VAZIO
    {
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledAmarelo, LOW);
        digitalWrite(ledVermelho, HIGH);
    }
}
*/

#endif