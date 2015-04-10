/* 
motorMovement.h - library for controlling pairs of motors using digitalWrite
Created by Jay Lewis William Demeijer Hansen, March 29, 2015.

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


#ifndef MotorMovement_h
#define MotorMovement_h

#include <Arduino.h>;

class MotorPair
{
public:
	MotorPair(unsigned char pinLeft, unsigned char pinRight, unsigned char pinReverse);
	void stop();
	void turnLeft(unsigned char rightPower);
	void turnRight(unsigned char leftPower);
	void driveForward(unsigned char power);
	void driveBackward(unsigned char power);
private:
	unsigned char _pinLeft, _pinRight, _pinReverse;
};

class AsymmetricMotorPair
{
public:
	AsymmetricMotorPair(unsigned char pinLeft, unsigned char pinRight, unsigned char pinLeftReverse, unsigned char pinRightReverse, unsigned char pinRightPower, unsigned char pinLeftPower);
	void stop();
	void turnLeft(unsigned char rightPower);
	void turnRight(unsigned char leftPower);
	void turnLeftOnPoint(unsigned char leftPower, unsigned char rightPower);
	void turnRightOnPoint(unsigned char leftPower, unsigned char rightPower);
	void driveForward(unsigned char leftPower, unsigned char rightPower);
	void driveBackward(unsigned char leftPower, unsigned char rightPower);
private:
	unsigned char _pinLeft, _pinRight, _pinLeftReverse, _pinRightReverse, _pinRightPower, _pinLeftPower;
};

typedef enum command {
	DRIVEFORWARDS,
	DRIVEBACKWARDS,
	TURNLEFT,
	ROTATELEFT,
	TURNRIGHT,
	ROTATERIGHT,
	STOP
};
#endif // !motorMovement
