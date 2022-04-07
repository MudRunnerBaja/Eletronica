int combYellowPort = 26;
int combGreenPort = 27;
int ledGreen = 19;
int ledYellow = 20;
int ledRed = 21;

void combSetup()
{
    pinMode(combYellowPort, INPUT);
    pinMode(combGreenPort, INPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    digitalWrite(ledRed, HIGH);
    pinMode(ledRed, OUTPUT);
}

void setarCombustivel(int nivel)
{
    if (nivel == 2)
    {
        digitalWrite(ledGreen, HIGH);
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledRed, LOW);
    }
    else if (nivel == 1)
    {
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledYellow, HIGH);
        digitalWrite(ledRed, LOW);
    }
    else
    {
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledYellow, LOW);
        digitalWrite(ledRed, HIGH);
    }
}

int getComb()
{
    int yellowState = digitalRead(combYellowPort);
    int greenState = digitalRead(combGreenPort);

    if (greenState && yellowState)
    {
        setarCombustivel(2);
        return 2;
    }

    else if (yellowState)
    {
        setarCombustivel(1);
        return 1;
    }

    setarCombustivel(0);
    return 0;
}
