#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
 
#define LED 13
 
// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  300  // microseconds
#define p_QTR_THRESHOLD 150 //partial for half covered, used in corner detection
  
// these might need to be tuned for different motor types
#define REVERSE_SPEED     100 // 0 is stopped, 400 is full speed
#define TURN_SPEED        100
#define FORWARD_SPEED     100
#define REVERSE_DURATION  200 // ms
#define TURN_DURATION     300 // ms
 
 
 #include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

 
ZumoMotors motors;
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 int incomingByte; //read data input
 bool InCorner;
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

 
void setup()
{
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);
   // initialize serial communication:
  Serial.begin(9600);
  pinMode(LED, HIGH);
  InCorner = 0;
   
 
}

void loop()
{

   if (Serial.available() > 0) {
    
    
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();

    
    
    

    
    
    
    
    
    if (incomingByte == 'W' || incomingByte =='w') {
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);

    }
    
    if (incomingByte == 'C' || incomingByte == 'c') {
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    InCorner = 0;

    }
    
     if (incomingByte == 'S' || incomingByte == 's') {
  motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);


    }
    
     if (incomingByte == 'A' || incomingByte == 'a') {
      
  motors.setSpeeds(-TURN_SPEED, TURN_SPEED);

       
    }
    
        //dO THE ROBOT
    if (incomingByte == 'D' || incomingByte == 'd') {
  motors.setSpeeds(TURN_SPEED, -TURN_SPEED);

   }
    
      if (incomingByte == ' ') {
      
 
    motors.setSpeeds(0,0);
  
       
    }
    
    
  }
    sensors.read(sensor_values);
    
    
    if (InCorner == 0)
    {

      
    if (sonar.ping_cm() < 20)
    {
     motors.setSpeeds(0,0);
    Serial.println("Object Detected, Once Object has moved please set Zumo in Motion using C key"); 
    InCorner = 1;
    }
      
  if (sensor_values[1] > p_QTR_THRESHOLD || sensor_values[2] > p_QTR_THRESHOLD || sensor_values[3] > p_QTR_THRESHOLD || sensor_values[3] > p_QTR_THRESHOLD)
  {
     motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    
    motors.setSpeeds(0,0);
    
    Serial.println("Corner Reached please press C when turn is complete");
    InCorner = 1;
  }
  
 else if (sensor_values[0] > QTR_THRESHOLD)
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);

  }
  else if (sensor_values[4] > QTR_THRESHOLD) 
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    

  } }

}
