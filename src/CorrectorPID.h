#ifndef CORRECTORPID_H
#define CORRECTORPID_H

#include <iostream>

using namespace std;

class CorrectorPID
{
	public :
	  CorrectorPID(float kp, float ki=0, float kd=0);
	  float computeCorrection(float error);
	
	private :
	  float kp;
	  float ki;
	  float kd;
	  float oldError;
	  float integralError;
};

#endif
