//
#ifndef MySensorData_h
#define MySensorData_h
class MySensorData
{
	public:
		MySensorData(float roll, float pitch, float heading);
		float GetRoll();
		float GetPitch();
		float GetHeading();

	private:
		float _roll;
		float _pitch;
		float _heading;
};
#endif
