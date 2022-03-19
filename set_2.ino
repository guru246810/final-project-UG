#include <Wire.h>
#include <MQ2.h>
int Analog_Input = A1;                        //analog feed from MQ2
int lpg, co, smoke;                           // values from MQ2
MQ2 mq2(Analog_Input);                        //defining analog pin A1 for MQ2 Sensor
const int buzzer = 3;                         //buzzer to arduino pin 3   

void setup() {
  
Serial.begin(9600);                           //serial comms for debuging
mq2.begin();
pinMode(buzzer, OUTPUT);                    // Set buzzer - pin 3 as an output
pinMode(9,OUTPUT);                            //led as output

}

void loop() {
  
float* values= mq2.read(true);                //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
  delay(1000);

  if (co>= 50 && lpg>=50 && smoke>=50){
  tone(buzzer, 1000);                                    // Send 1KHz sound signal...
  delay(1000);                                           // ...for 1 sec
  noTone(buzzer);                                       // Stop sound...
  delay(1000);                                          // ...for 1sec
  digitalWrite(9,HIGH);
  delay(1000);
  digitalWrite(9,LOW);
  delay(1000);
  }
  else{
  pinMode(9,LOW);
  noTone(buzzer); 
  }
  }
  
