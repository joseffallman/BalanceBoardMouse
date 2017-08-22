/*
 Name:		BalanceBoardMouse.ino
 Created:	8/18/2017 1:25:55 PM
 Author:	Josef
*/

#include <Arduino.h>
#include "MyButton.h"

// Bluetooth hid
#include <bluefruit.h>
BLEDis bledis;
BLEHidAdafruit blehid;

//Gyro sensor
#include "GyroSensor.h"
GyroSensor MyGyro;
int startposX, startposY;

//Add buttons.
MyButton bMouseMove(2);  // pin A0
MyButton button2(3);  // pin A1
MyButton button3(4);  // pin A2
MyButton button4(5);  // pin A3



// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);

	
	MyGyro.initSensor();
	

	bMouseMove.addInput();
	button2.addInput();
	button3.addInput();
	button4.addInput();



	//------------------------------------------------------------- Bluetooth Settings

	Bluefruit.begin();
	// HID Device can have a min connection interval of 9*1.25 = 11.25 ms
	Bluefruit.setConnInterval(9, 16); // min = 9*1.25=11.25 ms, max = 16*1.25=20ms
	Bluefruit.setName("Bluefruit52");

	// Configure and Start Device Information Service
	bledis.setManufacturer("Adafruit Industries");
	bledis.setModel("Bluefruit Feather 52");
	bledis.begin();

	// BLE HID
	blehid.begin();

	// Set up and start advertising
	startAdv();
}

void startAdv(void)
{
	// Advertising packet
	Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
	//Bluefruit.Advertising.addTxPower();
	Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_MOUSE);

	// Include BLE HID service
	Bluefruit.Advertising.addService(blehid);

	// There is enough room for 'Name' in the advertising packet
	Bluefruit.Advertising.addName();

	/* Start Advertising
	* - Enable auto advertising if disconnected
	* - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
	* - Timeout for fast mode is 30 seconds
	* - Start(timeout) with timeout = 0 will advertise forever (until connected)
	*
	* For recommended advertising interval
	* https://developer.apple.com/library/content/qa/qa1931/_index.html
	*/
	
	//Bluefruit.Advertising.restartOnDisconnect(true);
	//Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
	//Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
	
	Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}
//------------------------------------------------------------- Bluetooth Settings

// the loop function runs over and over again until power down or reset
void loop() {

	//_state = _mouseMove.isPressed();
	if ( bMouseMove.isPressed() == 1 ) {
		MyGyro.GetSensorMotion(startposX, startposY);
		Serial.println("MouseMove is pressed");
	}
	if (bMouseMove.isPressed() > 0) {
		Serial.println("MouseMove is hold");
		int x, y;
		MyGyro.GetSensorMotion(x, y);
		x = MyGyro.calcMotion(x);
		y = MyGyro.calcMotion(y);
		blehid.mouseMove(x, -y);
	}

	/*
	_button2.isPressed();
	_button3.isPressed();
	_button4.isPressed();
	*/

	/*
	int x, y, z;
	MyGyro.GetSensorMotion(x, y, z);
	
	Serial.print("x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.print(y);
	Serial.print(" z: ");
	Serial.print(z);
	Serial.println();
	*/
	delay(10);
}
