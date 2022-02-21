#define WHEEL_RADIUS 26.67
#define SENSOR_QUANTITY 4

int metersPerSignal = (WHEEL_RADIUS * 2 * PI) / (SENSOR_QUANTITY * 100);
int velCounter = 0;
int velRecieverPort = 3;

float getVel()
{
    float vel = metersPerSignal * velCounter;
    velCounter = 0;
    return vel;
}

void velCounterFunc()
{
    velCounter++;
}

void setupVel()
{
    attachInterrupt(digitalPinToInterrupt(velRecieverPort), velCounterFunc, RISING);
}
