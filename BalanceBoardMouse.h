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

