/*
LaserSupport.cpp - Library for support with the ladarlite range sensor
Created by Jay Lewis William Demeijer Hansen, April 7, 2015.

Copyright (c) 2015 Jay Lewis William Demeijer Hansen

Permission is hereby granted, free of unsigned charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

//functions inspried from https://github.com/PulsedLight3D/LIDAR_Lite_PWM_Fix
//AND https://github.com/PulsedLight3D/LIDARLite_Basics/tree/master/Arduino/LIDARLite_PWM_GetDistance_ContinuousRead

#include <Arduino.h>
#include <LaserSupport.h>
#include <I2C.h>

#define    LaserDistanceToCM   3.93701

#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.

//PWMLaser constructor
PWMLaser LaserSupport_h::PWMLaser(unsigned char LASER_TRIGGER_PIN, unsigned char LASER_MONITOR_PIN, unsigned char LASER_PE_LINE)
{
	_LASER_TRIGGER_PIN = LASER_TRIGGER_PIN;
	_LASER_MONITOR_PIN = LASER_MONITOR_PIN;
	_LASER_PE_LINE     = LASER_PE_LINE;

	pinMode(_LASER_TRIGGER_PIN, OUTPUT);					// Set pin as trigger pin
	pinMode(_LASER_MONITOR_PIN, INPUT);						// Set pin as monitor pin
	pinMode(_LASER_PE_LINE, OUTPUT);						// Set pin to control power enable line

	digitalWrite(_LASER_PE_LINE, HIGH);					    // Turn sensor on
	digitalWrite(_LASER_TRIGGER_PIN, LOW);			    	// Set trigger LOW for continuous read
}

// Gets the current distance in CM from the laser sensor, however when we return a 0 it means the sensor may lockup
unsigned long PWMLaser::getLaserDistance()
{
	_pulseWidth = pulseIn(_LASER_MONITOR_PIN, HIGH);            // Count how long the pulse is high in microseconds
	if (_pulseWidth)                                            // If we get a reading that isn't zero
	{ 
		return (_pulseWidth / LaserDistanceToCM);    // 10usec = 1 cm of distance for LIDAR-Lite
	}
	return 0;													//warning, the sensor is about to lockup
}

// Gets the current distance in CM from the laser sensor
unsigned long PWMLaser::getLaserDistanceSafe()
{
	_pulseWidth = pulseIn(_LASER_MONITOR_PIN, HIGH);     // Count how long the pulse is high in microseconds

	while (!_pulseWidth) // We read a zero which means we're locking up. restart the sensor and try again
	{
		digitalWrite(_LASER_PE_LINE, LOW);               // Turn off the sensor
		delay(1);                                        // Wait 1ms
		digitalWrite(_LASER_PE_LINE, HIGH);              // Turn on the sensor
		delay(1);                                        // Wait 1ms for it to turn on.
		_pulseWidth = pulseIn(_LASER_MONITOR_PIN, HIGH); // Try again
	}
	return (_pulseWidth / LaserDistanceToCM); // 10usec = 1 cm of distance for LIDAR-Lite
}

//I2CLaser constructor
I2CLaser LaserSupport_h::I2CLaser()
{
	I2c.begin();				// Opens & joins the irc bus as master
	delay(100);					// Waits to make sure everything is powered up before sending or receiving data  
	I2c.timeOut(50);			// Sets a timeout to ensure no locking up of sketch if I2C communication fails
}

unsigned short I2CLaser::getLaserDistance()
{
	// Write 0x04 to register 0x00
	uint8_t nackack = 100;                                                     // Setup variable to hold ACK/NACK resopnses     
	while (nackack != 0)                                                       // Continue polling until sucess message (ACK) is received )
	{ 
		nackack = I2c.write(LIDARLite_ADDRESS, RegisterMeasure, MeasureValue); // Write 0x04 to 0x00
		delay(1);                                                              // Wait 1 ms to prevent overpolling
	}

	byte distanceArray[2];                                                     // array to store distance bytes from read function

	// Read 2byte distance from register 0x8f
	nackack = 100;                                                                 // Setup variable to hold ACK/NACK resopnses     
	while (nackack != 0)                                                           // Continue polling until sucess message (ACK) is received 
	{ 
		nackack = I2c.read(LIDARLite_ADDRESS, RegisterHighLowB, 2, distanceArray); // Read 2 Bytes from LIDAR-Lite Address and store in array
		delay(1);                                                                  // Wait 1 ms to prevent overpolling
	}
	short distance = (distanceArray[0] << 8) + distanceArray[1];                   // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int(short)
	distance = distance * 2.54;
	return distance;
}