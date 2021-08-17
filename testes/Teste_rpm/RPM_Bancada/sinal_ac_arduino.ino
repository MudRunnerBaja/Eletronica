
#define pwm 11

float seno;
int sine;

void setup (){
  
  pinMode(pwm, OUTPUT);
  Serial.begin(9600);
  
  }

void loop(){
  
  for(int i = -180;i<180;i++){

    seno = sin(120*i*(3.1415/180.0));
     sine = 127+int(seno*255.0/2.0);


    analogWrite(pwm,sine);
    Serial.println(sine);
    delay(50);
    }  
}
