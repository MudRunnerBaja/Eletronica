//Bibliotecas
#include <Arduino.h>
//Funcionalidades
#include "include/combustivel.c"
#include "include/comunicacao2515.h"
#include "include/display.c"
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
    setupComunicacao();   
    
    tupMenu():          
    intialized = true;
    Serial.println("Inicializacao completa");
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop(){
    while(!intialized){
        delay(1000);
    }
    menuButton(menu);
    updateHUDMain(update, menu, menu); 
    updateHUDRaw(update, menu, menu);
    updateMenu(menu);
        
}

void loop1(){
   
    updateEncoder();
    
    receiveMessage(true);
    
}
