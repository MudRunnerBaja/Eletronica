#include <CAN.h>


bool CVT = false, gps_conn = false, sd_rw = false, conn = false;
bool can_conn = false, update = false, nivelFreio = false, setLap = false;
short comb = 0;
int vel, velGps, rpm, rpmMovida, volta;
float tensao = 13, pressFreio, posAcelerador;
long told, tlap, tlapOld, tOn;
double TCvt, TProtecao;

char tvel[10]; // String responsável por mostrar o valor da velocidade
char trpm[10]; // String responsável por mostrar o valor do RPM
char mrpm[10];

void randomValues();

void canUpdate(){
    if(millis() >= told + 500){
        randomValues();

        itoa(vel/10, &tvel[0], 10);
        itoa(vel%10, &tvel[1], 10);

        itoa(rpm/1000, &trpm[0], 10);
        itoa((rpm/100)%10, &trpm[1], 10);


        itoa(rpm/1000, &mrpm[0], 10);
        itoa((rpm/100)%10, &mrpm[1], 10);
        itoa((rpm%100)/10, &mrpm[2], 10);
        itoa(rpm%10, &mrpm[3], 10);
        told = millis();
        update = true;
    }
}

void setupComunicacao(){

}

void randomValues(){
    comb = random(3);
    vel = random(99);
    rpm = random(4000);
    CVT = int(random(2));
    gps_conn = int(random(2));
    sd_rw = int(random(2));
    can_conn = int(random(2));
    velGps = random(99);
    tOn = millis()/1000;
    rpmMovida = random(4000);
    pressFreio = random(1600);
    posAcelerador = random(100);
    nivelFreio = int(random(2));
    TCvt = random(120);
    TProtecao = random(120);
    tensao = 12.6;
    volta = random(21);
}
