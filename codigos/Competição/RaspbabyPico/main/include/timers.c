//// adicionado para realizar contagem de tempo de rodagem do motor e do carro ///
long engineElapsedTime;
long movingElapsedTime;
int engineTimerCounter; //valor lido no flash do pico
int movingTimerCounter; //valor lido no flash do pico

void readFlash();
void writeFlash();


bool timerEngine(){
    int rpm = getRpm();

    if(rpm != 0){
        engineTimerCounter += 1;
        return true;
    }
    return false;
}

bool timerMoving(){
    int spd = gpsSpdInt();
    int rpm = getRpm();

    if(spd >= 2 && rpm != 0){
        movingTimerCounter += 1;        
        return true;              
    }
    return false;
}


void timerUpdate(){
    readFlash();  
    if (timerEngine() || timerMoving()){
        writeFlash();
    }
}