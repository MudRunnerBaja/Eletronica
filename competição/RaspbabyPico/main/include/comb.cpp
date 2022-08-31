/*
    Implementação dos níveis de combustível do carro
    !!   ALIMENTADOS COM 12V, PODEM QUEIMAR PICO   !!
*/

int combSup = 32;
int combInf = 31;
int ledVerde = 25;
int ledAmarelo = 26;
int ledVermelho = 27;

enum nivel {
    VAZIO,
    MEDIO,
    CHEIO
};

void combSetup()
{
    pinMode(combSup, INPUT);
    pinMode(combInf, INPUT);

    pinMode(ledVerde, OUTPUT);
    pinMode(ledAmarelo, OUTPUT);
    pinMode(ledVermelho, OUTPUT);
}

void setarCombustivel(int nivel)
{
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

    int sensorSup = digitalRead(combSup);
    int sensorInf = digitalRead(combInf);

    if (sensorInf) // Se o inferior não detecta combustível
    {               
        setarCombustivel(VAZIO);
        return VAZIO;
    }
    
    if (!sensorSup) // Se o superior detecta combustível
    {                   // E o inferior TAMBÉM (1º if)
        setarCombustivel(CHEIO);
        return CHEIO;
    }

    else // Se o superior não detecta e o inferior detecta
    {
        setarCombustivel(MEDIO);
        return MEDIO;
    }
}