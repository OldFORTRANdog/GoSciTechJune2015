
#include <Wire.h>
#include <Adafruit_MotorShield.h> 
#include <math.h> 
#include <breadboardbot.h>
#include <NewPing.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

/* Define Constants */

// IO Pins used
const byte LEFT_BUMP_PIN = 47;    // Define DIGITAL Pins for left
const byte RIGHT_BUMP_PIN = 46;   // and right bump sensors
const byte SONIC_TRIGGER_PIN = 51;
const byte SONIC_ECHO_PIN = 50;

// Parameters controlling program behavior
// Bump behavior
const byte FORWARD_SPEED = 215;   // Define normal speeds
const byte BACKWARD_SPEED = 175;  // and backup/turn speed


// Sonic sensor
const float TARGET_DISTANCE_INCHES = 8; 
const int MAX_SONIC_DISTANCE = 500;      // cm, optional, 500 cm is default

// Define 'ports' for motors.
const byte LEFT_MOTOR_PORT = 3;
const byte RIGHT_MOTOR_PORT = 1;

// Create pointers to motor control objects
Adafruit_DCMotor *motorLeft = AFMS.getMotor(LEFT_MOTOR_PORT);
Adafruit_DCMotor *motorRight = AFMS.getMotor(RIGHT_MOTOR_PORT);

/* Define new untrasonic sensor with trigger & echo pins and 
   the maximum distance to be sensed. */
NewPing sonic(SONIC_TRIGGER_PIN, SONIC_ECHO_PIN, MAX_SONIC_DISTANCE); 

void setup(void){
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Turn off all motors to start, just a good habit
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  Serial.begin(9600);  //Begin serial communcation
  
  /*Set up Bump Pins with Arduino internal pullup resistors
    This will make them always high unless a bump switch is hit, 
    which will make a connection to ground and they will read low. */
  pinMode(LEFT_BUMP_PIN,INPUT_PULLUP);
  pinMode(RIGHT_BUMP_PIN,INPUT_PULLUP);

  //  pinMode(SONIC_TRIGGER_PIN,OUTPUT);
  //  pinMode(SONIC_ECHO_PIN,INPUT);  
}

void loop(){
  // Test some of the sonic library functions:
  int inches = sonic.ping_in();
  Serial.print(inches);
  
  motorLeft->run(FORWARD);
  motorRight->run(FORWARD);
  
  /*  Assuming no switches closed initially.  Drive forward: */
  motorLeft->setSpeed(FORWARD_SPEED);
  motorRight->setSpeed(FORWARD_SPEED);
  
  while(digitalRead(LEFT_BUMP_PIN) && digitalRead(RIGHT_BUMP_PIN));
	//&& Distance_inches(sonic.ping()) > TARGET_DISTANCE_INCHES) 
  {
    motorLeft->run(FORWARD);
    motorRight->run(FORWARD);
  }
  
  /* If you got here, one of the bump switches was closed or B^3 is too
     close to something straight ahead */

  /* First check the LEFT sensor: */
  if(! digitalRead(LEFT_BUMP_PIN)) { // the LEFT side switch was bumped
  
    backUp(700);
    spin(90., 200, *motorLeft, *motorRight);
        
    motorLeft->run(RELEASE);               // Then stop power to the motors      
    motorRight->run(RELEASE);              // and move to next section of code

  }
  /* Then check the right sensor: */
  else if(! digitalRead(RIGHT_BUMP_PIN)) { // the RIGHT side switch was bumped
    backUp(700);
    
    spin(-90., 200, *motorLeft, *motorRight);
    
    motorLeft->run(RELEASE);               // Then stop power to the motors
    motorRight->run(RELEASE);              // and move to next section of code
  }
  /* It must have been the sonar sensor 
  else {
    motorLeft->run(RELEASE);   // So stop power to the motors
    motorRight->run(RELEASE);  // and move to next section of code
  }*/

  /*That is all!  Now go back to the beginning of the loop and 
     drive straight ahead until somehting is bumped. */
}

void backUp(int howLong) { 
    motorLeft->run(BACKWARD);
    motorRight->run(BACKWARD);
    
    motorLeft->setSpeed(BACKWARD_SPEED); 
    motorRight->setSpeed(BACKWARD_SPEED);
    
    delay(howLong);                  // for specified duration
    motorLeft->run(RELEASE);               // Then stop power to the motors
    motorRight->run(RELEASE);              // and move to next section of code
}


