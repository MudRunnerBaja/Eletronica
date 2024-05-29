int ledVerde = 2, ledAmarelo = 1, ledVermelho = 0;
int brilho = 30;
bool reserva = false;


enum nivel {
    VAZIO,
    MEDIO,
    CHEIO
};


void testLed(){
    for (size_t i = 0; i < 255; i++)
    {
        analogWrite(ledVermelho, i);
        delay(1);
    }
    for (size_t i = 0; i < 255; i++)
    {
        analogWrite(ledAmarelo , i);
        delay(1);
    }
    for (size_t i = 0; i < 255; i++)
    {
        analogWrite(ledVerde , i);
        delay(1);
    }
    for (size_t i = 255; i > 0; i--)
    {
        analogWrite(ledVerde, i);
        delay(1);
    }
    for (size_t i = 255; i > 0; i--)
    {
        analogWrite(ledAmarelo , i);
        delay(1);
    }
    for (size_t i = 255; i > 0; i--)
    {
        analogWrite(ledVermelho , i);
        delay(1);
    }
}

void setCombustivel(int nivel){
    if (nivel == CHEIO)
    {
        analogWrite(ledVerde, brilho);
        analogWrite(ledAmarelo, 0);
        analogWrite(ledVermelho, 0);
        reserva = false;
    }
    else if (nivel == MEDIO)
    {
        analogWrite(ledVerde, 0);
        analogWrite(ledAmarelo, brilho);
        analogWrite(ledVermelho, 0);
        reserva = false;
    }
    else // VAZIO
    {
        analogWrite(ledVerde, 0);
        analogWrite(ledAmarelo, 0);
        analogWrite(ledVermelho, brilho);
        reserva = true;
    }
}

int checkReserva(){
    return reserva;
}

void setupComb(){
    pinMode(ledVermelho,OUTPUT);
    pinMode(ledAmarelo,OUTPUT);
    pinMode(ledVerde,OUTPUT);
    testLed();
}