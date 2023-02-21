#line 1 "D:\\lucas\\Documents\\GitHub\\Eletronica\\Codigos\\Competição\\RaspbabyPico\\main\\include\\rpm.c"
/* 
    Implementação da contagem de rpm do carro 
*/

int rpmInputPin = 28;
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
    attachInterrupt(digitalPinToInterrupt(rpmInputPin), rpmCounterFunc, RISING);
}
