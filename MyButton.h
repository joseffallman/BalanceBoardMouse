#include <Arduino.h>

#ifndef MyButton_h
#define MyButton_h

class MyButton
{
public:
	MyButton(int pin);

	void addInput();
	int isPressed();

private:
	byte _pin;
	bool _state = false;
};

#endif

