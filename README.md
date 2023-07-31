# Eletronica
Repositório a ser usado apenas pelos membros de eletrônica da equipe baja do Cefet-RJ <br />
Por favor, ao fazer uma alteração no código, indicar o que foi alterado e colocar no READ.ME <br />

## Microcontroladores

- __Pic__:É um microcontrolador de arquitetura Harvard fabricado pela Microchip technology, ele tem a capacidade de processar dados de 8 bits, 16 bits e na versão mais atual, ele é capaz de processar dados de 32 bits. Ele possui uma alta velocidade de processamento devido a sua arquitetura Harvard, além disso, as famílias do MCU Pic  tem núcleos de processamento de 12bits, 14bits e 16bits, e trabalham em velocidade 0kHZ 48MHZ e velocidades de 16MIPS em alguns modelos.<br />   

- __Arduino__:Arduino é uma plataforma de prototipagem eletrônica de hardware livre e de placa única, projetada com um microcontrolador Atmel AVR com suporte de entrada/saída embutido, uma linguagem de programação padrão, a qual tem origem em Wiring, e é essencialmente C/C++.  Normalmente é utilizado em projetos mais simples e que não necessitam de conhecimento muito avançado sobre o firmware do microcontrolador (projetos caseiros).<br /> 

- __Esp32__:É um microcontrolador, que emprega um microprocessador de arquitetura Tensilica Xtensa LX6 de 32 bits com variações dual e single core e uma memória SRAM de 512Kb. Possui um clock máximo de 240 MHz. Ele também conta com wifi e bluetooth integrado.<br /> 

- __STM Arm__:STM32 é uma família de microcontroladores de 32 bits produzidos pela STMicroelectronics. Os chips STM32 são agrupados em séries relacionadas que são baseados em torno do mesmo núcleo do processador ARM de 32 bits, como o Cortex-M7, Cortex-M4F, Cortex-M3, Cortex-M0 +, ou Cortex-M0.<br /> 

- __RP2040__: O RP2040 é um microcontrolador de baixo custo e boa performance, criado pela Raspberry Pi. Trata-se de um processador Dual-Core ARM Cortex M0+, rodando em até 133MHz. Possui 264kB de memória SRAM e 2MB de memória Flash integrada na placa e pode ser programado em MicroPhython ou C/C++. O RP2040 possui 26 GPIOs multifunção, com 2x SPI, 2x I2C, 2x UART, 3x ADC de 12-bits e 16 canais PWM. Ela inclui um sensor de temperatura e bibliotecas para tratar ponto flutuante.<br />

### Microcontrolador escolhido pela equipe

O microcontrolador selecionado pela equipe é o RP2040, vendo sua alta performance, baixo custo e a possibilidade de ser programado pela IDE do arduino. A possibilidade de ser programado pela IDE do Arduino cria uma facilidade pela alta quantidade de bibliotecas, documentações e a familiaridade com a linguaguem de programação. Para usar esse microcontrolador, usamos a placa micro-controlada Raspberry Pi Pico.<br />

__Raspberry Pi Pico__

![Pinout Pico](https://user-images.githubusercontent.com/13077798/224742127-b1833368-27a5-40e4-bc1d-77e34551913e.jpeg)
  

## Projetos
No momento foram implementadas as seguintes funcionalidades no carro:<br />

<ul>
  <li>Medição da temperatura da CVT</li>
  <li>GPS para localização e mapeamento do carro</li>
  <li>Medidor de combustível</li>
  <li>Leitura do RPM e da Velocidade</li>
  <li>Telemetria do carro</li>
  <li>Armazenamento de dados</li>
  <li>Chamada para o box</li>
</ul><br />

### Medição da temperatura da CVT
Atualmente, muitas equipes sofrem com superaquecimento gerado não só pelo atrito dos componentes presentes na CVT, como também pela falta de ventilação do local. Para resolver essa situação, a equipe decidiu desenvolver um sistema capaz de coletar a temperatura relativa à caixa interna da proteção da CVT, e enviar esses dados pela telemetria para o box. Dessa forma, podemos evitar o rompimento da correia ao detectar um sinal de aquecimento dentro do local. <br />

Após uma análise dos módulos a serem utilizados, o escolhido foi o módulo max6675 junto ao termopar tipo K, pois: <br />

<ul>
  <li>Atende a faixa de temperatura esperada (300 ºC)</li>
  <li>Possui o cabo revestido para não afetar no dado </li>
  <li>Possui uma boa precisão </li>
  <li>Facilidade de implementação no código </li>
  <li>Comunicação rápida (SPI) </li>
  <li>Ótimo custo benefício </li>
  <li>Possui na biblioteca do PROTEUS </li>
</ul><br />

![max6675](https://user-images.githubusercontent.com/57758959/103159764-2d9ad180-47ac-11eb-93e6-ab4ec3b03b7b.jpg)<br />
*Fig 3 - Termopar max6675*<br />

```c
 /*
Código do pic 18f4550 para simulação da temperatura da CVT

Habilitar as seguintes bibliotecas:
- Lcd  e Lcd_Constants
- SPI
- Conversions e C_String e C_Type
- Uart
- C_Stdlib

Clock padrão: 20MHz
*/

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

sbit MAX6675_CS at RC0_Bit;
sbit MAX6675_CS_Direction at TRISC0_Bit;

union{
  char state:1;
  char deviceID:1;
  char open:1;
  char temperature:12;
  char sign:1;
  unsigned output;
}Max6675Data;

void MAX6675_Init(){
  MAX6675_CS_Direction = 0;
  MAX6675_CS = 1;
}

unsigned Max6675_Read(){
unsigned tmp;
  MAX6675_CS = 0;
  Hi(tmp) = SPI1_Read(0);
  Lo(tmp) = SPI1_Read(0);
  MAX6675_CS = 1;
  return(tmp);
}

void main(){
char texto[8];
int temperatura;
   PCFG3_bit = 1; PCFG2_bit = 1; PCFG1_bit = 1; PCFG0_bit = 1;
   UART1_Init(9600);
   SPI1_Init();
   MAX6675_Init();
   Lcd_Init();
   Lcd_Cmd( _LCD_CURSOR_OFF );
   Lcd_Cmd( _LCD_CLEAR );
   Lcd_Out( 1, 6, "Temperatura CVT" );
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
```

### GPS para localização e mapeamento do carro
O mapeamento de percurso é uma informação de suma importância para nossa equipe, visto que, com ela, é possível analisarmos possíveis falhas de direção, analisar as maiores dificuldades de nossos pilotos, saber se e onde o carro parou, e entre outros dados. O módulo GPS serve para transmitir em tempo real a localização do baja, a partir de dados como a longitude e a latitude. Esses dados podem posteriormente serem processados para mapear os locais visitados pelo carro, bem como sua atual posição. <br />

O módulo escolhido pela equipe foi o  GPS GY-NEO6MV2, por ser mais barato e de fácil utilização: <br />

![gps](https://user-images.githubusercontent.com/57758959/103160082-a2233f80-47af-11eb-986d-ffa3a41f8a7b.png)<br />
*Fig 4 - GPS GY-NEO6MV2*<br />

```c
/*
Código do pic 18f4550 para simulação do GPS

Habilitar as seguintes bibliotecas:
- UART
- C_String

Clock padrão: 20MHz
*/

char txt[768];   // variavel txt para guardar todos os caracteres enviados pelo GPS
char *string;    // ponteiro para guardar a informação de interesse
int i,count,value;

void GPS(){
      int j;
      string = strstr(txt,"$GPGGA");    //String GPGGA contem as informações de latitude e longitude

      // Se a variavel string não for vazia, enviamos a latitude e longitude pela telemetria
      if(string != 0) {
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
              count++;
              TMR1H= 0x0B;
              TMR1L= 0xDC;
              TMR1IF_bit = 0;
     }

     if(RCIF_bit){
              txt[i++] = UART1_Read();
              if(i==768) i=0;
              RCIF_bit = 0;
     }
}

void main() {
           PCFG3_bit = 1; PCFG2_bit = 1; PCFG1_bit = 1; PCFG0_bit = 1; // setando PORTA como digital ( evitar bugs )
           UART1_Init(9600);

           /*Configuração do timer 1 para obter o estouro desejado em ms
             Valores obtidos utilizando o clock padrão de 20MHz e preescaler de 8

              TMR1H = 0x0B;  TMR1L = 0xDC; ----> estouro de 100ms
              TMR1H = 0x85;  TMR1L = 0xEE; ----> estouro de 50ms
              TMR1H = 0xE7;  TMR1L = 0x96; ----> estouro de 10ms
              TMR1H = 0xF3;  TMR1L = 0xCB; ----> estouro de 5ms
              TMR1H = 0xFD;  TMR1L = 0x8F; ----> estouro de 1ms

           */
           TMR1IE_bit = 1;
           T1CON = 0b10110001;
           TMR1H = 0x0B;  TMR1L = 0xDC;

           TRISC.F0 = 0; // porta rc0 definida como saída

           // habilitando as interrupções globais, por periféricos e por UART
           GIE_bit = 1;
           PEIE_bit = 1;
           RCIE_bit = 1;

           while(1){

                    // count é incrementado a cada 100ms pelo timer 1, logo esse if será executado a cada 1segundo
                     if (count == 10){
                          count = 0;
                          value = ~value;
                          LATC.F0 = value;
                          GPS();
                     }

           }
}
```
### Medidor de combustível
O sistema de controle de nível de combustível é um dos circuitos mais importantes no carro, visto que com a noção do volume de gasolina presente no tanque, é possível prevenir a pane seca, que elimina a equipe da prova. Portanto, visando obter um maior tempo de carro na pista sem precisar reabastecer, é imprescindível que tenhamos um bom funcionamento nesse sistema.<br /> 

O módulo escolhido pela equipe foi o  LJC18A3,pois possui uma boa sensibilidade e é ajustável, permitindo uma melhor calibração. Já possuímos esses sensores na oficina e tivemos bons resultados com ele.<br />

![capacitivo](https://user-images.githubusercontent.com/57758959/103160265-70ab7380-47b1-11eb-94c5-ec99e95b99e8.jpg)<br />
*Fig 5 - Sensor capacitivo LJC18A3*<br />
### Leitura do RPM e da Velocidade

#### Velocidade
A velocidade do carro é um dado muito importante de se adquirir, visto que dá dados ao piloto para testar as melhores condições para fazer uma curva ou passar um obstáculo e é utilizada em diversos testes para a equipe. Com isso em mente, foi implementado um sensor de efeito hall, o qual detectava a pessagem de imãs no disco de freio. Posteriormente, vendo a imprecisão na aquisição da velocidade, causada pela folga axial no eixo da roda, o sistema de aquisição de velocidade foi substituido pela aquisição via GPS, a qual tem uma precisão de 0.1m/s.<br />

#### RPM
O motor de um baja é seu coração, portanto, controlar seu ‘batimento’ (RPM) é de suma importância para o time como um todo. É um dado imprescindível para análise de comportamento do motor, setagem de motor para TF, esforço do motor, quando mostrado ao piloto e entre outras situações.<br />

O motor utilizado possui 4 tempos que são: a admissão, a compressão, a explosão e a exaustão. Ao efetuar um ciclo completo (admissão, compressão, explosão e exaustão), uma indução eletromagnética da corrente é gerada pela bobina da vela. Para conseguir um bom valor de RPM, o sinal do motor precisa ser tratado antes dele ser transmitido para a placa. Esse tratamento de sinal se faz por filtros elétricos; com esse procedimento se espera ter um sinal na forma de onda quadrática com amplitude máxima de 3.3V.<br />

![sinais](https://user-images.githubusercontent.com/13077798/224748826-631d1fd8-9ae0-47be-bea8-870b38402c91.png)<br />
*Fig 7 - Sinal da bobina primária do motor sem o filtro e com o filtro*<br /> 

![filtroantigo](https://user-images.githubusercontent.com/57758959/103160515-f7ae1b00-47b4-11eb-8956-71e126adb942.PNG)<br />
*Fig 8 - Filtro atual implementado pela equipe*<br />


### Telemetria
Dado agora que já somos capazes de implementar na prática todos os projetos acima mencionados, damos início ao nosso projeto da Telemetria. Irá funcionar como um sistema supervisório, em que todos os dados coletados são enviados por meio de um transmissor para nosso box. Dessa forma, todos da equipe poderam observar e perceber o que está se passando no carro, ajudando nas tomadas de decisão durante a prova.<br />
De modo geral, serão 2 desafios a serem superados. O primeiro consiste em juntar todos os projetos em um só. Já o segundo se resume na criação de um sistema supervisório e interativo, o qual ficou decidido que será um site.<br />
Para transmitir nossos dados, a equipe optou por escolher os seguintes componentes:<br />

- __Módulo HC-12:__ Tal módulo foi selecionado pela sua facilidade de uso, possui um custo baixo e atender a meta de telemetria de 800m, se utilizada com uma antena adequada. A antena helicoidal (que vem junto ao módulo) tem uma limitação de até 300-500m dependendo do local. É importante estar atento a escolha do próprio módulo, devendo ele ser ORIGINAL. Existem versões genéricas que limitam o alcance.<br />  

- __Antena monopólo vertical:__ https://www.youtube.com/watch?v=nQ4qYwILRjA Nesse video, há uma validação pratica com 2 diferentes antenas usando o HC12. Explicando o porquê de utilizar a antena monopólio vertical. Como ela pode ser fabricada por nós mesmos, de forma simples e barata, ela foi selecionada.<br />

![hc12](https://user-images.githubusercontent.com/39687418/103317085-3f2ce500-4a09-11eb-96c7-58145a00bb46.PNG)
![antena](https://user-images.githubusercontent.com/39687418/103317095-4522c600-4a09-11eb-9319-c5dd3230839c.PNG)<br />
*Fig 10 - Módulo HC 12 e antena*<br />

### Chamada para o box
A comunicação entre o piloto e o box durante a competição é algo muito importante para a equipe. Dessa forma, decidimos implementar um sistema de chamada para o box que será adicionado ao projeto da telemetria que a equipe já tem. Esse sistema consiste em uma comunicação bilateral onde o piloto tem a capacidade de avisar a equipe que ele está indo para o box ou a equipe pode chamar o piloto para ir para o box para reabastecer ou devido a um problema detectado no carro. <br />
A implementação será feita por meio da adição de um diodo LED no painel do carro para avisar o piloto que ele precisa ir para o box (a equipe chamando o piloto) e uma chave Push Button (Botão) para o piloto avisar a equipe que está indo ou querendo ir para o box. <br />

![box](https://user-images.githubusercontent.com/39687418/103317573-4f918f80-4a0a-11eb-8a07-47d8383fcef5.PNG)<br />
*Fig 11 - LEDs e Push Button*br />

## Testes
Os seguintes testes estão em desenvolvimento para auxíliar a equipe quanto a otimização dos componentes do carro<:br />

<ul>
  <li>Teste de Strain Gauge</li>
  <li>Teste de retomada e aceleração</li>
  <li>Teste de CVT Tunning</li>
  <li>Teste da variação do coeficiente de atrito da pastilha e do disco</li>
  <li>Teste de vibração</li>
</ul><br />
