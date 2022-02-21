int rpmRecieverPort = 4;
int rpmCounter = 0;

void rpmCounterFunc()
{
    rpmCounter++;
}

float getRpm()
{
    int rpm = rpmCounter * 60;
    rpmCounter = 0;
    return rpm;
}

void setupRpm()
{
    attachInterrupt(digitalPinToInterrupt(rpmRecieverPort), rpmCounterFunc, RISING);
}
