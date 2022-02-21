int combYellowPort = 5;
int combGreenPort = 6;

void combSetup()
{
    pinMode(combYellowPort, INPUT);
    pinMode(combGreenPort, INPUT);
}

int getComb()
{
    int yellowState = digitalRead(combYellowPort);
    int greenState = digitalRead(combGreenPort);

    if (greenState && yellowState)
        return 2;
    else if (yellowState)
        return 1;

    return 0;
}