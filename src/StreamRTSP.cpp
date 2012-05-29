#include "StreamRTSP.h"

StreamRTSP::StreamRTSP(string pathRTSP, int fps, bool iplImage)
{
	this->iplImage=iplImage;

	ostringstream oss;
	oss << pathRTSP;
	if (fps != -1)
	{
	  oss << "?fps=" << fps;
	  this->fps=fps;
	}
	
	cout << "Open the stream (this might take several minutes...)\nWait the frame window" << endl;
	
	if (this->iplImage)
	{
	  cvCap=cvCaptureFromFile(oss.str().c_str());

	  if(cvCap==NULL)
	  {
        	cout << "Error opening video stream or file" << endl;
    	  }
	  currentFrame = this->grabIplFrame();
	}
	else
	{
	  vcap.open(oss.str().c_str());
	  matCurrentFrame = this->grabFrame();
	}

	
}

StreamRTSP::StreamRTSP(int device)
{
	vcap.open(device);
	this->iplImage=false;
	matCurrentFrame = this->grabFrame();
}

StreamRTSP::~StreamRTSP()
{
	if (this->iplImage)
	  cvReleaseCapture(&cvCap);
}

IplImage *StreamRTSP::grabIplFrame()
{

	currentFrame=cvQueryFrame(cvCap);
	if (!currentFrame)
	{
	  cout << "StreamRTSP : grab frame error" << endl;
	}
	return currentFrame;
}

Mat StreamRTSP::grabFrame()
{

	if (!vcap.read(matCurrentFrame))
	{
	  cout << "StreamRTSP : grab frame error" << endl;
	}
	return matCurrentFrame;
}

