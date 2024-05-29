


#include <RotaryEncoder.h>

int S1PIN = 20;
int S2PIN = 21;
int KEY = 22;
RotaryEncoder encoder(S1PIN, S2PIN, RotaryEncoder::LatchMode::FOUR3);

bool bnt, menu;


int encoderPosition(){
    static int pos = 0;
    encoder.tick();
    return encoder.getPosition();;
}

void updateEncoder(){
    encoder.tick();

}

int i;
void encoderButton(){
    Serial.println("BOTAO");
    if (i>2000 && !menu){            //ACHAR OUTRO MEIO DE VERIFICAR TOGGLE POR 2 SEGUNDOS
        //detachInterrupt(digitalPinToInterrupt(KEY));
        Serial.println("MENU");
        i = 0;
        menu = true;
    }
    i++;
    delay(1);
}

void setEncoderKey(bool attach){
    if (attach){
        attachInterrupt(digitalPinToInterrupt(KEY), encoderButton, LOW);
    } else {
        detachInterrupt(digitalPinToInterrupt(KEY));
    }
}
/*
int encoderKey(){
    int but  = digitalRead(KEY);
    return but;
}
*/



void setupEncoder(){
    pinMode(KEY, INPUT);
    setEncoderKey(true);
}