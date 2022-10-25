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

<<<<<<< HEAD:codigos/Competição/RaspbabyPico/main/include/rpm.c
void rpmSetup()
=======
void rpmCounterFunc()
>>>>>>> parent of 156ac38 (Update SDCard):Codigos/RaspbabyPico/main/include/rpm.c
{
    rpmCounter++;
}

void rpmSetup()
{
    attachInterrupt(digitalPinToInterrupt(rpmInputPin), rpmCounterFunc, RISING);
}
