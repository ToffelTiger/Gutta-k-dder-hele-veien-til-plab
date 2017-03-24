#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewPing.h>
#include <NewServo.h>
#include <Pushbutton.h>
#include <PLab_ZumoMotors.h>
#include <PLabBTSerial.h>

#define txPin 2 // Her
#define rxPin 3 // Her


#define LED 13
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  200 // 
// these might need to be tuned for different motor types
#define REVERSE_SPEED     200 // 0 is stopped, 400 is full speed
#define TURN_SPEED        200
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
#define MAX_SPEED         400

ZumoMotors motors;
PLab_ZumoMotors plabMotors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

PLabBTSerial btSerial(txPin, rxPin); // Her
 
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




int degreesServo = 80;
int degreesStep = 10;
boolean turnedYet = false;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600); // Her
  pinMode(ledPin,OUTPUT);
  myServo.attach(servoPin); 
  myServo.write(90-30);
  sensors.init();
  button.waitForButton(); // start when button pressed
  motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  
}

void loop() {
  warMode();
}
 
void warMode() {

  static bool front = false;

   if (!front){  
   degreesServo = degreesServo + degreesStep;
   
   if (degreesServo > 170) {
       degreesStep = -degreesStep;
       degreesServo = 170;
   } else if (degreesServo < -20) {
       degreesStep = -degreesStep;
       degreesServo = -20;
   } 
   myServo.write(degreesServo);
   }
   //Serial.println(degreesServo); //høyre side = 0, venstre side 180
   
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar.ping();
  float distance = sonar.convert_cm(time);
 // Serial.println(distance);

  if (distance == 0.0) { // sonar gives zero when outside range
      // Turn off LED and just go forward
      digitalWrite(ledPin,LOW);
      motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
      front = false;
      //turnedYet = false; 
   } else {
    
    //Serial.println(degreesServo);
    //delay(500);
      digitalWrite(ledPin,HIGH);
      if (degreesServo+30 > 100 ) { // && !turnedYet) {
        plabMotors.turnLeft(400, (float)(degreesServo - 60)/10);
        Serial.println("LEFT");
        Serial.println(60 - degreesServo);
        //motors.setSpeeds(MAX_SPEED, MAX_SPEED);
       // delay(2000);
        turnedYet = true;
      }
      else if(degreesServo+30 < 80 ){ // && !turnedYet) {
        plabMotors.turnRight(400,(float)(60 - degreesServo)/5);
        //motors.setSpeeds(MAX_SPEED, MAX_SPEED);
        Serial.println("RIGHT");
        myServo.write(120);
      // delay(2000);
        turnedYet = true;
      }
      //else {
      //  motors.setSpeeds(MAX_SPEED, MAX_SPEED);
      //}
      motors.setSpeeds(MAX_SPEED, MAX_SPEED);
       
      myServo.write(60);
      degreesServo = 60;
      front = true;
    
   }

   sensors.read(sensor_values);

  if (sensor_values[0] < QTR_THRESHOLD)
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensor_values[5] < QTR_THRESHOLD)
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  /*
  else
  {
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
*/
while (btSerial.available()) { //Her
    char c = btSerial.read();
    Serial.write(c);

    if (c == 'w') {
      Serial.write("war mode");
    } else if (c == 's') {
      Serial.write("suicide mode");
    } else if (c == 't') {
      Serial.write("tiss mode");
    } else if (c == 'c') {
      Serial.write("chill mode");
    }
  } // Til her
}

