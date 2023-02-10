#line 1 "d:\\lucas\\Documents\\GitHub\\Eletronica\\codigos\\Competição\\RaspbabyPico\\main\\include\\rpm.c"
/* 
    Implementação da contagem de rpm do carro 
*/

int rpmInputPin = 8;
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
