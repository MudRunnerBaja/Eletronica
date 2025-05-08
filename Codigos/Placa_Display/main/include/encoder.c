#include <RotaryEncoder.h>

int S1PIN = 20;
int S2PIN = 21;
int KEY = 22;
RotaryEncoder encoder(S1PIN, S2PIN, RotaryEncoder::LatchMode::FOUR3);

bool bnt, menu = false;


int encoderPosition(){
    return encoder.getPosition();
}

void updateEncoder(){
    encoder.tick();
}

void overrideEnc(int valor){
    encoder.setPosition(valor);
}

int lastButtonState;
long buttonPressTime, currentTime;
int toogleButton(int ms){
    bool pressed;
    long currentTime = millis();
    int buttonState = digitalRead(KEY);

    if (buttonState == LOW && lastButtonState == HIGH) {
        buttonPressTime = currentTime;
    } else if (buttonState == HIGH && lastButtonState == LOW) {
        buttonPressTime = 0; 
    }

    if (buttonState == LOW && (currentTime - buttonPressTime >= ms)) {
        pressed = true;
    } else {
        pressed = false;
    }
    lastButtonState = buttonState;

    return pressed;
    }


void menuButton(bool enabled){
    if(!enabled){
        if(toogleButton(2000)){
            menu = true;
        } else {
            menu = false;
        }
    }
}

int encoderKey(){
    return digitalRead(KEY);
}


void setupEncoder(){
    pinMode(KEY, INPUT);
    digitalWrite(KEY, HIGH);
}