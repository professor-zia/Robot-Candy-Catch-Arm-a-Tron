// candy_armatron_v1.ino
// F.Zia 2025_1002
// Code to test and calibrate servos for candy catch arm-a-tron
// code pre-requisites:
// - install   board: esp32 by Espressif Systems (code tested with v3.2.1)
// - install library: ESP32Servo by Kevin Harrington,John Bennett (code tested with v3.0.9)

#include <ESP32Servo.h>
// create servo object to control a servo
// 16 servo objects can be created on the ESP32
Servo armServo1, armServo2, armServo3, armServo4;

// assign pin names to servo pins
// servo are assigned to arm motors in the following order: 
// armServo1>base, armServo2>link1, armServo3>link2, armServo4>gripper
int servo1Pin = 16, servo2Pin = 17, servo3Pin = 18, servo4Pin = 19;

// joystick axes are assigned to servos in the following order:
// analogJ1X>armServo1>base, analogJ1Y>armServo2>link1, 
// analogJ2X>armServo3>link2, analogJ2Y>armServo4>gripper
// experiment by swapping the following pin number assignments to get the correct order:
int analogJ1XPin = 32, analogJ1YPin = 33, analogJ2XPin = 34, analogJ2YPin = 35;

// global variables to store current servo positions, initialize to mid positions (90 deg)
int servo1Pos = 90, servo2Pos = 90, servo3Pos = 90, servo4Pos = 90;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  //set the resolution to 12 bits (0-4095)
  analogReadResolution(12);

  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // standard 50 hz servo
  armServo1.setPeriodHertz(50);
  armServo2.setPeriodHertz(50);
  armServo3.setPeriodHertz(50);
  armServo4.setPeriodHertz(50);

  // attach the servos on pins to the servo objects
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
  // default min/max is 1000us and 2000us
  // using min/max of 500us and 2500us for micro servos used in arm-a-tron
  // for an accurate 0 to 180 sweep
  armServo1.attach(servo1Pin, 500, 2500);
  armServo2.attach(servo2Pin, 500, 2500);
  armServo3.attach(servo3Pin, 500, 2500);
  armServo4.attach(servo4Pin, 500, 2500);
}

void loop() {

  // read analog joysticks values
  int analogValue1 = analogRead(analogJ1XPin);
  int analogValue2 = analogRead(analogJ1YPin);
  int analogValue3 = analogRead(analogJ2XPin);
  int analogValue4 = analogRead(analogJ2YPin);

  // print analog joysticks values
  Serial.printf("analogValue1 = %d ,", analogValue1);
  Serial.printf("analogValue2 = %d ,", analogValue2);
  Serial.printf("analogValue3 = %d ,", analogValue3);
  Serial.printf("analogValue4 = %d\n", analogValue4);

  // control servos by mapping 12-bit (0-4095) analog values ...
  // to servos positions (0-180 degrees)
  servo1Pos = map(analogValue1, 0, 4095, 0, 180);
  armServo1.write(servo1Pos);

  servo2Pos = map(analogValue2, 0, 4095, 0, 180);
  armServo2.write(servo2Pos);

  servo3Pos = map(analogValue3, 0, 4095, 0, 180);
  armServo3.write(servo3Pos);

  servo4Pos = map(analogValue4, 0, 4095, 0, 180);
  armServo4.write(servo4Pos);
}
