#define A 5
#define B 6
#define C 7
#define D 10
#define E 11
#define F_DISPLAY 12
#define G 13

byte cont = 0;
int displays[] = {14, 15, 16, 17};

const byte tabela_7seg[10][7] =
    {
        // A B C D E F G
        {0, 0, 0, 0, 0, 0, 1}, // 0
        {1, 0, 0, 1, 1, 1, 1}, // 1
        {0, 0, 1, 0, 0, 1, 0}, // 2
        {0, 0, 0, 0, 1, 1, 0}, // 3
        {1, 0, 0, 1, 1, 0, 0}, // 4
        {0, 1, 0, 0, 1, 0, 0}, // 5
        {0, 1, 0, 0, 0, 0, 0}, // 6
        {0, 0, 0, 1, 1, 1, 1}, // 7
        {0, 0, 0, 0, 0, 0, 0}, // 8
        {0, 0, 0, 0, 1, 0, 0}  // 9
};

void escolherDisplay(int contador)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (i == contador)
            digitalWrite(displays[contador], HIGH);
        else
            digitalWrite(displays[i], LOW);
    }
}

void converteValorDisplay(int valor)
{
    int pino = 5;
    valor = valor > 9 ? 9 : valor;

    for (int x = 0; x < 7; x++)
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
        digitalWrite(displays[i], LOW);
        pinMode(displays[i], OUTPUT);
    }
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F_DISPLAY, OUTPUT);
    pinMode(G, OUTPUT);
}

void mostraDados()
{
    int contaDisplay = 0;
    float vel = getVelValue();
    int rpm = getRpmValue();

    // RPM
    int milhar = rpm / 1000;
    escolherDisplay(contaDisplay);
    converteValorDisplay(milhar);
    contaDisplay++;
    delay(1);

    int centesimo = (rpm % 1000) / 100;
    escolherDisplay(contaDisplay);
    converteValorDisplay(centesimo);
    contaDisplay++;
    delay(1);

    // Velocidade
    int decimal = vel / 10;
    escolherDisplay(contaDisplay);
    converteValorDisplay(vel);
    contaDisplay++;
    delay(1);

    int unitario = int(vel) % 10;
    escolherDisplay(contaDisplay);
    converteValorDisplay(unitario);
    contaDisplay++;
    delay(1);
}
