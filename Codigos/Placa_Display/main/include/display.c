#include <U8g2lib.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include "./imagens.c"      //Biblioteca das imagens
#include "./encoder.c"

int SCKPIN = 10, CSPIN = 13;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCKPIN, TXPIN, CSPIN);

float wprpm, rpmmax = 4000;

void loadScreen();
void displayGraficos();
void displayRPM();
void displayVelo();
void displayTVolta();
void displayAvisos();


void setupDisplay(){
    u8g2.begin();
    wprpm = 128/rpmmax;
    itoa(vel/10, &tvel[0], 10);
    itoa(vel%10, &tvel[1], 10);
    itoa(rpm/1000, &trpm[0], 10);
    itoa((rpm/100)%10, &trpm[1], 10);
    //itoa((rpm%100)/10, &trpm[2], 10);
    //itoa(rpm%10, &trpm[3], 10);
    loadScreen();
}

void updateDisplay(bool refresh, bool menuInUse){
  if (refresh && !menuInUse){
    u8g2.firstPage();
  do {
    bool warning = false;

    //######### CONTEUDOS DO DISPLAY #########
    displayGraficos();
    displayRPM();
    displayVelo();
    displayTVolta();
    displayAvisos();
    
  } while (u8g2.nextPage());
  setCombustivel(comb);
  } 
}

//######## INTERFACE DE TESTES ########
void updateMenu(bool refresh){
  if(refresh){
  setEncoderKey(false);
  u8g2.firstPage();
  do {
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0,24,String(encoderPosition()).c_str());
  } while ( u8g2.nextPage() );
  }
}





/*
#############################################
############ ELEMENTOS GRAFICOS #############
#############################################
*/
void displayGraficos(){
  //FUNDO
  u8g2.setDrawColor(1);
  u8g2.drawBox(0,12,128,32);
  u8g2.drawBox(0,32,30,32);
  u8g2.drawTriangle(30,44, 30,64, 50,44);
  u8g2.drawBox(50,44,78,4);
  //FRAMES
  u8g2.drawFrame(51, 48, 76, 15);
  u8g2.drawFrame(50, 48, 78, 16);

  //BARRA ATIVA RPM
  u8g2.setDrawColor(1);
  u8g2.drawFrame(0,0,128,12);
  float w = rpm * wprpm;
  u8g2.drawBox(0,0,w,12);
}



void displayRPM(){
  u8g2.setDrawColor(0);
  //RPM
  u8g2.setFont(u8g2_font_fub30_tn);
  u8g2.drawStr(2,43, trpm);
  u8g2.setFont(u8g2_font_wedge_tr);
  u8g2.drawStr(48,17, "x100");
}

void displayVelo(){
  //VELOCIDADE
  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_fub17_tn);
  u8g2.drawStr(2,62, tvel);
  u8g2.setFont(u8g2_font_fourmat_tr);
  u8g2.drawStr(28,48, "km/h");
}


void displayTVolta(){
  u8g2.setFont(u8g2_font_helvB12_tf);
  u8g2.setDrawColor(1);
  u8g2.drawStr(53,62, "00:00:000");
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_wedge_tr);
  u8g2.drawStr(52,48, "T. Volta");
}


void displayAvisos(){
  bool warning = false;

  u8g2.setDrawColor(1);
  //NIVEL DE COMBUSTIVEL BAIXO
    //if (checkReserva()){}

    

    //TEMPERATURA CVT ALTA
   if (CVT){
      //u8g2.setFont(u8g2_font_t0_11b_mf);
      //u8g2.drawButtonUTF8(98, 62, U8G2_BTN_INV|U8G2_BTN_BW2, 0, 0, 0, "!TCVT");
      u8g2.drawXBM(96, 12, 32, 32, TCVT_xbm);
      warning = true;
    } else {


    //CONECTADO AO MASTER
    if(can_conn){     //TALVEZ POR SER IMPORTANTE BOTAR ALGUM INDICADOR MAIOR
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(115, 20, 0xe20e);
    }else{
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(115, 20, 0xe20f);
    }


    //GRAVAÇÃO CARTÃO SD
    if(sd_rw){
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(115, 31, 0xe1e1);
    }else{
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(115, 31, 0xe0ae);
    }
    

    //SINAL DE GPS
    if (gps_conn){
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(115, 42, 0xe1ba);
    }else{
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(115, 41, 0xe217);
    }
  }

    //INDICADOR DE BATERIA
    if (tensao >= 12){
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(2, 9, 0xe24B);
    }
    
    //INDICADOR DE ATENÇÃO
    if (warning){/*
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_streamline_interface_essential_circle_triangle_t);
      u8g2.drawGlyph(100,36, 0x34); */
    }
}


void loadScreen(){
    u8g2.firstPage();
     do {
        u8g2.setDrawColor(0);
        u8g2.drawXBM( 0, 0, 128, 64, mud_xbm);
        u8g2.setDrawColor(1);
        u8g2.setFont(u8g2_font_t0_13_te);
        u8g2.drawButtonUTF8(16, 62, U8G2_BTN_INV|U8G2_BTN_BW1, 0, 0, 0, "Inicializando...");
        u8g2.setFont(u8g2_font_5x8_tf);
        u8g2.drawButtonUTF8(2, 7, U8G2_BTN_INV|U8G2_BTN_BW1, 0, 0, 0, "Eletronica MudRunner 2024");
  } while (u8g2.nextPage());
}


