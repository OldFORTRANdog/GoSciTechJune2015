#include <BreadBoardBot.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h> 

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield (); 

// Define Constants
#define TESTTIME 1000

const byte SPEED = 200; // Default speed for motors

// Define 'ports' for motors.
const byte LEFTMOTORPORT = 3;
const byte RIGHTMOTORPORT = 1;
// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHTMOTORPORT);

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}

void loop(void){
  
 // delay(2000); // Delay for two seconds to give time to place the robot.

    motorLeft->setSpeed(SPEED);  // Set both speeds
    motorRight->setSpeed(SPEED);
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
delay(TESTTIME);  // Run for 1 second
     // Turn off all motors 
    motorLeft->run(RELEASE);
    motorRight->run(RELEASE);
      delay(TESTTIME);  // Do not drive the motors for 1 second
}
