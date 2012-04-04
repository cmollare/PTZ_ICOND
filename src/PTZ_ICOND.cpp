#include <iostream>
using namespace std;

#include "applipath.h"
#include "def_paramslist.h"


#include "Sample.h"
#include "ParticleFilter.h"
#include "ICOND.h"

#include "ControlPTZ.h"
#include "CorrectorPID.h"
#include "StreamRTSP.h"

#include <pthread.h>

typedef struct
{
	StreamRTSP *stream;
	IplImage *imgBuf;
	pthread_mutex_t mutex_stock;
}SStream;

typedef struct
{
	Point_<int> point;
	bool start_tracking;
}SMouseEvent;

static void* pthread_img(void* stream)
{
	SStream *str = (SStream *) stream;
	for(;;)
	{
	  //cout << "pouet" << endl;
	  pthread_mutex_lock(&(str->mutex_stock));
	  str->imgBuf=str->stream->grabFrame();
	  pthread_mutex_unlock(&(str->mutex_stock));
	}
	return NULL;
}

void on_mouse(int event, int x, int y, int flags, void* param)
{
	SMouseEvent *mouseEvent = (SMouseEvent *) param;
	switch(event)
	{
	  case CV_EVENT_LBUTTONDOWN:
	    mouseEvent->point.x = x;
	    mouseEvent->point.y = y;
	    mouseEvent->start_tracking=true;
	    cout << "x : " << mouseEvent->point.x << endl;
	    cout << "y : " << mouseEvent->point.y << endl;
	    break;

	  default :
	    break;
	}
	
}

int main()
{
	ControlPTZ ctrlPTZ;
	CorrectorPID PIDpan(0.03,0,0), PIDtilt(0.03,0,0), PIDzoom(4,0,0);
	float errPan=0, errTilt=0, errZoom=0;
	IplImage *imgIn, *imgBuf, *imgRes;
	SStream stream;
	stream.stream = new StreamRTSP("rtsp://opera:clm2pO@axis-ptz2/axis-media/media.amp");

	SMouseEvent mouseEvent;
	mouseEvent.start_tracking=false;
	
	//Open the thread for RTSP streaming
	pthread_t thread_img;
	pthread_create(&thread_img, NULL, pthread_img, &stream);
	

	ParticleFilter* pf = new ICONDFilter("../data/filters/body_tracking_icond.txt");

	pthread_mutex_lock(&stream.mutex_stock);
	while(stream.imgBuf==NULL){}
	imgBuf=stream.imgBuf;
	pthread_mutex_unlock(&stream.mutex_stock);

	imgIn = cvCreateImage(cvSize(320, 240),  IPL_DEPTH_8U, 3);
  	cvResize(imgBuf, imgIn, CV_INTER_LINEAR);

	pf->target->imgBank->set(imgIn);
  	pf->InitSamplesFromPrior();
  	cout<< " imgBank set and samples initialized\n"<<endl; 
  
  	pf->DispSamples();
	
	///END INITIALISATION///

	cvNamedWindow("img",0);
  	cvMoveWindow("img",0,0);
	//Open the Mouse callblack
	cvSetMouseCallback("img", on_mouse, &mouseEvent);
  	cvNamedWindow("RES",0);
  	cvMoveWindow("RES",350,0);
	cvShowImage("img", imgIn);
	
	cvWaitKey(0);

	Sample sps(3,0);
  	double mm[3]={mouseEvent.point.x,mouseEvent.point.y,2.2};

  	sps.ContinusP[0] = mm[0];
  	sps.ContinusP[1] = mm[1];
 	sps.ContinusP[2] = mm[2];
	
	cvResize(imgBuf, imgIn, CV_INTER_LINEAR);
	imgRes = cvCloneImage(imgIn);

  	pf->target->imgBank->set(imgIn);
  	pf->InitSamplesFromPrior(mm);

  	pf->target->Trace(&sps,imgIn);
	cvShowImage("img",imgIn);
	cvShowImage("RES",imgRes);
	//cvWaitKey(0);

	for(;;)
	{
	  pthread_mutex_lock(&stream.mutex_stock);
	  imgBuf=stream.imgBuf;
	  pthread_mutex_unlock(&stream.mutex_stock);
	  cvResize(imgBuf, imgIn, CV_INTER_LINEAR);
	  cvCopyImage(imgIn,imgRes);
      	  cvShowImage("img",imgIn);

	      /* On place l'image a traiter */
      	  pf->target->imgBank->set(imgIn);

      	  /* Execution de la detection */
      	  pf->target->detector->process();
      	  cout << "Found " << pf->target->detector->nbdetected << " faces\n";

      	  /* Filtrage */
      	  pf->step();

      	  /* Resultat */
      
      	  pf->target->Trace(pf->pfState,imgRes);
	  errPan=-(float)imgIn->width/2+pf->pfState->ContinusP[pf->target->posXk];
	  errTilt=(float)imgIn->height/2-pf->pfState->ContinusP[pf->target->posYk];
	  ctrlPTZ.HTTPRequestPTZPosRelative(PIDpan.computeCorrection(errPan), PIDtilt.computeCorrection(errTilt),0);
	  //cout << "posX : " << pf->pfState->ContinusP[pf->target->posXk] << endl;
	  //cout << "posY : " << pf->pfState->ContinusP[pf->target->posYk] << endl;
      
      	  for(int j=0; j< pf->nbSamples ; j++)
      	  {
		int x = (int)pf->sps[j]->ContinusP[0];
		int y = (int)pf->sps[j]->ContinusP[1];
      		cvCircle(imgRes, cvPoint(x, y), 2, CV_RGB(255, 255, 0), 1);
      	  }
      	  //pf->TraceAllSamples(imgRes, CV_RGB(255, 255, 0)); 
      	  //pf->PlotPkk(imgRes,CV_RGB(255, 255, 0));
      	  cvShowImage("RES",imgRes);

	  if(cv::waitKey(5) >= 0)
	  {
		pthread_cancel(thread_img);
		pthread_join(thread_img, NULL);
		ctrlPTZ.HTTPRequestPTZPosAbsolute(-31.8904, -20, 550);
		delete stream.stream;
		cv::waitKey(100);
		break;
	  }
	}
}
