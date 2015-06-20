
/*programmer: Austin Taylor
   Date: 6/15/2015
   */
  #include <Wire.h>
  #include<Adafruit_MotorShield.h>
  
  //create the motor shield object with the default I2C address
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();
  
  // Define Constants
  #define TESTTIME 1000
  const byte SPEED = 150;  //Default speed motor
  const byte SPEED2 = 200;   // Default speed for motor
  //Define 'ports' for motors.
  const byte LEFTMOTORPORT = 3;
  const byte RIGHTMOTORPORT = 1; 
// Create pointers to motor control objects
Adafruit_DCMotor  *motorLeft = AFMS.getMotor(LEFTMOTORPORT);
Adafruit_DCMotor  *motorRight = AFMS.getMotor(RIGHTMOTORPORT); 
void setup() { 
  AFMS. begin();  // create with default frequency 1.6KHz
  // Turn off all motors to start, just a good habit 
  motorLeft->run(RELEASE);
  motorRight->run(RELEASE);
}
void loop(void){
  // delay(2000) ; // Delay for two seconds to give time to set bot down
  
  motorLeft->setSpeed(SPEED) ; // set both speeds
  motorRight->setSpeed(SPEED2);
 motorLeft-> run(FORWARD);
 motorRight-> run(FORWARD);
delay(TESTTIME); // Do not drive the motors for one second. If instead of delay TESTTIME i put while, the motors will run for the time given before the while and will stop
}
