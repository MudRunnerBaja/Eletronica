/* Habilitar bibliotecas:
   -I2C
   -UART
   -ADC
   -LCD & LCD Constants
   -Sprintf
*/
 
#define GF 2                            //Sensibilidade do strain Gauge
#define VIN 5                           //Alimentação da ponte de wheatstone(normalmente 5V)
#define AMP 150                         //Valor da amplificação do Amplificador
#define ELASTICIDADE 172000             //Modulo de elasticidade do material em Newtons por mm²
#define AREA 314                        //Area da seção transversal do material em mm²
 
sbit LCD_RS at RD3_bit;
sbit LCD_EN at RD2_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;
 
sbit LCD_RS_Direction at TRISD3_bit;
sbit LCD_EN_Direction at TRISD2_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
 
const sensor = 0x5A;
const ambiente = 0x06;
const sensorbin = 0x5B;
const objeto = 0x07;
float temp;
int count = 0;
double calibragem;
 
 
//Protocolo de comunicaçao I2C (Leitura do sensor)
 
void calibrar(double vout){
    calibragem = vout;
}
 
int leiturasensor(char temp_source) {
  unsigned int Temp_var;
 
  I2C1_Start();                                 // start no barramento i2c
  I2C1_Wr(sensor << 1);                         // endereço da memoria no barramento + comando de escrita(0)
  I2C1_Wr(temp_source);                         // endereço da eeprom onde sera lido o byte
  I2C1_Repeated_Start();                        // re-start no barramento
  I2C1_Wr(sensor << 1);                         // endereço da memoria no barramento + comando de leitura(1)
  Temp_var = I2C1_Rd(0);                        // Leitura do endereço
  Temp_var = (((I2C1_Rd(0) << 8))) + Temp_var;  // Funcao para converçao de bit para decimal (Funcao auxiliar)
  I2C1_Stop();                                  // finaliza a comunicacao i2c
  return Temp_var;
}
 
 
double calcularDeformacao(double vout){
     return ((0.5)*(4/GF)*(vout/VIN)) / (AMP) ;     //Equacao de calculo da deformação( Alterar caso necessario)
}
 
 
double calcularTensaoDeSaida(double num){
      return num*5/(1023);                          //Equacao de calculo da tensão vout
}
 
 
double calcularPressao(double vout){
       return ((vout/VIN)*100 - 4.4)/7.4;           //Equacao de calculo da pressao do sensor 5pp8-1c
}
 
void setup(){
     PCFG3_bit = 1;    PCFG2_bit = 1;    PCFG1_bit = 0;    PCFG0_bit = 1;   //seta as portas AN2 até AN12 como digitais, AN0 e AN1 analógicas
     GIE_bit = 0;                                                           //Desabilita as interrupcoes globais( evitar ocorrer uma interrupcao enquanto o pic é ligado  para evitar bugs)
     PEIE_bit = 1;                                                          //Habilita as interrupcoes por perifericos(mas nao vai interromper enquanto a interrupcao global tiver desabilitada)
     TMR1IE_bit = 1;                                                        //Habilita o Timer1
     T1CKPS1_bit = 1; T1CKPS0_bit = 1;                                      //Bits que configuram o preescaler do timer1, configurado para 1:8
     TMR1H = 0xE7;  TMR1L = 0x96;                                           //Carregando um valor inicial no timer1 para obter um estouro de 10ms
     TMR1ON_bit = 1;                                                        //Timer1 LIGADO(NAO TA FUNCIONANDO AINDA PQ AS INTERRUPCOES GLOBAIS TAO DESABILITADAS)
     TRISD.F0  = 0;                                                         //Porta RD0 definida como saída para calibragem do straingauge
     LATD.F0   = 1;                                                         //Porta RD0 setada em HIGH
     UART1_Init(9600);                                                      //Inicialização da comunicação UART
     I2C1_Init(50000);                                                      //Inicialização da comunicação I2C
     Delay_ms(100);                                                         //Delay para evitar bugs na hora de inicializar o I2C
     Lcd_Init();                                                            //Inicializacao do display LCD
     Lcd_Cmd( _LCD_CURSOR_OFF );
     Lcd_Cmd( _LCD_CLEAR );
     Lcd_Out( 1, 3, "Coef. Atrito" );
     TRISD = 0;
     GIE_bit = 1;                                                           //Habilita as interrupções GLOBAIS
 
 
 
}
 
double calcularAtrito(double temp, double deformacao, double pressao_sensor){
       return 0;
}
 
void mostrarDisplay(double coef_atrito){
            char str_coef_atrito[8];
            sprintf(str_coef_atrito, "%d", coef_atrito);
            Lcd_Out( 2, 1, "Coef: " );
            Lcd_Out( 2, 7, str_coef_atrito);
}
 
void enviarDados(double coef_atrito, double temp, double deformacao, double pressao_sensor){
            char coefstring[8],tempstring[8],deformstring[8],pressaostring[8];
 
            sprintf(coefstring, "%d", coef_atrito);
            UART1_Write_Text("coeficiente:");
            UART1_Write_Text(coefstring);
            UART1_Write(13);
            
            sprintf(tempstring, "%d", temp);
            UART1_Write_Text("temperatura:");
            UART1_Write_Text(tempstring);
            UART1_Write(13);
            
            sprintf(deformstring, "%d", deformacao);
            UART1_Write_Text("deformacao:");
            UART1_Write_Text(deformstring);
            UART1_Write(13);
            
            sprintf(pressaostring, "%d", pressao_sensor);
            UART1_Write_Text("pressao:");
            UART1_Write_Text(pressaostring);
            UART1_Write(13);
}
void interrupt(){
 
     if(TMR1IF_bit){
         count++;
         TMR1H = 0xE7;  TMR1L = 0x96;
         TMR1IF_bit = 0;
 
     }
}
 
void main() {
  double vout_sg, vout_sensor, deformacao, pressao_sensor, coef_atrito;
  setup();
 
  
  while (1) {
  
        // count == 100 para fazer o controle de 1 segundo
        if( count == 100){
            count = 0;                                        //zera o contador para reiniciar o ciclo
            
            
            //leitura dos dados
            //temp = (leiturasensor(objeto) / 50) - 273.15;     //calcula a temperatura
            vout_sg = calcularTensaoDeSaida(ADC_Read(0));     //valor da tensao de saida do sg
            
            //calibragem do sg
            if(PORTD.F0 == 0)
               calibrar(vout_sg);
               
            vout_sg -= calibragem;
            
            vout_sensor = calcularTensaoDeSaida(ADC_Read(1)); //valor da tensao de saida do sensor de pressao 5pp8-1c
            deformacao = calcularDeformacao(vout_sg);         //valor da deformacao do sg
            pressao_sensor = calcularPressao(vout_sensor);    //valor da pressao obtida pelo sensor 5pp8-1c
            
            //calculo do coef de atrito
            coef_atrito = calcularAtrito(temp, deformacao, pressao_sensor);
            
            // exibicao dos dados e telemetria
            mostrarDisplay(coef_atrito);
            enviarDados(coef_atrito, temp, deformacao, pressao_sensor);
 
        }
 
 }
}