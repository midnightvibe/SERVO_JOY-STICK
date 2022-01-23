#include <Arduino.h>
#include <ESP32Servo.h>

/* Servo Log: 1 23.01.2022
 * The library worked very well even tho I still dont know how the library works.
 * I deleted everything that wasnt nessecary, and added the JoyStick
*/


int xValuePin = 12;			// Joystick VRx pin 
int yValuePin = 14;			// Joystick VRy pin
int pos; 					// pos in degrees int prevents servo ratteling 
							// float causes the servo to rattle since the current always changes a little
int Xmax = 4095; 			// convert joystick output into degrees

#define LED_BUILTIN 2
int b;

// create servo object
Servo myservo;
int myservopin = 13; 		// must be an pmw pin


void setup() {
	Serial.begin(115200);			  // Setup Serial Monitor
	myservo.setPeriodHertz(50);      // Standard 50hz servo
	pinMode(LED_BUILTIN,OUTPUT);	// tells the pin to put out a current
}

void loop() {

	// just for debugging
	Serial.print("y-value: "); 			// not relevant for servo
	Serial.print(analogRead(yValuePin));
	Serial.print("		");

	Serial.print("x-value: "); 			// x value in this case between 4095 and 0
	Serial.print(analogRead(xValuePin));
	Serial.print("		");

	pos = analogRead(xValuePin); 		// read the x-value in order to map it
	pos = map(pos, 0, Xmax, 0, 180); 	// converts x-values into degrees
	
	// also for debugging
	Serial.print("degrees: "); 			// pos = position in the case of a servos this can be a value between 0 an 180
	Serial.print(pos);
	Serial.print("\n");

	myservo.attach(myservopin); 		// tells the ESP32 to witch pin the servo is attached
	myservo.write(pos); 				// servo gets his degrees to work with

	int a = analogRead(xValuePin);
	if (a<Xmax & a>0){
		digitalWrite(LED_BUILTIN,HIGH);
		}

		else {

			digitalWrite(LED_BUILTIN,LOW);
		}
	
	
	delay(22); // lowest possible delay not sure why
}