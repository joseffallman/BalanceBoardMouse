#include "GyroSensor.h"


GyroSensor::GyroSensor()
{
}


GyroSensor::~GyroSensor()
{
}



//Start and handle all motion sensor
void GyroSensor::initSensor() {

	// Initialize the sensors.
	if (!gyro.begin())
	{
		/* There was a problem detecting the gyro ... check your connections */
		Serial.println("Ooops, no gyro detected ... Check your wiring!");
		while (1);
	}
	if (!accelmag.begin(ACCEL_RANGE_4G))
	{
		Serial.println("Ooops, no FXOS8700 detected ... Check your wiring!");
		while (1);
	}

	// Filter expects 70 samples per second
	// Based on a Bluefruit M0 Feather ... rate should be adjuted for other MCUs
	filter.begin(25);
}

//MySensorData* GyroSensor::GetSensorMotion() {
void GyroSensor::GetSensorMotion(int &retX, int &retY) {
	int z;
	GetSensorMotion(retX, retY, z);
}
void GyroSensor::GetSensorMotion(int &retX, int &retY, int &retZ) {
	/*
	sensors_event_t gyro_event;
	sensors_event_t accel_event;
	sensors_event_t mag_event;
	*/

	// Get new data samples
	gyro.getEvent(&gyro_event);
	accelmag.getEvent(&accel_event, &mag_event);

	// Apply mag offset compensation (base values in uTesla)
	float x = mag_event.magnetic.x - mag_offsets[0];
	float y = mag_event.magnetic.y - mag_offsets[1];
	float z = mag_event.magnetic.z - mag_offsets[2];

	// Apply mag soft iron error compensation
	float mx = x * mag_softiron_matrix[0][0] + y * mag_softiron_matrix[0][1] + z * mag_softiron_matrix[0][2];
	float my = x * mag_softiron_matrix[1][0] + y * mag_softiron_matrix[1][1] + z * mag_softiron_matrix[1][2];
	float mz = x * mag_softiron_matrix[2][0] + y * mag_softiron_matrix[2][1] + z * mag_softiron_matrix[2][2];

	// Apply gyro zero-rate error compensation
	float gx = gyro_event.gyro.x + gyro_zero_offsets[0];
	float gy = gyro_event.gyro.y + gyro_zero_offsets[1];
	float gz = gyro_event.gyro.z + gyro_zero_offsets[2];

	// The filter library expects gyro data in degrees/s, but adafruit sensor
	// uses rad/s so we need to convert them first (or adapt the filter lib
	// where they are being converted)
	gx *= 57.2958F;
	gy *= 57.2958F;
	gz *= 57.2958F;

	// Update the filter
	filter.update(gx, gy, gz,
		accel_event.acceleration.x, accel_event.acceleration.y, accel_event.acceleration.z,
		mx, my, mz);

	// Create a MySensorData object with the orientation filter output
	//return new MySensorData(filter.getRoll(), filter.getPitch(), filter.getYaw());
	retX = (int) filter.getRoll();
	retY = (int) filter.getPitch();
	retZ = (int) filter.getYaw();
}

//
// Calculates the motion 
//
int GyroSensor::calcMotion(int val) {
	if (_threshold > abs(val)) {
		return 0;
	}
	bool _negative = false;
	if (0 > val) {
		_negative = true;
	}
	val = abs(val) - _threshold;
	val = val * _multiple;
	if (_negative) { 
		return 0 - val;
	}
	return val;
	//_threshold
	//_multiple
}