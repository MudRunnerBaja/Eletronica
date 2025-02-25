#include <LiquidCrystal.h>

/*
ESSE CODIGO FOI DESENVOLVIDO PARA SER USADO EM UM ARDUINO MEGA 2560 EM CONJUNTO COM UM SHIELD DE LCD
OS SENSORES USADOS DEVEM SER NORMALMENTE ABERTO (QUANDO O FEIXE DE LUZ NÃO ESTA INTERROMPIDO O SINAL DEVE SER HIGH)
*/

long startTime, finalTime, elapsedTime;
int botao = 0;
bool ready = true, finish = false;

const int StartSensorPort = 32;
const int FinishSensorPort = 34;


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup(){ 
    Serial.begin(9600);

    lcd.begin(16,2);
    lcd.print("MUDRUNNER:");
    lcd.setCursor(0,2);
    lcd.print("TESTE ACELERACAO");

    delay(1000);

    lcd.clear();
    lcd.print("Aperte down p/");
    lcd.setCursor(0,2);
    lcd.print("testar sensores");

    delay(2000);

    lcd.clear();
    lcd.print("Aguardando");
    lcd.setCursor(0,2);
    lcd.print("1st passagem");

    Serial.print("Inicializado");

    pinMode(StartSensorPort, INPUT);
    pinMode(FinishSensorPort, INPUT);
}

void loop(){

    int vlr = analogRead(botao);
    int StartSensor = digitalRead(StartSensorPort);
    int FinalSensor = digitalRead(FinishSensorPort);

    if (StartSensor == 1 && ready == true){
        start();
    }

    if (FinalSensor == 1 && finish == true){
        finishTime();
    }

    if (vlr < 300 && vlr > 200){
        delay(200);
        sensorTest();
    }
}

void start(){
    Serial.println("SENSOR INICIAL INTERROMPIDO. Millis inical:");

    startTime = millis();
    Serial.println(startTime);

    ready = false;
    finish = true;

    lcd.clear();
    lcd.print("DETECTADO!");
    lcd.setCursor(0,2);
    lcd.print("Aguarde!");
}

void finishTime(){
    
    finalTime = millis();
    elapsedTime = finalTime - startTime;

    finish = false;
    ready = true;

    Serial.println("SENSOR FINAL INTERROMPIDO. Millis final:");
    Serial.println(finalTime);
    Serial.print("Millis Final - Millis Inicial =");
    Serial.println(elapsedTime);

    lcd.clear();
    lcd.print("Passagem:");
    lcd.setCursor(0,2);
    lcd.print(elapsedTime);
    lcd.print(" ms");

    bool continuar = false;
    while(continuar != true){
        int vlr = analogRead(0);
        if (vlr < 920){
            continuar = true;

            lcd.clear();
            lcd.print("Aguardando Pass...");
            delay(500);
        }
    }

}

void sensorTest(){

    bool done = false;

    while(done != true){
        int vlr = analogRead(botao);

        pinMode(StartSensorPort, INPUT);
        pinMode(FinishSensorPort, INPUT);

        lcd.clear();
        lcd.home();
        lcd.print("INICIO: ");

        if(digitalRead(StartSensorPort)){
            lcd.print("1");
        } else {
            lcd.print("0");
        }

        lcd.setCursor(0,2);
        lcd.print("FINAL: ");

        if(digitalRead(FinishSensorPort)){
            lcd.print("1");
        } else {
            lcd.print("0");
        }
        delay(200);

        if(vlr < 920){
            lcd.clear();
            lcd.print("Aguardando");
            lcd.setCursor(0,2);
            lcd.print("1st passagem");
            done = true;
        }
    }
}