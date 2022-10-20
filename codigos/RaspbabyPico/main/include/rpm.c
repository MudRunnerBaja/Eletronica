// Modificado
int rpmRecieverPort = 22;
int rpmCounter = 0;
int rpmGlobal;

void rpmCounterFunc()
{
    rpmCounter++;
}

float getRpm()
{
    rpmGlobal = rpmCounter * 60;
    rpmCounter = 0;
    return rpmGlobal;
}

float getRpmValue()
{
    return rpmGlobal;
}

void setupRpm()
{
    attachInterrupt(digitalPinToInterrupt(rpmRecieverPort), rpmCounterFunc, RISING);
}
