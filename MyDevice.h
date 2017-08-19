
//initBluetooth
#include <bluefruit.h>

// initSensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Mahony.h>
#include <Madgwick.h>
#define ST_LSM303DLHC_L3GD20        (0)
#define ST_LSM9DS1                  (1)
#define NXP_FXOS8700_FXAS21002      (2)
// Define your target sensor(s) here based on the list above!
#define AHRS_VARIANT   NXP_FXOS8700_FXAS21002
#include <Adafruit_FXAS21002C.h>
#include <Adafruit_FXOS8700.h>


class MyDevice
{
	public:
		//Constructor
		MyDevice();

		//Destructor
		~MyDevice();

		//Starts and handle all bluetooth setup
		void initBluetooth();
		void HIDmoveMouse(int x, int y);

		//Starts and handle all motion sensor
		void initSensor();

		// Read motion sensor and returning a MySensorData object
		//MySensorData* GetSensorMotion();
		void GetSensorMotion(int &x, int &y, int &z);
		void GetSensorMotion(int &x, int &y);
		int calcMotion(int val);

		void initButtons();
		void checkButtons();

	private:
		//
		//
		// Bluetooth
		//
		//
		BLEDis *_bledis;
		BLEHidAdafruit *_blehid;

		//
		//
		// Motion Sensor
		//
		//
		Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);
		Adafruit_FXOS8700 accelmag = Adafruit_FXOS8700(0x8700A, 0x8700B);
		// Offsets applied to raw x/y/z mag values
		float mag_offsets[3] = { 23.13F, 0.80F, 58.20F };

		// Soft iron error compensation matrix
		float mag_softiron_matrix[3][3] = { { 0.970,  -0.001,  0.005 },
		{ -0.001,  0.964, -0.009 },
		{ 0.004, -0.009,  1.070 } };

		float mag_field_strength = 41.78F;

		// Offsets applied to compensate for gyro zero-drift error for x/y/z
		float gyro_zero_offsets[3] = { 0.0F, 0.0F, 0.0F };

		// Mahony is lighter weight as a filter and should be used
		// on slower systems
		Mahony filter;
		//Madgwick filter;
		sensors_event_t gyro_event;
		sensors_event_t accel_event;
		sensors_event_t mag_event;
		const int _threshold = 5;
		const int _multiple = 1;



		//
		//
		// Buttons
		//
		//
		// 2 = A0, 3 = A1, 4 = A2, 5 = A3
		//byte _buttons[] = { 2, 3, 4, 5 };
		//int _bReading;
};

