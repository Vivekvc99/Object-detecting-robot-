# Object-detecting-robot-
#Arduino Code


 


#include <Servo.h>
Servo leftServo;
Servo rightServo;
Servo extraServo;
const int buzzer = 12; //buzzer to arduino pin 12

int pingPin=4;
long int duration, distanceInches;
long distanceFront=0;//cm
int startAvoidanceDistance=20;//cm
long microsecondsToInches(long microseconds)
{
  return microseconds/74/2;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds/29/2;
}
long distanceCm(){
  pinMode(pingPin,OUTPUT);
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin,LOW);
  pinMode(pingPin,INPUT);
  duration=pulseIn(pingPin,HIGH);
  distanceInches=microsecondsToInches(duration);
  return microsecondsToCentimeters(duration);
}
void center()
{
//This is a brief stop when an obstacle is detected
//LED on pin 6 blinks to indicate an obstacle
digitalWrite(6,HIGH);
leftServo.write(90);
rightServo.write(90);
delay(100);
digitalWrite(6,LOW);
delay(100);
}
void moveForward()
{
  leftServo.write(0);
  rightServo.write(180);
delay(200);
  
  //Need code here for forward
  }
  void turnAround()
  {
    

 
  digitalWrite(6,HIGH);
    delay(150);
      digitalWrite(6,LOW);
   
    leftServo.write(180);

    rightServo.write(180);
    delay(600);
    
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
    
    
    

 


  
  //Add code for turning and or obstacle avoidance
  
 

  }
  
  void setup()
  {
    leftServo.attach(2);
    rightServo.attach(3);
    extraServo.attach(5);
    pinMode(4,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 12 as an output
  }
  void loop ()
  {
    digitalWrite(9,HIGH);
   digitalWrite(7,LOW);
   tone(6,1000,1000);
   delay(1000);
   
    distanceFront=distanceCm();
    if(distanceFront>1){
      if(distanceFront<startAvoidanceDistance){
        center();
        turnAround();
 delay(100);
        }
  else{
    moveForward();
    delay(125);
  }

    }
  }
  
    
    
