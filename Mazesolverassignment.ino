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
 
ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12
 
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
    
    //Serial.write("TESTTESTHELP");
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

  if (sensor_values[1] > p_QTR_THRESHOLD || sensor_values[2] > p_QTR_THRESHOLD || sensor_values[3] > p_QTR_THRESHOLD || sensor_values[4] > p_QTR_THRESHOLD)
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
    Serial.print ("Left");
    Serial.println(sensor_values[0]);
    Serial.println(sensor_values[1]);
    Serial.println(sensor_values[2]);
    Serial.println(sensor_values[3]);
    Serial.println(sensor_values[4]);
    Serial.println(sensor_values[5]);
    Serial.println("end");
  }
  else if (sensor_values[5] > QTR_THRESHOLD) 
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    
     Serial.print ("Left");
     Serial.println(sensor_values[0]);
    Serial.println(sensor_values[1]);
    Serial.println(sensor_values[2]);
    Serial.println(sensor_values[3]);
    Serial.println(sensor_values[4]);
    Serial.println(sensor_values[5]);
    Serial.println("end");
  } }

}
