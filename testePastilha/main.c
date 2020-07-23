/* ProgramaÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o PIC18F4685 - TESTE Mack1 I2C
  ProgramÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o para leitura sensor Temperatura CVT
  Sensor: MLX90614
  MCU: PIC18F4550
  EndereÃƒÆ’Ã‚Â§amento:
  Sensor: 0x5A
  Temperatura Ambiente: 0x06
  Temperatura Objeto: 0x07
  MudRunner 2020 - Teste interno
  Equipe EletrÃƒÆ’Ã‚Â´nica
*/
//Habilitar bibliotecas
//ADC
//C_Type e Sprintf
//UART

#include<stdio.h>
#include<string.h>
#include<math.h>

#define GF 2                            //Sensibilidade do strain Gauge
#define VIN 5                           //AlimentaÃ§Ã£o da ponte de wheatstone(normalmente 5V)
#define AMP 150                         //Valor da amplificaÃ§Ã£o do Amplificador
#define ELASTICIDADE 172000             //Modulo de elasticidade do material em Newtons por mmÂ²
#define AREA 314                        //Area da seÃ§Ã£o transversal do material em mmÂ²

double calibragem = 0;
int count = 0;
const sensor = 0x5A;
const ambiente = 0x06;
const sensorbin = 0x5B;
const objeto = 0x07;
char Temp1, Temp2, Temp3, Temp4;
float temp, pressao;
unsigned int ADCResult = 0;
unsigned char txt[15];
unsigned char txt2[15];

double vout, deformacao;
double forca, pressao_strain_gauge;
char output[15];

void sendData();
//Conectando o LCD

sbit LCD_RS at LATD4_bit;
sbit LCD_EN at LATD5_bit;
sbit LCD_D4 at LATD0_bit;
sbit LCD_D5 at LATD1_bit;
sbit LCD_D6 at LATD2_bit;
sbit LCD_D7 at LATD3_bit;

sbit LCD_RS_Direction at TRISD4_bit;
sbit LCD_EN_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;

//Protocolo de comunicaÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o I2C (Leitura do sensor da temperatura)

int leiturasensor1(char temp_source) {
  unsigned int Temp_var, Temp_var1;

  I2C1_Start();                   // start no barramento i2c
  I2C1_Wr(sensor << 1);              // endereÃƒÆ’Ã‚Â§o da memÃƒÆ’Ã‚Â³ria no barramento + comando de escrita(0)
  I2C1_Wr(temp_source);              // endereÃƒÆ’Ã‚Â§o da eeprom onde serÃƒÆ’Ã‚Â¡ lido o byte
  I2C1_Repeated_Start();          // re-start no barramento
  I2C1_Wr(sensor << 1);           // endereÃƒÆ’Ã‚Â§o da memÃƒÆ’Ã‚Â³ria no barramento + comando de leitura(1)
  Temp_var = I2C1_Rd(0);          // Leitura do endereÃƒÆ’Ã‚Â§o
  Temp_var1 = (((I2C1_Rd(0) << 8)));  // FunÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o para conversÃƒÆ’Ã‚Â£o de bit para decimal (FunÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o auxiliar)
  I2C1_Stop();                    // finaliza a comunicaÃƒÆ’Ã‚Â§ÃƒÆ’Ã‚Â£o i2c
  return Temp_var1;
}

void sendData() {
  if (UART_Tx_Idle()) {
    UART_Write(temp);
    UART_Write(":");
    UART_Write(pressao_strain_gauge);
    UART_Write(":");
    UART_Write(deformacao);
    UART_Write(":");
    UART_Write(forca);
    UART_Write("\n");
  }
}

void calibrar(double vout) {
  calibragem = vout;
}

double calcularForca(double deformacao) {
  return ELASTICIDADE * AREA * deformacao;
}

double calcularPressao(double forca) {
  return forca * 1000 / AREA;
}

double calcularDeformacao(double vout) {
  return ((0.5) * (4 / GF) * (vout / VIN)) / (AMP) ;
}

double calcularTensaoDeSaida(double num) {
  return num * 5 / (1023);
}

void main() {

  TRISC    = 0xFE;                          //Configura o RC como saÃƒÆ’Ã‚Â­da
  PORTC    = 0xFE;                          //Inicializa o PORTC (RC em LOW)
  TRISC    = 0xFD;                          //Configura o RC como saÃƒÆ’Ã‚Â­da
  PORTC    = 0xFD;
  TRISA.RA1 = 1;

  ADCON1 = 0x0F;
  CMCON  = 0x07;
  ADC_Init();                        // Iniciando ADC
  I2C1_Init(50000);

  Lcd_Init();                        // Iniciando LCD
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);

  Uart1_Init(9600);

  Delay_ms(100);

  do {
     // Strain gauge
     vout = calcularTensaoDeSaida(ADC_Read(0));

    if (PORTD.F0 == 0)
      calibrar(vout);

    vout -= calibragem;

    deformacao = calcularDeformacao(vout);
    forca = calcularForca(deformacao);
    pressao_strain_gauge = calcularPressao(forca);

    //Temperatura
    temp = (leiturasensor1(objeto)) / (50 - 273.15);

    //Pressão
    ADCResult = ADC_Read(1);          // Get 10-bit results of AD conversion
    pressao = ((ADCResult * 5.0) / 1024); // Lendo o sinal de entrada em volt
    pressao = ((pressao + 0.475) / 0.0475); // Convertendo a saida em kPa usando a funÃƒÂ§ÃƒÂ£o de transferencia

    FloatToStr(pressao, txt);            // Convertendo a pressao em string
    Lcd_Out(1, 1, "Pressao = ");
    Lcd_Out_Cp(txt);
    Lcd_Out_Cp("KPa");

    FloatToStr(temp, txt2);            // Convertendo a temperatura em string
    Lcd_Out(2, 1, "Temperatura = ");
    Lcd_Out_Cp(txt2);
    Lcd_Out_Cp("°C");

    sendData();

  }  while (1);
}
