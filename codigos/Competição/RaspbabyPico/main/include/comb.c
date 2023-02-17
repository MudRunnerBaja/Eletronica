/*
    Implementação dos níveis de combustível do carro
    !!   ALIMENTADOS COM 12V, PODEM QUEIMAR PICO   !!
*/

int combSup = 27;
int combInf = 26;
int ledVerde = 19;
int ledAmarelo = 20;
int ledVermelho = 21;
int nivelComb = 0;

enum nivel {
    VAZIO,
    MEDIO,
    CHEIO
};

void combSetup()
{
    pinMode(COMB_SUPERIOR, INPUT);
    pinMode(COMB_INFERIOR, INPUT);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarelo, OUTPUT);
    pinMode(ledVermelho, OUTPUT);

    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, HIGH);
}

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
        setarCombustivel(VAZIO);
        return (int) VAZIO;
    }
    
    if (sensorSup == LOW) // Se o superior detecta combustível
    {                   // E o inferior TAMBÉM (1º if)
        setarCombustivel(CHEIO);
        return (int) CHEIO;
    }

    else // Se o superior não detecta e o inferior detecta
    {
        setarCombustivel(MEDIO);
        return (int) MEDIO;
    }
}

int getNivelComb()
{
    return nivelComb;
}