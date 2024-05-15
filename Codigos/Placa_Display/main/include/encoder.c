

#include <RotaryEncoder.h>

int S1PIN = 20;
int S2PIN = 21;
int KEY = 22;
RotaryEncoder encoder(S1PIN, S2PIN, RotaryEncoder::LatchMode::FOUR3);

int newPos;
bool bnt;


void setupEncoder(){
    pinMode(KEY, INPUT);
}


int encoderPosition(){
    static int pos = 0;

    encoder.tick();

    newPos = encoder.getPosition();
    if (pos != newPos) {
        pos = newPos;   
    }
    return newPos;
}

bool encoderKey(){
    int but  = digitalRead(KEY);
   /* if (!but){ 
        bool bnt = true;
        } else {
        bool bnt = false;
        }*/
    return but;
}
