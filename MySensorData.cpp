#include "MySensorData.h"



MySensorData::MySensorData(float roll, float pitch, float heading)
{
	_roll = roll;
	_pitch = pitch;
	_heading = heading;
}
float MySensorData::GetRoll()
{
	return this->_roll;
}
float MySensorData::GetPitch()
{
	return this->_pitch;
}
float MySensorData::GetHeading()
{
	return this->_heading;
}