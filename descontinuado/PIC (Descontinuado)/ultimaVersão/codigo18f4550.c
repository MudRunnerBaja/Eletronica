#define PRECISAO_DA_FILTRAGEM 10

unsigned int guardaValoresRpm[PRECISAO_DA_FILTRAGEM];
unsigned int guardaValoresVel[PRECISAO_DA_FILTRAGEM];

int ready,count,value;
unsigned long int num=0,nextNum = 0;
unsigned int digit = 0;
int portaRpmRecebeuSinal, portaVelRecebeuSinal,numvel,numrpm;
int i = 0;

void filtrarValores(unsigned int Rpm, unsigned int Vel){

    unsigned long somaValoresRpm = 0, somaValoresVel = 0;

    for(i = PRECISAO_DA_FILTRAGEM - 1; i > 0; i--){
        guardaValoresRpm[i] = guardaValoresRpm[i-1];
        guardaValoresVel[i] = guardaValoresVel[i-1];
    }

    guardaValoresRpm[0] = Rpm;
    guardaValoresVel[0] = Vel;

    for (i = 0; i < PRECISAO_DA_FILTRAGEM; i++){
        somaValoresRpm = somaValoresRpm + guardaValoresRpm[i];
        somaValoresVel = somaValoresVel + guardaValoresVel[i];
    }

    numrpm = somaValoresRpm/PRECISAO_DA_FILTRAGEM;
    numvel = somaValoresVel/PRECISAO_DA_FILTRAGEM;

}

unsigned char segs[10] = {
    0b11000000,//0
    0b11111001,//1
    0b10100100,//2
    0b10110000,//3
    0b10011001,//4
    0b10010010,//5
    0b10000010,//6
    0b11111000,//7
    0b10000000,//8
    0b10010000//9
};

unsigned char digits[4] = {
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000
};

unsigned int mods[4] = {
    1000,
    100,
    10,
    1
};

unsigned int mods2[4] = {
    10000,
    1000,
    100,
    10
};

unsigned int nexts[4] = {
    1,
    2,
    3,
    0
};

void interrupt(){

     if(TMR1IF_bit){



         ready = 1;
         count++;
         TMR1H = 0xE7;  TMR1L = 0x96;
         TMR1IF_bit = 0;

     
     
     }


     
    if (INT0IF_bit){
        portaRpmRecebeuSinal++;     //Variavel que armazena o total de sinais recebidos pelo motor

        INT0IF_bit = 0;
     }

    if (INT1IF_bit) {
        portaVelRecebeuSinal++;     //Variavel que armazena o total de sinais recebidos pelo sensor de vel

        INT1IF_bit = 0;

     }


}


void main() {
     PCFG3_bit = 1; PCFG2_bit = 1; PCFG1_bit = 1; PCFG0_bit = 1;

     GIE_bit = 1;
     PEIE_bit = 1;
     INT0IE_bit = 1;
     INTEDG0_bit = 0;
     INT1IE_bit = 1;
     INTEDG1_bit = 0;
     TMR1IE_bit = 1;
     T1CKPS1_bit = 1;
     T1CKPS0_bit = 1;
     TMR1H = 0xE7;  TMR1L = 0x96;
     TMR1ON_bit = 1;
     
     TRISC0_bit = 0;
     TRISA = 0x00;
     TRISD = 0x00;
     
     while(1){
     
              if(ready){

                       
                       ready = 0;

                       num = nextNum;
                       num = num % (mods2[digit]);
                       LATA = digits[digit];
                       LATD = segs[(num / mods[digit])];
                       digit = nexts[digit];
              
              
              }
              if(count == 25){
              

                       value = ~value;
                       PORTC.F0 = value;
                       count = 0;

                       
                       numvel = portaVelRecebeuSinal*6;
                       numrpm = portaRpmRecebeuSinal*240;
                       
                       filtrarValores(numrpm,numvel);
                       
                       portaVelRecebeuSinal = 0;
                       portaRpmRecebeuSinal = 0;
                       
                       nextNum = (numvel * 100 + (numrpm /100));
                       
                       
              
              
              }
     
     
     
     
     
     }
     

}