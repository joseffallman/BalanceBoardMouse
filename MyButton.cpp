#include "MyButton.h"



MyButton::MyButton(int pin)
{
	_pin = byte(pin);
}

// Makes this pin act like a input, normally unpressed high
void MyButton::addInput() {
	pinMode(_pin, INPUT_PULLUP);
}

// Check if the button is pressed
// Return (int): 1 if button pressed
//				 2 if button is hold down
//				 -1 if it's released
//				 0 if it's untouched
int MyButton::isPressed() {
	
	// Button is newly pressed
	if (digitalRead(_pin) == LOW && _state == false) {
		_state = true;
		return 1;
	}
	// Button is hold down
	else if (digitalRead(_pin) == LOW) {
		return 2;
	}

	// Button is newly released
	else if (digitalRead(_pin) == HIGH && _state == true) {
		_state = false;
		return -1;
	}
	return 0;
}


