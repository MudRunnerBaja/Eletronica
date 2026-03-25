//Bibliotecas
#include <Arduino.h>
//Funcionalidades
#include "include/combustivel.c"
// #include "include/comunicacao.c"
#include "include/comunicacao2515.h"
#include "include/display.c"
// #include "include/encoder.c"
#include "include/leds.c"

bool intialized = false, setup0Completed = false;
int rpmold;

void setup(){
        //Espera um enter no serial para inicializar a placa (p/ DEBUG?)
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(2, OUTPUT);
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
    // setupComb();
    // setupMenu():          //FALTA CONSTRUIR
    intialized = true;
    Serial.println("Inicializacao completa");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop(){
    while(!intialized){
        delay(1000);
    }
    // menuButton(menu);
    updateHUDMain(update, false, false); 
    // updateHUDRaw(update, menu, menu);
    // updateMenu(menu);
    // updateHUDMain(true, false, false);    
}

void loop1(){
    // setCombustivel(comb);
    updateEncoder();
    // canUpdate();
    receiveMessage(true);
    
}
