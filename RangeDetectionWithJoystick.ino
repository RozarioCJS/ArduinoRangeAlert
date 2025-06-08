#include <Servo.h>
#include "SR04.h"
//Servo Code
Servo myservo;
int pos = 0;
int DPIN = 9;

//Joystick Code
const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
int val;

//Sensor Code
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

//Active Buzzer Code
const int Buzzpin = 7; 

void setup(){
  myservo.attach(DPIN);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  pinMode(Buzzpin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(X_pin);
  val = map(val,0,1023,0,189);
  myservo.write(val);
  a = sr04.Distance();
  if(a < 10){
    digitalWrite(Buzzpin, LOW);
    for(pos = 0; pos <=200; pos+=1){
      myservo.write(pos);
      delay(1);
    }
    for(pos = 200; pos>=0;pos -=1){
      myservo.write(pos);
      delay(1);
    }
  }
  else{
    digitalWrite(Buzzpin,HIGH);
  }
  Serial.print(a);
  Serial.println("cm");
  delay(15);
}