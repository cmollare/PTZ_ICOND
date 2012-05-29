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
	  //the 3 coefficients below have to be positive :
	  float kp; //Proportional coefficient : increase precision and speed but decrease stability
	  float ki; //Integral coefficient : increase precision but decrease speed and stability (remove statical error) must be < 1 !
	  float kd; //Derivative coefficient : decrease precision but increase stability and speed
	  float oldError; //Previous error
	  float integralError;
};

#endif
