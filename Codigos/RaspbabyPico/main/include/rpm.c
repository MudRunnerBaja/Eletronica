/* 
    Implementação da contagem de rpm do carro 
*/

int rpmInputPin = 28;
int rpmCounter = 0;
int rpmGlobal;

float setRpm()
{
    rpmGlobal = rpmCounter * 60;
    rpmCounter = 0;
    return rpmGlobal;
}

float getRpm()
{
    return setRpm();
}

void rpmCounterFunc()
{
    rpmCounter++;
}

void rpmSetup()
{
    attachInterrupt(digitalPinToInterrupt(rpmInputPin), rpmCounterFunc, RISING);
}
