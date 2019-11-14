

#define _XTAL_FREQ 20000000

#include <xc.h>
#include "setup.h"

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
    0b00000100, 
    0b01000000,
    0b10000000 
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

unsigned int digit = 0;
unsigned long  int p_rpm = 0, num = 0, p_vel = 0, V = 0, i = 0, nextNum = 0;
unsigned int timer = 0, timer2 = 0;

void main (void)
{
     
    RCON = 0X80; // Limpa o Registro de Reset
    CMCON   = 0x0F; // Desabilita o Comparador
    //ADCON1 = 0x0F; // Configura todas a portas como Portas Analogicas exeto A0
    T0CON   = 0b11010000; // Habilita Timer , 8 bits,clock interno, preescale 1:64
   // T1CON   = 0b0
    RCONbits.IPEN = 1;
    INTCON  = 0b10110000;
    INTCON2 = 0b11110101;
    INTCON3 = 0b00001000;
    
    TRISA = 0;
    TRISB = 0b00001111; // Coloca todos como tudo Saida
    TRISC = 0;
    TRISD = 0;
    
    LATA = 0;
    LATB = 0;
    LATC = 0;
    LATD = 0;
    LATE = 0;
    
    unsigned char lastState = 0;
    
    while (1){
     if(PORTBbits.RB2 == 1){
                LATBbits.LB4 = 0;
                LATBbits.LB5 = 0;
                LATBbits.LB6 = 1;
            }else if(PORTBbits.RB3 == 1){
                LATBbits.LB4 = 0;
                LATBbits.LB5 = 1;
                LATBbits.LB6 = 0;
            }else{
                LATBbits.LB4 = 1;
                LATBbits.LB5 = 0;
                LATBbits.LB6 = 0;
            }
     __delay_ms(2000);
    }
   
}


void interrupt MyInterrupt(){
    
    if(INTCONbits.T0IF){
        
        if(!(timer % 30)){
            
            LATC = 255;
            LATD = 255;
            num = nextNum;
            num = num % (mods2[digit]);
            LATC = digits[digit];
            LATD = segs[(num / mods[digit])];
            digit = nexts[digit];   
        }
    
        if(timer == 5000){
            p_rpm = i * 60;
            p_vel = V * 3,3282;
            nextNum = (p_vel * 100 + (p_rpm /100)); // Carro 38 MR 17
            //nextNum = p_rpm ; // Carro 56 MR 19
            i = 0;
            V = 0;
            timer = 0;
        }
        TMR0 = 6;                    
        INTCONbits.T0IF = 0;
        timer++;
    }
    
    if(INTCONbits.INT0IF){
       i++;
       INTCONbits.INT0IF=0;    
    } 
    if(INTCON3bits.INT1IF){
        V++;
        INTCON3bits.INT1IF=0;    
    }
    
}



