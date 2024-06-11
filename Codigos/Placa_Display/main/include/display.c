#include <U8g2lib.h>
#include <SPI.h>
#include <SoftwareSerial.h>

#include "./imagens.c"      //Biblioteca das imagens
#include "./encoder.c"


int SCKPIN = 10, CSPIN = 13;
int TXPIN = 11; // MOSI
int RXPIN = 12; // MISO
int RESETPIN = 14;
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, SCKPIN, TXPIN, CSPIN, RESETPIN);

float wprpm, rpmmax = 4000;
bool  raw = false;

void loadScreen();
void displayGraficos();
void displayRPM();
void displayVelo();
void displayTVolta();
void displayTVoltaAnterior();
void displayAvisos();
void rawInfos();


void setupDisplay(){
    u8g2.begin();
    wprpm = 128/rpmmax;
    itoa(vel/10, &tvel[0], 10);
    itoa(vel%10, &tvel[1], 10);
    itoa(rpm/1000, &trpm[0], 10);
    itoa((rpm/100)%10, &trpm[1], 10);
    loadScreen();
}



void updateHUDMain(bool refresh, bool menuInUse, bool rawInUse){
  if (refresh && !menuInUse && !rawInUse){
    u8g2.firstPage();
  do {
    bool warning = false;

    // CONTEUDOS DO DISPLAY 
    displayGraficos();
    displayRPM();
    displayVelo();
    displayTVolta();
    displayTVoltaAnterior();
    displayAvisos();
    
  } while (u8g2.nextPage());
  } 
}

void updateHUDRaw(bool refresh, bool menuInUse, bool rawInUse){
  if (refresh && !menuInUse && rawInUse){
    u8g2.firstPage();
  do {
    rawInfos();
  } while (u8g2.nextPage());
  } 
}

//MENU 
void updateMenu(bool menuInUse){
  if(menuInUse){
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_helvB12_tf);
    u8g2.setDrawColor(2);
    switch(encoderPosition()){
      case -1:
        overrideEnc(3);
        break;
      case 0:
        u8g2.drawStr(0,15,"SETAR VOLTA");
        u8g2.drawBox(0,0,128,17);
        u8g2.drawStr(0,31,"HUD MAIN");
        u8g2.drawStr(0,47,"HUD TESTES");
        u8g2.drawStr(0,63,"SETUP");
        break;

      case 1:
        u8g2.drawStr(0,15,"SETAR VOLTA");
        u8g2.drawStr(0,31,"HUD MAIN");
        u8g2.drawBox(0,16,128,17);
        u8g2.drawStr(0,47,"HUD TESTES");
        u8g2.drawStr(0,63,"SETUP");
        break;

      case 2:
        u8g2.drawStr(0,15,"SETAR VOLTA");
        u8g2.drawStr(0,31,"HUD MAIN");
        u8g2.drawStr(0,47,"HUD TESTES");
        u8g2.drawBox(0,32,128,17);
        u8g2.drawStr(0,63,"SETUP");
        break;

      case 3:
        u8g2.drawStr(0,15,"SETAR VOLTA");
        u8g2.drawStr(0,31,"HUD MAIN");
        u8g2.drawStr(0,47,"HUD TESTES");
        u8g2.drawStr(0,63,"SETUP");
        u8g2.drawBox(0,48,128,17);
        break;

      case 4:
        overrideEnc(0);
        break;
    }
  } while ( u8g2.nextPage() );
  Serial.print(menu);  Serial.print(raw);
  Serial.println();

  if(toogleButton(500)){
    if(encoderPosition()==0){
     setLap = true;// Depois que a placa central setar a volta tem que retornar a FALSE
    }

    if(encoderPosition()==1){
      Serial.println("HUD PRINCIPAL");
      overrideEnc(0);
      menu = false;
      raw = false;
    }

    if(encoderPosition()==2){
      Serial.println("HUD CRUA");

      overrideEnc(0);
      menu = false;
      raw = true;
    }
    if(encoderPosition()==3){
      int i;
      while (!i)
      {
        u8g2.firstPage();
        do {
          if (encoderPosition()<0){overrideEnc(0);}
          if (encoderPosition()>20){overrideEnc(20);}

          int percentLed = encoderPosition() * 5;

          u8g2.setCursor(0,16);
          u8g2.printf("Brilho Comb:\n%d",percentLed);

          brilho = map(percentLed, 0, 100, 0, 255);
        } while (u8g2.nextPage());
        if(toogleButton(1000)){
        Serial.println("Setado Brilho");
        overrideEnc(0);
        break;
        }
      }
    }
  }
 }
}


//LOADSCREEN

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




/*
#############################################
############ ELEMENTOS GRAFICOS #############
#############################################
*/
void displayGraficos(){
  //FUNDO
  u8g2.setDrawColor(1);
  u8g2.drawBox(0,13,128,32);
  u8g2.drawBox(0,32,30,32);
  u8g2.drawTriangle(30,44, 30,64, 50,44);
  u8g2.drawBox(50,44,78,4);





  //FRAMES
  u8g2.setDrawColor(1);
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
  u8g2.drawStr(2,45, trpm);
  u8g2.setFont(u8g2_font_wedge_tr);
  u8g2.drawStr(48,19, "x100");
}

void displayVelo(){
  //VELOCIDADE
  u8g2.setDrawColor(2);
  u8g2.setFont(u8g2_font_fub17_tn);
  u8g2.drawStr(2,63, tvel);
  u8g2.setFont(u8g2_font_fourmat_tr);
  u8g2.drawStr(28,49, "km/h");
}


void displayTVolta(){
  u8g2.setFont(u8g2_font_helvB12_tf);
  u8g2.setDrawColor(1);
  u8g2.drawStr(53,62, "00:00:000");
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_wedge_tr);
  u8g2.drawStr(52,47, "Lap");
}

void displayTVoltaAnterior(){
  if (!CVT){
  u8g2.setDrawColor(0);
  u8g2.drawBox(52,28,74,13);
  u8g2.setFont(u8g2_font_helvB12_tf);
  u8g2.setDrawColor(1);
  u8g2.drawStr(53,41, "00:00:000");
  u8g2.setDrawColor(0);
  u8g2.setFont(u8g2_font_wedge_tr);
  u8g2.drawStr(52,27, "Last Lap");
  }
}


void displayAvisos(){
  bool warning = false;

  u8g2.setDrawColor(1);
  //NIVEL DE COMBUSTIVEL BAIXO
    //if (checkReserva()){}

    

    //TEMPERATURA CVT ALTA
   if (CVT){
      u8g2.drawXBM(96, 13, 32, 32, TCVT_xbm);
      warning = true;
    }

    //CONECTADO AO MASTER
    if(can_conn){     //TALVEZ POR SER IMPORTANTE BOTAR ALGUM INDICADOR MAIOR
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(114, 9, 0xe20e);
    }else{
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(114, 9, 0xe20f);
    }


    //GRAVAÇÃO CARTÃO SD
    if(sd_rw){
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(102, 10, 0xe1e1);
    }else{
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(102, 10, 0xe0ae);
    }
    

    //SINAL DE GPS
    if (gps_conn){
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(91, 10, 0xe1ba);
    }else{
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(91, 9, 0xe217);
    }


    //INDICADOR DE BATERIA
    if (tensao >= 12){
      u8g2.setDrawColor(2);
      u8g2.setFont(u8g2_font_siji_t_6x10);
      u8g2.drawGlyph(2, 10, 0xe24B);
    }
    
    //INDICADOR DE ATENÇÃO
    if (warning){/*
      u8g2.setDrawColor(0);
      u8g2.setFont(u8g2_font_streamline_interface_essential_circle_triangle_t);
      u8g2.drawGlyph(100,36, 0x34); */
    }
}

void rawInfos(){// RPM, Vel eixo, vel gps, press freio, nivel comb, nivel freio, acelerador, temp cvt, tensão bat, tempos, volta
  int PosY = 7;
  static int StepY = 8;

  u8g2.setDrawColor(1);
  u8g2.setFont(u8g2_font_wedge_tr);
  u8g2.drawLine(64,0,64,64);

 
  //COLUNA 1 - RPM Motor/RPM Movida
  u8g2.drawFrame(0,0,128,9);

  u8g2.setCursor(2,PosY);
  u8g2.printf("RPM Mt:%4d", rpm);

  u8g2.setCursor(66,PosY);
  u8g2.printf("RPM Mv:%4d", rpmMovida);

  //COLUNA 2 - Velocidade Eixo/ Velocidade GPS
  u8g2.drawFrame(0,8,128,9);
  PosY += StepY;

  u8g2.setCursor(2,PosY);
  u8g2.printf("V Eixo:%3d", vel);

  u8g2.setCursor(66,PosY);
  u8g2.printf("V GPS:%3d", velGps);

  //COLUNA 3 - Pressão Freio/Acelerador
  u8g2.drawFrame(0,16,128,9);
  PosY += StepY;

   u8g2.setCursor(2,PosY);
  u8g2.printf("P.Freio:%4.0f", pressFreio);

  u8g2.setCursor(66,PosY);
  u8g2.printf("Acel:%3.1f", posAcelerador);

  //COLUNA 4 - Nivel Comb/Nivel Freio
  u8g2.drawFrame(0,24,128,9);
  PosY += StepY;

   u8g2.setCursor(2,PosY);
  u8g2.printf("N.Comb:%d", comb);

  u8g2.setCursor(66,PosY);
  u8g2.printf("N.Fre:%d", nivelFreio);

  //COLUNA 5  - TempCVT/Temp protecão
  u8g2.drawFrame(0,32,128,9);
  PosY += StepY;

   u8g2.setCursor(2,PosY);
  u8g2.printf("T.CVT:%3.1f", TCvt);

  u8g2.setCursor(66,PosY);
  u8g2.printf("T.Prot:%3.1f", TProtecao,1);

  //COLUNA 6 - Bateria/Tempo Ativo
  u8g2.drawFrame(0,40,128,9);
  PosY += StepY;

   u8g2.setCursor(2,PosY);
  u8g2.printf("Volts:%2.1f", tensao,1);

  u8g2.setCursor(66,PosY);
  u8g2.printf("T.On:%d", tOn);

  //COLUNA 7 - Tempos
  u8g2.drawFrame(0,48,128,9);
  PosY += StepY;

   u8g2.setCursor(2,PosY);
  u8g2.printf("T.Lap:%d", tOn);

  u8g2.setCursor(66,PosY);
  u8g2.printf("T.OLap:%d", tOn);

  //COLUNA 8 - Delta T/Voltas
  u8g2.drawFrame(0,56,128,8);
  PosY += StepY;

 u8g2.setCursor(2,PosY);
  u8g2.printf("Delta:%d", tlap - tlapOld);

  u8g2.setCursor(66,PosY);
  u8g2.printf("Lap:%2d", volta);

}





