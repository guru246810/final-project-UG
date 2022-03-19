
#include <Servo.h>
#include <Wire.h>
#define anInput     A0                       //analog feed from MQ135
#define co2Zero  70                          //calibrated CO2 0 level 
int servoPin = 3;                             // Declare the Servo pin   
Servo Servo1;                                 // Create a servo object   
const int buzzer = 9;                         //buzzer to arduino pin 9                      

void setup() {
  Servo1.attach(servoPin);
  pinMode(anInput,INPUT);                     //MQ135 analog feed set for input
  Serial.begin(9600);                         //serial comms for debuging
  pinMode(buzzer, OUTPUT);                    // Set buzzer - pin 9 as an output
}
void loop() {
  
int co2now[10];                               //int array for co2 readings
int co2raw = 0;                               //int for raw value of co2
int co2comp = 0;                              //int for compensated co2 
int co2ppm = 0;                               //int for calculated ppm
int zzz = 0;                                  //int for averaging


  for (int x = 0;x<10;x++){                   //samplpe co2 10x over 2 seconds
    co2now[x]=analogRead(A0);
    delay(200);
  }

for (int x = 0;x<10;x++){                     //add samples together
    zzz=zzz + co2now[x];
    
  }
  co2raw = zzz/10;                            //divide samples by 10
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp,0,1023,400,5000);      //map value for atmospheric levels

 
  Serial.print("co2 ppm value : ");                      //print co2 ppm
  Serial.println(co2ppm);                                 //print the ppm value
  if (co2ppm >= 1000){
  Servo1.write(180);
  delay(1000);
  tone(buzzer, 1000);                                    // Send 1KHz sound signal...
  delay(1000);                                           // ...for 1 sec
  noTone(buzzer);                                       // Stop sound...
  delay(1000);                                          // ...for 1sec
  }
  else if (co2ppm >= 500 && co2ppm < 599){
  Servo1.write(90);
  delay(1000);
  }
  else{
  Servo1.write(0);
  delay(5000);
  }
}
