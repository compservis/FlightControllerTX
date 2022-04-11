#include <Wire.h>
#include "HX711.h"
#include <SPI.h>

// ADC
HX711 scale(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

int calibration_factor = 3178;
float cal_y1 = 500.0;
long cal_x1 = 0L;
long cal_x0 = 0L;

double units;  // weight in g
double units_setpoint;
double delta; 
double gramm_max = 0;  
double gramm_min = 1000; 

void initThrust() 
{
	scale.tare(10);
	scale.set_scale(calibration_factor);
	units_setpoint = 50;
}

float readThrustUnits() 
{
	if (scale.is_ready()) 
	{

		units = scale.get_units_direct();

		if (gramm_min>units) gramm_min = units;
		if (gramm_max<units) gramm_max = units;

		delta = units - units_setpoint;
	}

	return (float)round(abs(units));
}

float readThrustDelta() 
{
	if (scale.is_ready()) 
	{

		units = scale.get_units_direct();

		if (gramm_min>units) gramm_min = units;
		if (gramm_max<units) gramm_max = units;

		delta = units - units_setpoint;
	}

	return (float)round(abs(delta));
}

void encreaseCalibrationCoef()
{
	gramm_max=0;
	gramm_min=1000;
} 

void decreaseCalibrationCoef()
{
	calibration_factor=units/500.0;
	scale.set_scale(calibration_factor);
} 

void applyCalibrationCoef() 
{
	scale.set_scale(); 
	gramm_max=0;
	gramm_min=1000; 
} 

void calibrateThrust() 
{
	scale.tare();
	gramm_max=0;
	gramm_min=1000;
} 