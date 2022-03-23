#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DP 9

byte cont = 0;
int displays[] = {10, 11, 12, 13};
int contadorDisplay = 0;

const byte tabela_7seg[10][7] =
    {
        // A B C D E F G
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9

};

void escolherDisplay(int num)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (i == num)
            digitalWrite(displays[i], LOW);
        else
            digitalWrite(displays[i], HIGH);
    }
}

void converteValorDisplay(byte valor)
{
    valor = min(valor, 9);
    byte pino = 2;

    for (byte x = 0; x < 7; x++)
    {
        digitalWrite(pino, tabela_7seg[valor][x]);
        pino++;
    }
}

void setupDisplay()
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        digitalWrite(displays[i], HIGH);
        pinMode(displays[i], OUTPUT);
    }
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(DP, OUTPUT);
}

void mostrarDados()
{
    // Velocidade
    float vel = getVelValue();

    escolherDisplay(contadorDisplay);
    int decimal = vel / 10;
    converteValorDisplay(decimal);
    contadorDisplay++;

    escolherDisplay(contadorDisplay);
    int unitario = int(vel) % 10;
    converteValorDisplay(unitario);
    contadorDisplay++;

    // RPM
    int rpm = getRpmValue();

    escolherDisplay(contadorDisplay);
    int milhar = rpm / 1000;
    converteValorDisplay(milhar);
    contadorDisplay++;

    escolherDisplay(contadorDisplay);
    int centesimo = (rpm % 1000) / 100;
    converteValorDisplay(centesimo);
    contadorDisplay = 0;
}
