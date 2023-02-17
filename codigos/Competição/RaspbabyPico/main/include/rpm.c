/* 
    Implementação da contagem de rpm do carro 
*/

int rpmCounter = 0;
int rpmGlobal;
long minuto = 60 * (1000 / TIMER_INTERVAL_MS);

float setRpm()
{
    rpmGlobal = rpmCounter * minuto;
    rpmCounter = 0;
    return rpmGlobal;
}

float getRpm()
{
    return rpmGlobal;
}

void rpmCounterFunc()
{
    rpmCounter++;
}

void rpmSetup()
{
    attachInterrupt(digitalPinToInterrupt(RPM_INPUT_PIN), rpmCounterFunc, RISING);
}
