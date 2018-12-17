/*
  EGR 111 Robot Movement
  Final robot project 
*/

//  Preprocessor directives
#include "MeMegaPi.h"

MeUltrasonicSensor ultraSensor(PORT_7); // declare ultrasonic sensor as "FrontSensor" at Port 7

MeMegaPiDCMotor motor1(PORT1A); // 4 physical motors are divided into 8 "logical" motors

MeMegaPiDCMotor rightSide(PORT1B);

MeMegaPiDCMotor motor3(PORT2A);

MeMegaPiDCMotor leftSide(PORT2B);

MeMegaPiDCMotor motor5(PORT3A);

MeMegaPiDCMotor gantry(PORT3B);

MeMegaPiDCMotor motor7(PORT4A);

MeMegaPiDCMotor gripper(PORT4B);

//  Declairation of variables
uint8_t motorSpeed = 150;
double distCriterion = 50.0;
int sensorState;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
   
   int delaystart = 0;
   int current = 0;
   int delaay = 0;
  
  
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() ); // print detected distance
  Serial.println(" cm");
  delay(100);

{
 while(millis()- time <= 9500)
{ 
 while(ultraSensor.distanceCm() < 13)
 {
 
  motor1.run(motorSpeed); /* value: between -255 and 255. */
  rightSide.run(motorSpeed); /* value: between -255 and 255. */
  leftSide.run(-motorSpeed);
  motor4.run(-motorSpeed);
  delaystart = millis();
  delaay =(3000);
  
  
  
  motor1.stop();
  rightSide.stop();
  leftSide.stop();
  motor4.stop();
  delay(1000);
 
 }
while(ultraSensor.distanceCm()> 16 && ultraSensor.distanceCm()<60) 
 {
  motor1.run(-motorSpeed); // value: between -255 and 255. 
  rightSide.run(-motorSpeed); //value: between -255 and 255. 
  leftSide.run(-motorSpeed);
  motor4.run(-motorSpeed);
  delay(500);
  
  motor1.run(-motorSpeed); // value: between -255 and 255. 
  rightSide.run(-motorSpeed); //value: between -255 and 255. 
  leftSide.run(motorSpeed);
  motor4.run(motorSpeed);
  delay(3000);

  motor1.run(motorSpeed); // value: between -255 and 255. 
  rightSide.run(motorSpeed); //value: between -255 and 255. 
  leftSide.run(motorSpeed);
  motor4.run(motorSpeed);
  delay(1250);
      
  motor1.stop();
  rightSide.stop();
  leftSide.stop();
  motor4.stop();
  delay(500);
 }
  //  When an object is detected, robot stops moving then moves forward to the object
  while (ultraSensor.distanceCm() < distCriterion)
  {
    delay(300);
    motor1.stop();
    rightSide.stop();
    motor3.stop();
    leftSide.stop();

    motor1.run(-motorSpeed);
    rightSide.run(-motorSpeed);
    motor3.run(motorSpeed);
    leftSide.run(motorSpeed);

   while (ultraSensor.distanceCm() < 90)
  {
    rightSide.run(-100);
    leftSide.run(100);

    delay(1500);

    rightSide.stop();
    leftSide.stop();
    delay(1500);

    while (ultraSensor.distanceCm() <= 20)
    {

      // Gripper opens
      gripper.run(-200);
      delay(1200);
      gripper.stop();

      // Gantry goes down
      gantry.run(-150);
      delay(1200);
      gantry.stop();

      // Gripper closes
      gripper.run(200);
      delay(1200);
      gripper.stop();

      // Gantry raises
      gantry.run(200);
      delay(1200);
      gantry.stop();

      // Gantry lowers
      gantry.run(-90);
      delay(1200);
      gantry.stop();

      // Relases the bottle
      gripper.run(-160);
      delay(1200);
      gripper.stop();

      // Gantry goes back to default position
      gantry.run(100);
      delay(1200);
      gantry.stop();
    }
  }
  }
}
