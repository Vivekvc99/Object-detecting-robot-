#include <Servo.h> // Include Servo library for controlling servos

// Declare servo objects
Servo leftServo; 
Servo rightServo;
Servo extraServo;
const int buzzer = 12; // Assign buzzer to arduino pin 12

// Define pin for ultrasonic sensor
int pingPin=4;
long int duration, distanceInches;
long distanceFront=0;//cm
int startAvoidanceDistance=20;//cm  // Start avoidance if obstacle is less than 20cm

// Function to convert time to distance in inches
long microsecondsToInches(long microseconds)
{
  return microseconds/74/2;
}

// Function to convert time to distance in centimeters
long microsecondsToCentimeters(long microseconds)
{
  return microseconds/29/2;
}

// Function to calculate distance in cm
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

// Function to stop and indicate obstacle
void center()
{
  digitalWrite(6,HIGH); // Turn on indicator LED on pin 6
  leftServo.write(90); // Stop left servo
  rightServo.write(90); // Stop right servo
  delay(100);
  digitalWrite(6,LOW); // Turn off indicator LED
  delay(100);
}

// Function to move forward
void moveForward()
{
  leftServo.write(0); // Move left servo forward
  rightServo.write(180); // Move right servo forward
  delay(200);
}

// Function to turn around and avoid obstacle
void turnAround()
{
  digitalWrite(6,HIGH); // Turn on indicator LED on pin 6
  delay(150);
  digitalWrite(6,LOW); // Turn off indicator LED
  
  // Reverse both servos to turn around
  leftServo.write(180); 
  rightServo.write(180);
  delay(600);
  
  // Make buzzer sound to indicate obstacle
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
}

// Setup function for Arduino
void setup()
{
  // Attach servos to their respective pins
  leftServo.attach(2);
  rightServo.attach(3);
  extraServo.attach(5);

  // Set pins for output
  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
    
  // Set buzzer - pin 12 as an output
  pinMode(buzzer, OUTPUT); 
}

// Loop function for Arduino
void loop ()
{
  digitalWrite(9,HIGH);
  digitalWrite(7,LOW);
  tone(6,1000,1000); // Make a tone on pin 6
  delay(1000);
  
  // Get distance from ultrasonic sensor
  distanceFront=distanceCm();

  // If there is a reading from the sensor
  if(distanceFront>1){
    // If obstacle is too close
    if(distanceFront<startAvoidanceDistance){
      center(); // Stop
      turnAround(); // Turn around
      delay(100);
    }
    // If path is clear
    else{
      moveForward(); // Move forward
      delay(125);
    }
  }
}
