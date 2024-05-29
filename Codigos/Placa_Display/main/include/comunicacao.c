#include <CAN.h>


bool CVT = false, gps_conn = false, sd_rw = false, conn = false;
bool can_conn = false, update = false;
short comb = 0;
int vel = 00, rpm = 0000;
float tensao = 13;
long told;

char tvel[10]; // String responsável por mostrar o valor da velocidade
char trpm[10]; // String responsável por mostrar o valor do RPM

void canUpdate(){
    if(millis() >= told + 2000){
        comb = random(3);
        vel = random(99);
        rpm = random(4000);
        CVT = int(random(2));
        gps_conn = int(random(2));
        sd_rw = int(random(2));
        can_conn = int(random(2));

        itoa(vel/10, &tvel[0], 10);
        itoa(vel%10, &tvel[1], 10);
        itoa(rpm/1000, &trpm[0], 10);
        itoa((rpm/100)%10, &trpm[1], 10);
        //itoa((rpm%100)/10, &trpm[2], 10);
        //itoa(rpm%10, &trpm[3], 10);
        told = millis();
        update = true;
    }
}

void setupComunicacao(){

}
