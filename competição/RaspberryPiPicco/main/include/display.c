#define A 5
#define B 6
#define C 7
#define D 10
#define E 11
#define F 12
#define G 13

byte cont = 0;
int displays[] = {14, 15, 16, 17};
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

void escolherDisplay(int contador)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        digitalWrite(displays[i], HIGH);
    }
    digitalWrite(displays[contador], LOW);
}

void converteValorDisplay(byte valor)
{
    byte pino = 5;

    for (byte x = 0; x < 6; x++)
    {
        digitalWrite(pino, tabela_7seg[valor][x]);
        if (pino == 7)
            pino = 10;
        else
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
}

void mostraDados()
{
    float vel = getVel();
    int rpm = getRpm();

    escolherDisplay(contadorDisplay);
    // Milhar RPM
    int milhar = rpm / 1000;
    converteValorDisplay(milhar);
    contadorDisplay++;

    escolherDisplay(contadorDisplay);
    // Centesimo RPM
    int centesimo = (rpm % 1000) / 100;
    converteValorDisplay(centesimo);

    escolherDisplay(contadorDisplay);
    // Decimal velocidade
    int decimal = vel / 10;
    converteValorDisplay(decimal);
    contadorDisplay++;

    escolherDisplay(contadorDisplay);
    // Unitário velocidade
    int unitario = int(vel) % 10;
    converteValorDisplay(unitario);
    contadorDisplay++;

    contadorDisplay = 0;
}
