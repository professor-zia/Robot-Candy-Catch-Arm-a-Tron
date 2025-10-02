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
	// attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
	armServo1.attach(armServo1Pin, 500, 2500);
	armServo2.attach(armServo2Pin, 500, 2500);
	armServo3.attach(armServo3Pin, 500, 2500);
	armServo4.attach(armServo4Pin, 500, 2500);
}

void loop() {

	// read the analog / millivolts value for pin 2:
	int analogValue1 = analogRead(analogJ11Pin);
	int analogValue2 = analogRead(analogJ12Pin);
	int analogValue3 = analogRead(analogJ21Pin);
	int analogValue4 = analogRead(analogJ22Pin);
	//int analogVolts = analogReadMilliVolts(analogJ11Pin);

	// print out the values you read:
	Serial.printf("ADC analog value1 = %d\n", analogValue1);
	Serial.printf("ADC analog value2 = %d\n", analogValue2);
	Serial.printf("ADC analog value3 = %d\n", analogValue3);
	Serial.printf("ADC analog value4 = %d\n", analogValue4);
	//Serial.printf("ADC milliV value = %d\n", analogVolts);

	int pos1 = map(analogValue1, 0, 4095, 0, 255);
	armServo1.write(pos1);

	int pos2 = map(analogValue2, 0, 4095, 0, 255);
	armServo2.write(pos2);

	int pos3 = map(analogValue3, 0, 4095, 0, 255);
	armServo3.write(pos3);

	int pos4 = map(analogValue4, 0, 4095, 0, 255);
	armServo4.write(pos4);
	
	/*
for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		armServo4.write(pos);  // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}
	for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
		armServo4.write(pos);                // tell servo to go to position in variable 'pos'
		delay(15);                           // waits 15ms for the servo to reach the position
	}*/
}
