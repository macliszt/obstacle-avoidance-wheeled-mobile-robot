#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

//Define the Trig and the Echo pins
#define TRIG_PIN A1 
#define ECHO_PIN A5 

#define MAX_DISTANCE 200 
#define MAX_SPEED 120 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);// The NewPing library takes in the trig and the echo pins and also the maximum distance

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo servo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  servo.attach(9);  
  servo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 
 if(distance <= 30)//In order for it not to move too close to the wall
 {
  Stop(); //stop the car
  delay(100);
  moveBackward();
  delay(300);
  Stop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR >= distanceL)
  {
    turnRight();
    Stop();
  }
  else
  {
    turnLeft();
    Stop();
  }
 }
 else
 {
  moveForward();
 }
 distance = readPing();
}



int lookRight()
{
    servo.write(30); 
    delay(500);
    int distance = readPing();
    delay(100);
    servo.write(115); 
    return distance;
}

int lookLeft()
{
    servo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    servo.write(115); 
    return distance;
    delay(100);
}

//For the Ultrasonic sensor to measure the distance
int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();  
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}


//To stop the car
void Stop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 


//For the car to move Forward
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) //To gradually accelerate to avoid running down the batteries 
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

//To turn right and move in right direction
void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 

//To turn left and move in left direction
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}  
