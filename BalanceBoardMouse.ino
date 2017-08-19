/*
 Name:		BalanceBoardMouse.ino
 Created:	8/18/2017 1:25:55 PM
 Author:	Josef
*/

#include "BalanceBoardMouse.h";
#include "MyButton.h"
MyDevice mydevice;

//Add buttons.
MyButton bMouseMove(2);  // pin A0
MyButton button2(3);  // pin A1
MyButton button3(4);  // pin A2
MyButton button4(5);  // pin A3

int startposX, startposY;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	
	mydevice.initBluetooth();
	mydevice.initSensor();
	

	bMouseMove.addInput();
	button2.addInput();
	button3.addInput();
	button4.addInput();

}

// the loop function runs over and over again until power down or reset
void loop() {

	//_state = _mouseMove.isPressed();
	if ( bMouseMove.isPressed() == 1 ) {
		mydevice.GetSensorMotion(startposX, startposY);
		Serial.println("MouseMove is pressed");
	}
	if (bMouseMove.isPressed() > 0) {
		Serial.println("MouseMove is hold");
		int x, y;
		mydevice.GetSensorMotion(x, y);
		x = mydevice.calcMotion(x);
		y = mydevice.calcMotion(y);
		mydevice.HIDmoveMouse(x, y);
	}

	/*
	_button2.isPressed();
	_button3.isPressed();
	_button4.isPressed();
	*/

	int x, y, z;
	mydevice.GetSensorMotion(x, y, z);
	
	Serial.print("x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.print(y);
	Serial.print(" z: ");
	Serial.print(z);
	Serial.println();
	delay(10);
}
