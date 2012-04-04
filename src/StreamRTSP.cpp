#include "StreamRTSP.h"

StreamRTSP::StreamRTSP(string pathRTSP, int fps)
{
	ostringstream oss;
	oss << pathRTSP;
	if (fps != -1)
	{
	  oss << "?fps=" << fps;
	  this->fps=fps;
	}
	
	cout << "Open the stream (this might take several minutes...)\nWait the frame window" << endl;
	vcap=cvCaptureFromFile(oss.str().c_str());

	if(vcap==NULL)
	{
        	cout << "Error opening video stream or file" << endl;
    	}

	currentFrame = this->grabFrame();
}

StreamRTSP::~StreamRTSP()
{
	cvReleaseCapture(&vcap);
}

IplImage *StreamRTSP::grabFrame()
{

	currentFrame=cvQueryFrame(vcap);
	if (!currentFrame)
	{
	  cout << "StreamRTSP : grab frame error" << endl;
	}
	return currentFrame;
}

