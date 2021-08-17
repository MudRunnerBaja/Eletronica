char txt[768];
char *string;
int i,ready;
int portaRpmRecebeuSinal = 0, portaVelRecebeuSinal = 0;
int count = 0;
char rpm[5];
int value = 0;
unsigned long int nextNum = 0, num = 0;
unsigned int digit = 0;
int numrpm=0, numvel=0;
unsigned int estadoDoCombustivel = 0;

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


void checarCombustivel(void){
          if(PORTB.F2 == 1){
                LATB4_bit = 0;
                LATB5_bit = 0;
                LATB6_bit = 1;
                estadoDoCombustivel = 1;

            }else if(PORTB.F3 == 1){
                LATB4_bit = 0;
                LATB5_bit = 1;
                LATB6_bit = 0;
                estadoDoCombustivel = 2;

            }else{
                LATB4_bit = 1;
                LATB6_bit = 0;
                LATB6_bit = 0;
                estadoDoCombustivel = 3;
            }
}

void TELEMETRIA(int rpm, int vel,int comb){
     char rpmstring[5],velstring[5],combstring[5];

     sprintf(rpmstring, "%d", rpm);
     UART1_Write_Text("rpm:");
     UART1_Write_Text(rpmstring);
     UART1_Write(13);

     sprintf(velstring, "%d", vel);
     UART1_Write_Text("vel:");
     UART1_Write_Text(velstring);
     UART1_Write(13);

     sprintf(combstring, "%d", comb);
     UART1_Write_Text("comb:");
     UART1_Write_Text(combstring);
     UART1_Write(13);



}

void GPS(){

      int j;
      string = strstr(txt,"$GPGGA");       //string de interesse $GPGLL

      if(string != 0) { //If txt array contains "$GPGLL" string we proceed...

          UART_Write_Text("latitude:");
          for(j = 18; j<27; j++)
              UART_Write(string[j]);
          UART_Write(13);

          UART_Write_Text("longitude:");
          for(j = 30; j<40; j++)
              UART_Write(string[j]);
          UART_Write(13);


      }


}

void interrupt(){

     if(TMR1IF_bit){

              ready = 1;
              TMR1H= 0xF3;
              TMR1L= 0xC8;
              TMR1IF_bit = 0;


     }

     if(RCIF_bit){

              txt[i++] = UART1_Read();

              if(i==768) i=0;

              RCIF_bit = 0;

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
           UART1_Init(9600);
           GIE_bit = 1;
           PEIE_bit = 1;
           RCIE_bit = 1;
           INT0IE_bit = 1;
           INTEDG0_bit = 0;
           INT1IE_bit = 1;
           INTEDG1_bit = 0;
           TMR1IE_bit = 1;
           T1CKPS1_bit = 1;
           T1CKPS0_bit = 1;
           
           RD16_bit = 1;
           TMR1H = 0xF3;  TMR1L = 0xC8;
           TMR1ON_bit = 1;


           TRISA   = 0x00;
           TRISB   = 0b00001111;
           TRISD   = 0x00;
           TRISC6_bit = 0;
           TRISC7_bit = 1;
           TRISC0_bit = 0;
           while(1){



               if(ready){
                    count++;
                    ready = 0;
                    num = nextNum;
                    num = num % (mods2[digit]);
                    LATA = digits[digit];
                    LATD = segs[(num / mods[digit])];
                    digit = nexts[digit];

                     if (count == 200){
                          count = 0;
                          value = ~value;
                          LATC0_bit = value;
                          GPS();
                          numrpm = portaRpmRecebeuSinal*60;
                          numvel = portaVelRecebeuSinal*1.5;
                          nextNum = (numvel * 100 + (numrpm /100));
                          TELEMETRIA(numrpm,numvel,estadoDoCombustivel);
                          portaRpmRecebeuSinal = 0; portaVelRecebeuSinal = 0;
                          checarCombustivel();

                     }
               }

           }
}