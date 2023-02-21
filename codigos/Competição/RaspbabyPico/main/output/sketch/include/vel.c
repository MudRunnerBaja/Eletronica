#line 1 "D:\\lucas\\Documents\\GitHub\\Eletronica\\Codigos\\Competição\\RaspbabyPico\\main\\include\\vel.c"
/* 
    Implementação da contagem de rpm do carro
*/

#define WHEEL_RADIUS 26.67
#define SENSOR_QUANTITY 4

float metersPerSignal = (WHEEL_RADIUS * 2 * PI) / (SENSOR_QUANTITY * 100);
int velCounter = 0;
int velInputPin = 22;
float velGlobal;

float setVel()
{
    velGlobal = metersPerSignal * velCounter;
    velCounter = 0;
    // Serial.println(velGlobal);
    return velGlobal;
}

float getVel()
{
    return (velGlobal * (36/10));
}

void velCounterFunc()
{
    velCounter++;
}

void velSetup()
{
    attachInterrupt(digitalPinToInterrupt(velInputPin), velCounterFunc, FALLING);
}