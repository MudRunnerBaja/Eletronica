//Bibliotecas
#include <Arduino.h>

//Funcionalidades
#include "include/combustivel.c"
#include "include/comunicacao.c"
#include "include/display.c"
//#include "include/encoder.c"
#include "include/leds.c"

bool intialized = false, setup0Completed = false;
int rpmold;

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.print("Inicializando setup...");
    setupDisplay();
    setupEncoder();
    setup0Completed = true;
}

void setup1(){
    while (!setup0Completed)
    {
        delay(1);
    }
    setupComunicacao();   //FALTA CONSTRUIR
    setupComb();
    //setupMenu():          //FALTA CONSTRUIR
    intialized = true;
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop(){
    while(!intialized){
        delay(1);
    }
    updateDisplay(update, menu); 
    
    updateMenu(menu);
}

void loop1(){
    setCombustivel(comb);
    updateEncoder();
    canUpdate();
    
}