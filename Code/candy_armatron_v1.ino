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

int armServo1Pin = 16, armServo2Pin = 17, armServo3Pin = 18, armServo4Pin = 19;
int analogJ11Pin = 32, analogJ12Pin = 33, analogJ21Pin = 34, analogJ22Pin = 35;

//int pos = 0;  // variable to store the servo position

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
  armServo1.attach(armServo1Pin, 500, 2500);
  armServo2.attach(armServo2Pin, 500, 2500);
  armServo3.attach(armServo3Pin, 500, 2500);
  armServo4.attach(armServo4Pin, 500, 2500);
}

void loop() {

  // read analog joysticks values
  int analogValue1 = analogRead(analogJ11Pin);
  int analogValue2 = analogRead(analogJ12Pin);
  int analogValue3 = analogRead(analogJ21Pin);
  int analogValue4 = analogRead(analogJ22Pin);

  // print analog joysticks values
  Serial.printf("analogValue1 = %d ,", analogValue1);
  Serial.printf("analogValue2 = %d ,", analogValue2);
  Serial.printf("analogValue3 = %d ,", analogValue3);
  Serial.printf("analogValue4 = %d\n", analogValue4);

  // control servos by mapping 12-bit (0-4095) analog values ...
  // to servos positions (0-180 degrees)
  int pos1 = map(analogValue1, 0, 4095, 0, 180);
  armServo1.write(pos1);

  int pos2 = map(analogValue2, 0, 4095, 0, 180);
  armServo2.write(pos2);

  int pos3 = map(analogValue3, 0, 4095, 0, 180);
  armServo3.write(pos3);

  int pos4 = map(analogValue4, 0, 4095, 0, 180);
  armServo4.write(pos4);
}
