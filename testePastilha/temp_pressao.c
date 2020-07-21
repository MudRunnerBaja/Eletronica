  /* Programação PIC18F4685 - TESTE Mack1 I2C
  Programção para leitura sensor Temperatura CVT

  Sensor: MLX90614
  MCU: PIC18F4550

  Endereçamento:
  Sensor: 0x5A
  Temperatura Ambiente: 0x06
  Temperatura Objeto: 0x07

  MudRunner 2020 - Teste interno
  Equipe Eletrônica

*/

#include<stdio.h>
#include<string.h>
#include<math.h>

const sensor = 0x5A;
const ambiente = 0x06;
const sensorbin = 0x5B;
const objeto = 0x07;
char Temp1, Temp2, Temp3, Temp4;
float temp,pressao;
unsigned int ADCResult=0;
unsigned char txt[15];

//Conectando o LCD

sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

//Protocolo de comunicação I2C (Leitura do sensor da temperatura)

int leiturasensor1(char temp_source) {
  unsigned int Temp_var, Temp_var1;

  I2C1_Start();                   // start no barramento i2c
  I2C1_Wr(sensor << 1);              // endereço da memória no barramento + comando de escrita(0)
  I2C1_Wr(temp_source);              // endereço da eeprom onde será lido o byte
  I2C1_Repeated_Start();          // re-start no barramento
  I2C1_Wr(sensor << 1);           // endereço da memória no barramento + comando de leitura(1)
  Temp_var = I2C1_Rd(0);          // Leitura do endereço
  Temp_var1 = (((I2C1_Rd(0) << 8)));  // Função para conversão de bit para decimal (Função auxiliar)
  I2C1_Stop();                    // finaliza a comunicação i2c
  return Temp_var1;
}

 void main() {

  TRISC    = 0xFE;                          //Configura o RC como saída
  PORTC    = 0xFE;                          //Inicializa o PORTC (RC em LOW)
  TRISC    = 0xFD;                          //Configura o RC como saída
  PORTC    = 0xFD;
  TRISA.RA1 = 1;

  ADCON1 = 0x0F;
  CMCON  = 0x07;
  ADC_Init();                        // Iniciando ADC
  I2C1_Init(50000);

  Lcd_Init();                        // Iniciando LCD
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Delay_ms(100);



  do {

    temp = (leiturasensor1(objeto)) / (50 - 273.15);

    ADCResult = ADC_Read(1);          // Get 10-bit results of AD conversion
    pressao = ((ADCResult*5.0)/1024);   // Lendo o sinal de entrada em volt
    pressao = ((pressao + 0.475)/0.0475); // Convertendo a saida em kPa usando a fun��o de transferencia

    FloatToStr(pressao, txt);            // Convertendo a pressao em string
    Lcd_Out(1, 1, "Pressao = ");
    Lcd_Out_Cp(txt);
    Lcd_Out_Cp("KPa");
 }  while(1);
}