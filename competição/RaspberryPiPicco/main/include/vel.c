#define WHEEL_RADIUS 26.67
#define SENSOR_QUANTITY 4

int metersPerSignal = (WHEEL_RADIUS * 2 * PI) / (SENSOR_QUANTITY * 100);
int velCounter = 0;
int velRecieverPort = 3;
float velGlobal;

float getVel()
{
    velGlobal = metersPerSignal * velCounter;
    velCounter = 0;
    return velGlobal;
}

float getVelValue()
{
    return velGlobal;
}

void velCounterFunc()
{
    velCounter++;
}

void setupVel()
{
    attachInterrupt(digitalPinToInterrupt(velRecieverPort), velCounterFunc, RISING);
}
