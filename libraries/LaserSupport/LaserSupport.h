/*
LaserSupport.h - Library for support with the ladarlite range sensor
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

#ifndef LaserSupport_h
#define LaserSupport_h

#include <Arduino.h>
#include <I2C.h>

class PWMLaser
{
public:
	PWMLaser(unsigned char LASER_TRIGGER_PIN, unsigned char LASER_MONITOR_PIN, unsigned char LASER_PE_LINE);
	unsigned long getLaserDistance();
	unsigned long getLaserDistanceSafe();
private:
	unsigned char _LASER_TRIGGER_PIN, _LASER_MONITOR_PIN, _LASER_PE_LINE;
	unsigned long _pulseWidth;
};

class I2CLaser
{
public:
	I2CLaser();
	unsigned short getLaserDistance();

};

#endif// !LaserSupport