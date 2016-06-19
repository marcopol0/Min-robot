#include <AFMotor.h>
#include <Servo.h> 
#include <NewPing.h>
#include <Wire.h>

#define MAX_DISTANCE 200 // sets maximum useable sensor measuring distance to 200cm
#define MAX_SPEED 180 // sets speed of DC traction motors to 180/256 or about 70% of full speed - to get power drain down.
#define MAX_SPEED_OFFSET 20 // this sets offset to allow for differences between the two DC traction motors
#define COLL_DIST 10 // sets distance at which robot stops and reverses to 10cm
#define TURN_DIST COLL_DIST+10 // sets distance at which robot veers away from object (not reverse) to 20cm (10+10)


AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(4, MOTOR12_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency


int pos = 0; // this sets up variables for use in the sketch (code)
  int maxDist = 0;
  int maxAngle = 0;
  int maxRight = 0;
  int maxLeft = 0;
  int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;
char c;

//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(messageRecu); // register event
  Serial.begin(9600);
}
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
 
   Serial.println ("bonjour");
  delay (100);
  
}
void messageRecu(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.println ("un message est receptionne");
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  switch (x)
  {
    case 1:
      {
        moveForward();
        delay (100);
        break;
      }
      case 2:
      {
        moveBackward();
        delay (100);
        break;
      }
      case 3:
      {
        turnRight();
        delay (100);
        break;
      }
       case 4:
      {
        turnLeft();
        delay (100);
        break;
      }
      case 5:
      default:
      {
        moveStop();
        delay (100);
        break;
       }
    
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------
void moveStop() {motor1.run(RELEASE); motor2.run(RELEASE);}  // stop the motors.
//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {
    motorSet = "FORWARD";
    motor1.run(FORWARD);      // turn it on going forward
    motor2.run(FORWARD);      // turn it on going forward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
    motorSet = "BACKWARD";
    motor1.run(BACKWARD);      // turn it on going forward
    motor2.run(BACKWARD);     // turn it on going forward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  motorSet = "RIGHT";
  motor1.run(FORWARD);      // turn motor 1 forward
  motor2.run(BACKWARD);     // turn motor 2 backward
  delay(400); // run motors this way for 400ms
  motorSet = "FORWARD";
  motor1.run(FORWARD);      // set both motors back to forward
  motor2.run(FORWARD);      
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  motorSet = "LEFT";
  motor1.run(BACKWARD);     // turn motor 1 backward
  motor2.run(FORWARD);      // turn motor 2 forward
  delay(400); // run motors this way for 400ms
  motorSet = "FORWARD";
  motor1.run(FORWARD);      // turn it on going forward
  motor2.run(FORWARD);      // turn it on going forward
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void veerRight() {motor2.run(BACKWARD); delay(400); motor2.run(FORWARD);} // veering right? set right motor backwards for 400ms
//-------------------------------------------------------------------------------------------------------------------------------------
void veerLeft() {motor1.run(BACKWARD); delay(400); motor1.run(FORWARD);} // veering left? set left motor backwards for 400ms
//-------------------------------------------------------------------------------------------------------------------------------------


