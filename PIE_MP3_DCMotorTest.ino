// download adafruit motor shield V2 library before using! (tools -> manage libraries)

/*
This is our code for our animatronic bear.  When the bear reads that something is close to him
through an infrared sensor, he moves forward.  When the bear is patted (touched by a limit switch),
his tail(servo motor) wags faster

For use with the Adafruit Motor Shield v2
---->	http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>
#include <Servo.h>

// declare servo
Servo myservo;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M3
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(3);

int limitSwitch = 14;
int distanceFromFood = 0; // placeholder
int distanceSensor = 1;
int servoPin = 11;
int max_time_until_check_pats = 100 ;// declaring range of tail wag loop
int time_until_check_pats = 100 ; // declaring range of tail wag loop
int pats = 0; // number of pats per loop

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  myservo.attach(servoPin);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  // if fail, check if passes the adafruit DC motor test (find online)
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      Serial.println("Could not find Motor Shield. Check wiring.");
    }
    while (1);
  }
  Serial.println("Motor Shield found.");
  pinMode(distanceSensor, INPUT);
  pinMode(limitSwitch,INPUT);
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  pats = 0; //number of pats per loop
}
void loop() {
  
  uint8_t i;
  myMotor->run(FORWARD);

  // for loop for each pat check and speeds of servo
  for (int i=0; i<5; i++){
    // it only moves forward when you pat it
    for (int j=0; j<180;j = j + pats){
      pats = pats + digitalRead(limitSwitch) ; // checks if limit switch was touched
      Serial.println(pats + "pats");
      myservo.write(j);
      // distanceFromFood = analogRead(distanceSensor);
      // myMotor->setSpeed(distanceFromFood);
      delay(100);
    }
    Serial.println(pats);
    
    
  }
  pats = 0; // reset pats after loop
}