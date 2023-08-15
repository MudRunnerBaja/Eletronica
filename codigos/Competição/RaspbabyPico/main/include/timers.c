//// adicionado para realizar contagem de tempo de rodagem do motor e do carro ////
int engineElapsedTime;
int movingElapsedTime;
int engineTimerCounter;
int movingTimerCounter;


int timerEngine(){
    while(getRpm() != 0 && millis >= engineElapsedTime){
        engineTimerCounter = engineTimerCounter + 1;
        engineElapsedTime = millis + 1000;
    }
    return engineTimerCounter;    
}

int timerMoving(){
    while(gpsSpdFloat() >= 1 && getRpm() != 0 && millis >= movingElapsedTime){
        movingTimerCounter = movingTimerCounter + 3;        
        movingElapsedTime = millis + 3000;              //Delay de 3 segundos para evitar falsos positivos (falsa movimentação do gps mesmo carro estando imovel, quando o sinal esta fraco)
    }
    return movingTimerCounter;
}
