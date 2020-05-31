//Habilitar bibliotecas
//ADC
//C_Type e Sprintf
//UART

#define GF 2                            //Sensibilidade do strain Gauge
#define VIN 5                           //Alimentação da ponte de wheatstone(normalmente 5V)
#define AMP 150                         //Valor da amplificação do Amplificador
#define ELASTICIDADE 172000             //Modulo de elasticidade do material em Newtons por mm²
#define AREA 314                        //Area da seção transversal do material em mm²

double calibragem = 0;
int count = 0;

//Funcao usada para a calibração do sistema
void calibrar(double vout){
    calibragem = vout;
}

//Funcao usada para calcular a força no sistema
double calcularForca(double deformacao){
    return ELASTICIDADE*AREA*deformacao;
}

//Funcao usada para calcular a pressao no sistema
double calcularPressao(double forca){
    return forca*1000/AREA;
}

//Funcao usada para calcular a deformacao no strain gauge
double calcularDeformacao(double vout){
     return ((0.5)*(4/GF)*(vout/VIN)) / (AMP) ;
}

//Funcao usada para calcular a tensao de saida do strain gauge
double calcularTensaoDeSaida(double num){
      return num*5/(1023);
}

void interrupt(){

     if(TMR1IF_bit){
         count++;
         TMR1H = 0xE7;  TMR1L = 0x96;
         TMR1IF_bit = 0;

     }
}

void setup(){
     PCFG3_bit = 1;    PCFG2_bit = 1;    PCFG1_bit = 0;    PCFG0_bit = 1;
     GIE_bit = 0;
     PEIE_bit = 1;
     TMR1IE_bit = 1;
     T1CKPS1_bit = 1;
     T1CKPS0_bit = 1;
     TMR1H = 0xE7;  TMR1L = 0x96;
     TMR1ON_bit = 1;
     TRISD.F0  = 0;
     LATD.F0   = 1;
     UART1_Init(9600);
     GIE_bit = 1;


}

void main() {
     double vout, deformacao;
     double forca, pressao;
     char output[15];

     setup();

     while(1){
              vout = calcularTensaoDeSaida(ADC_Read(0));
              
              if(PORTD.F0 == 0)
                        calibrar(vout);
                        
              vout-=calibragem;
              
              deformacao = calcularDeformacao(vout);
              forca = calcularForca(deformacao);
              pressao = calcularPressao(forca);
              
              if (count == 100){
                        count = 0;
                        sprintf(output,"%f",deformacao);
                        UART1_Write_Text("Deformacao:");
                        UART1_Write_Text(output);
                        UART1_Write(13);

                        sprintf(output,"%f",forca);
                        UART1_Write_Text("Forca:");
                        UART1_Write_Text(output);
                        UART1_Write_Text("Newtons");
                        UART1_Write(13);

                        sprintf(output,"%f",pressao);
                        UART1_Write_Text("Pressao:");
                        UART1_Write_Text(output);
                        UART1_Write_Text("Pascals");
                        UART1_Write(13);
                        UART1_Write(13);
              }
              



     }
     
     

}