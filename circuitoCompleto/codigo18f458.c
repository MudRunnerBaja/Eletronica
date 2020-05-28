//Habilitar as seguintes bibliotecas:
// - Lcd
// - SPI
// - Conversions e C_String

#include <built_in.h>

sbit LCD_RS at RB5_bit;
sbit LCD_EN at RB4_bit;
sbit LCD_D4 at RB3_bit;
sbit LCD_D5 at RB2_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB5_bit;
sbit LCD_EN_Direction at TRISB4_bit;
sbit LCD_D4_Direction at TRISB3_bit;
sbit LCD_D5_Direction at TRISB2_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

//Copie e cole o código da bilioteca aqui!!!

sbit MAX6675_CS at RC0_Bit;
sbit MAX6675_CS_Direction at TRISC0_Bit;

char txt[768];
char *string;
int i,ready,numrpm,numvel,estadoDoCombustivel,portaRpmRecebeuSinal,portaVelRecebeuSinal,count,value;

union
{
  char state:1;
  char deviceID:1;
  char open:1;
  char temperature:12;
  char sign:1;
  unsigned output;
}Max6675Data;

void MAX6675_Init()
{
  MAX6675_CS_Direction = 0;
  MAX6675_CS = 1;
}

unsigned Max6675_Read()
{
unsigned tmp;
  MAX6675_CS = 0;
  Hi(tmp) = SPI1_Read(0);
  Lo(tmp) = SPI1_Read(0);
  MAX6675_CS = 1;
  return(tmp);
}

void checarCombustivel(void){
          if(PORTA.F1 == 1){
                LATD4_bit = 0;
                LATD5_bit = 0;
                LATD6_bit = 1;
                estadoDoCombustivel = 1;

            }else if(PORTA.F4 == 1){
                LATD4_bit = 0;
                LATD5_bit = 1;
                LATD6_bit = 0;
                estadoDoCombustivel = 2;

            }else{
                LATD4_bit = 1;
                LATD5_bit = 0;
                LATD6_bit = 0;
                estadoDoCombustivel = 3;
            }
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

void interrupt(){

     if(TMR1IF_bit){

              ready = 1;
              TMR1H= 0x0B;
              TMR1L= 0xDC;
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


void main()
{
char texto[8];
int temperatura;

   PCFG3_bit = 1; PCFG2_bit = 1; PCFG1_bit = 1; PCFG0_bit = 1;
   CMCON   = 0x0F;
   UART1_Init(9600);
   SPI1_Init();
   MAX6675_Init();
   Lcd_Init();
   Lcd_Cmd( _LCD_CURSOR_OFF );
   Lcd_Cmd( _LCD_CLEAR );
   Lcd_Out( 1, 6, "MAX6675" );
   
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
   TMR1H = 0x0B;  TMR1L = 0xDC;
   TMR1ON_bit = 1;
   TRISC6_bit = 0;
   TRISC7_bit = 1;
   TRISC1_bit = 0;
   TRISA = 0b00010010;
   TRISD = 0;



   while(1)
   {
           if(ready){
               count++;
               ready = 0;
               if(count == 10){
               
                        *(unsigned*)&Max6675Data = MAX6675_Read();
                        count = 0;
                        value = ~value;
                        LATC1_bit = value;
                        WordToStr( Max6675Data.temperature >> 1, texto );
                        temperatura = atoi(texto);
                        GPS();
                        Lcd_Out( 2, 1, "Temp: " );
                        Lcd_Out_CP( texto+2 );
                        Lcd_Chr_CP( 223 );
                        Lcd_Chr_CP( 'C' );
                        numrpm = portaRpmRecebeuSinal*60;
                        numvel = portaVelRecebeuSinal*1.5;
                        TELEMETRIA(numrpm,numvel,estadoDoCombustivel);
                        UART1_Write_Text("temperatura:");
                        UART1_Write_Text(texto);
                        UART1_Write(13);
                        portaRpmRecebeuSinal = 0; portaVelRecebeuSinal = 0;
                        checarCombustivel();
                        if(temperatura >= 120){
                             LATD.F0 = 1;
                        }
                        else{
                             LATD.F0 = 0;
                        }
               }
           
           }



   }

}