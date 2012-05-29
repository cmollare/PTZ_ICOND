#ifndef CONTROLPTZ_H
#define CONTROLPTZ_H

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>

using namespace std;

class ControlPTZ
{
	public:
		ControlPTZ();
		~ControlPTZ();
		//speed control (zoom still controlled in relative position mode)
		void HTTPRequestPTZ(int pan=0, int tilt=0, int zoom=0);
		//relative position control
		void HTTPRequestPTZPosRelative(float pan=0, float tilt=0, float zoom=0);
		//absolute position control
		void HTTPRequestPTZPosAbsolute(float pan=0, float tilt=0, float zoom=0);

	private :
		CURL *handle;
};

#endif
