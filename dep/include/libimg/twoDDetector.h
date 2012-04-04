#ifndef TWODDETECTOR_H
#define TWODDETECTOR_H

#include <iostream>
#include <string>
using namespace std;

#include "GaussianMixture.h"
#include "Gaussian.h"
#include "ImgProducer.h"

class twoDDetector
{
public:

  /* ID du detecteur */
  int detectorID;

  /* Banque d'images */
  ImgProducer* imgBank;

  /* Dim des images */
  int width;
  int height;

  /* Melange de gaussiennes 2D (fonction d'importance) */
  GaussianMixture* gm;

  /* Vecteur de ROI correspondant aux regions detectees */
  vector<CvRect> detectedROI;

  /* Vecteur de centre des regions detectees */
  vector<CvPoint> detectedCENTER;

  /*! \param int nbdetected
   *  \brief this is the number of detected elements
   */
  int nbdetected;

  /* Constructeur */
  twoDDetector(int w, int h, ImgProducer* imgB=NULL);
  twoDDetector(string file, ImgProducer* imgB=NULL);

  /* Destructeur */
  virtual ~twoDDetector();

  /* Fonction de trace du resultat de la detection sur une image */
  void dispROI(IplImage* imgRES, int d=2, CvScalar coul=CV_RGB(0,0,255));        /* Affiche les ROI */
  void dispCENTER(IplImage* imgRES, int d=2, CvScalar coul=CV_RGB(0,0,255));     /* Affiche les Centres */
  inline void disp(IplImage* imgRES, int dROI=2,CvScalar coulROI=CV_RGB(0,0,255), 
		   int dCENTER=2, CvScalar coulCENTER=CV_RGB(0,0,255))                          /* Affiche Tout */
  {
    dispROI(imgRES,dROI,coulROI);
    dispCENTER(imgRES,dCENTER,coulCENTER);
  };

  /* Fonction de detection */
  inline GaussianMixture* process(IplImage* img, int offsetX=0, int offsetY=0, double scale=1)
  {
    /* Production d'images */
    this->imgBank->set(img);

    /* Detection */
    return this->process(offsetX,offsetY,scale);
  }
  virtual GaussianMixture* process(int offsetX=0, int offsetY=0, double scale=1)=0;

  /* Initialisation avec une nouvelle covariance */
  inline void initGM(double* cov)
  { this->gm->Init(NULL,cov); };

};
#endif
