//Habilitar as seguintes bibliotecas:
// - Lcd  e Lcd_Constants
// - SPI
// - Conversions e C_String
// - Uart
// - C_Stdlib

#include <built_in.h>
#define tempmax 120

sbit LCD_RS at RB5_bit;
sbit LCD_EN at RB4_bit;
sbit LCD_D4 at RB3_bit;
sbit LCD_D5 at RB2_bit;
sbit LCD_D6 at RB1_bit;
sbit LCD_D7 at RB0_bit;

sbit LCD_RS_Direction at TRISB5_bit;
sbit LCD_EN_Direction at TRISB4_bit;
sbit LCD_D4_Direction at TRISB3_bit;
sbit LCD_D5_Direction at TRISB2_bit;
sbit LCD_D6_Direction at TRISB1_bit;
sbit LCD_D7_Direction at TRISB0_bit;

//Copie e cole o código da bilioteca aqui!!!

sbit MAX6675_CS at RC0_Bit;
sbit MAX6675_CS_Direction at TRISC0_Bit;

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


void main()
{
char texto[8];
int temperatura;
   PCFG3_bit = 1; PCFG2_bit = 1; PCFG1_bit = 1; PCFG0_bit = 1;
   UART1_Init(9600);
   SPI1_Init();
   MAX6675_Init();
   Lcd_Init();
   Lcd_Cmd( _LCD_CURSOR_OFF );
   Lcd_Cmd( _LCD_CLEAR );
   Lcd_Out( 1, 6, "MAX6675" );
   TRISD = 0;

   while(1)
   {
      *(unsigned*)&Max6675Data = MAX6675_Read();

      WordToStr( Max6675Data.temperature >> 1, texto );
      Lcd_Out( 2, 1, "Temp: " );
      Lcd_Out_CP( texto+2 );
      Lcd_Chr_CP( 223 );
      Lcd_Chr_CP( 'C' );
      UART1_Write_Text("temperatura:");
      UART1_Write_Text(texto);
      UART1_Write(13);
      
      temperatura = atoi(texto);

      if (temperatura >= tempmax){
      LATD.F0 = 1;
      }
      else{
      LATD.F0 = 0;
      }
      Delay_ms( 1000 );
   }

}