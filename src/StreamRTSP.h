#ifndef STREAMRTSP_H
#define STREAMRTSP_H

#include <opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace cv;

class StreamRTSP
{
	public :
	  StreamRTSP(string pathRTSP, int fps=-1);
	  ~StreamRTSP();
	  IplImage *grabFrame();

	private :
	  CvCapture *vcap;
	  IplImage *currentFrame;
	  int fps;
};

#endif
