#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>


#define LED 13
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  200 // 
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms

ZumoMotors motors;
PLab_ZumoMotors plabMotors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors;



const int ledPin=A5;

const int echoPin = A4;
const int triggerPin = A4;
const int maxDistance = 50;

const int servoPin = 6;
 
NewPing sonar(triggerPin, echoPin, maxDistance);
NewServo myServo; 




int degreesServo = 0;
int degreesStep = 10;
boolean turnedYet = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90-30);
  sensors.init();
  button.waitForButton(); // start when button pressed
  motors.setSpeeds(400,400);
  
}
 
void loop() {
  motors.setSpeeds(400, 400);
}

