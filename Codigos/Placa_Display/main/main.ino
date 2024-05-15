//Bibliotecas
#include <Arduino.h>

//Funcionalidades
#include "include/combustivel.c"
#include "include/comunicacao.c"
#include "include/display.c"
#include "include/encoder.c"
#include "include/imagens.c"

bool intialized = false, setup0Completed = false;


void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    Serial.print("Inicializando setup...");
    setupDisplay();
    setup0Completed = true;
}

void setup1(){
    while (!setup0Completed)
    {
        delay(1);
    }
    //setupComunicacao();
    setupComb();
    setupEncoder();
    //setupMenu();
    intialized = true;
    digitalWrite(LED_BUILTIN, HIGH);
}

void loop(){

}

void loop1(){

}