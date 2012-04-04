#include "CorrectorPID.h"

CorrectorPID::CorrectorPID(float kp, float ki, float kd)
{
	this->kp=kp;
	this->ki=ki;
	this->kd=kd;
	this->oldError=0;
	this->integralError=0;
}

float CorrectorPID::computeCorrection(float error)
{
	float correction,derivee;
	derivee=this->oldError-error;
	this->integralError+=error;
	correction=this->kp*error+this->ki*this->integralError+this->kd*derivee;
	oldError=error;
	return correction;
}
