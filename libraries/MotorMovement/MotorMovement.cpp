/* 
motorMovement.cpp - library for controlling pairs of motors using digitalWrite
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


#include <Arduino.h>
#include <MotorMovement.h>

MotorPair MotorMovement_h::MotorPair(unsigned char pinLeft, unsigned char pinRight, unsigned char pinReverse, unsigned char pinRightPower, unsigned char pinLeftPower)
{
	unsigned char _pinLeft, _pinRight, _pinReverse, _pinRightPower, _pinLeftPower;

	_pinLeft = pinLeft;
	_pinRight = pinRight;
	_pinReverse = pinReverse;
	_pinRightPower = pinRightPower;
	_pinLeftPower = pinLeftPower;

	pinMode(_pinLeft, OUTPUT);
	pinMode(_pinRight, OUTPUT);
	pinMode(_pinReverse, OUTPUT);
	pinMode(_pinRightPower, OUTPUT);
	pinMode(_pinLeftPower, OUTPUT);

}
void MotorPair::stop()
{
	//code to stop the motors
	digitalWrite(_pinLeft , LOW);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinReverse, LOW);

	digitalWrite(_pinRightPower, LOW);
	digitalWrite(_pinLeftPower, LOW);
}

void MotorPair::turnLeft(unsigned char rightPower)
{
	//code to turn left
	digitalWrite(_pinLeft , LOW);
	digitalWrite(_pinRight, HIGH);
	digitalWrite(_pinReverse, LOW);

	digitalWrite(_pinRightPower, rightPower);
	digitalWrite(_pinLeftPower, LOW);
}

void MotorPair::turnRight(unsigned char leftPower)
{
	//code to turn right
	digitalWrite(_pinLeft, HIGH);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinReverse, LOW);

	digitalWrite(_pinRightPower, LOW);
	digitalWrite(_pinLeftPower, leftPower);
}

void MotorPair::driveForward(unsigned char power)
{
	//code to drive forwards
	digitalWrite(_pinLeft , HIGH);
	digitalWrite(_pinRight, HIGH);
	digitalWrite(_pinReverse, LOW);

	digitalWrite(_pinRightPower, power);
	digitalWrite(_pinLeftPower, power);
}

void MotorPair::driveBackward(unsigned char power)
{
	//code to drive backwards
	digitalWrite(_pinLeft, LOW);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinReverse, HIGH);

	digitalWrite(_pinRightPower, power);
	digitalWrite(_pinLeftPower, power);
}

AsymmetricMotorPair MotorMovement_h::AsymmetricMotorPair(unsigned char pinLeft, unsigned char pinRight, unsigned char pinLeftReverse, unsigned char pinRightReverse, unsigned char pinRightPower, unsigned char pinLeftPower)
{
	unsigned char _pinLeft, _pinRight, _pinLeftReverse, _pinRightReverse, _pinRightPower, _pinLeftPower;

	_pinLeft = pinLeft;
	_pinRight = pinRight;
	_pinLeftReverse = pinLeftReverse;
	_pinRightReverse = pinRightReverse;
	_pinRightPower = pinRightPower;
	_pinLeftPower = pinLeftPower;

	pinMode(_pinLeft, OUTPUT);
	pinMode(_pinRight, OUTPUT);
	pinMode(_pinLeftReverse, OUTPUT);
	pinMode(_pinRightReverse, OUTPUT);
	pinMode(_pinRightPower, OUTPUT);
	pinMode(_pinLeftPower, OUTPUT);
}

void AsymmetricMotorPair::stop()
{
	//code to stop all motors
	digitalWrite(_pinLeft, LOW);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinRightReverse, LOW);
	digitalWrite(_pinLeftReverse, LOW);

	digitalWrite(_pinRightPower, LOW);
	digitalWrite(_pinLeftPower, LOW);
}

void AsymmetricMotorPair::turnLeft(unsigned char rightPower)
{
	//power to the right motor will turn left
	digitalWrite(_pinLeft, LOW);
	digitalWrite(_pinRight, HIGH);
	digitalWrite(_pinRightReverse, LOW);
	digitalWrite(_pinLeftReverse, LOW);

	digitalWrite(_pinRightPower, rightPower);
	digitalWrite(_pinLeftPower, LOW);
}

void AsymmetricMotorPair::turnRight(unsigned char leftPower)
{
	//power to the left motor will turn right
	digitalWrite(_pinLeft, HIGH);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinRightReverse, LOW);
	digitalWrite(_pinLeftReverse, LOW);

	digitalWrite(_pinRightPower, LOW);
	digitalWrite(_pinLeftPower, leftPower);
}

void AsymmetricMotorPair::turnLeftOnPoint(unsigned char leftPower, unsigned char rightPower)
{
	//power to reverseLeft and right will make the car turn on a pounsigned char
	digitalWrite(_pinLeft, LOW);
	digitalWrite(_pinRight, HIGH);
	digitalWrite(_pinRightReverse, LOW);
	digitalWrite(_pinLeftReverse, HIGH);

	digitalWrite(_pinRightPower, rightPower);
	digitalWrite(_pinLeftPower, leftPower);
}

void AsymmetricMotorPair::turnRightOnPoint(unsigned char leftPower, unsigned char rightPower)
{
	//power to reverseRight and left will make the car turn on a pounsigned char
	digitalWrite(_pinLeft, HIGH);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinRightReverse, HIGH);
	digitalWrite(_pinLeftReverse, LOW);

	digitalWrite(_pinRightPower, rightPower);
	digitalWrite(_pinLeftPower, leftPower);
}

void AsymmetricMotorPair::driveForward(unsigned char leftPower, unsigned char rightPower)
{
	//code to drive forwards
	digitalWrite(_pinLeft, HIGH);
	digitalWrite(_pinRight, HIGH);
	digitalWrite(_pinRightReverse, LOW);
	digitalWrite(_pinLeftReverse, LOW);

	digitalWrite(_pinRightPower, rightPower);
	digitalWrite(_pinLeftPower, leftPower);
}

void AsymmetricMotorPair::driveBackward(unsigned char leftPower, unsigned char rightPower)
{
	digitalWrite(_pinLeft, LOW);
	digitalWrite(_pinRight, LOW);
	digitalWrite(_pinRightReverse, HIGH);
	digitalWrite(_pinLeftReverse, HIGH);

	digitalWrite(_pinRightPower, rightPower);
	digitalWrite(_pinLeftPower, leftPower);
}