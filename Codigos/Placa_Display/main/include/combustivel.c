

int ledVerde = 2, ledAmarelo = 1, ledVermelho = 0;

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

void setupComb(){
    pinMode(ledVermelho,OUTPUT);
    pinMode(ledAmarelo,OUTPUT);
    pinMode(ledVerde,OUTPUT);
    testLed();
}