#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "MotionDistribution.h"
#include "ImgProducer.h"
#include "twoDDetector.h"
#include "externParams.h"
#include "constparams.h"

class motionDetector : public twoDDetector
{
public:
  
  /* Rectangle utilise pour le calcul de l'image de proba de mouvement */
  int Rwidth;
  int demiRwidth;
  int Rheight;
  int demiRheight;
  int rw,rh;  

  /* Nombre de pixels de marge a prendre */
  int nu;

  /* Pas d'echantillonnage de l'image (resolution en position) */
  int pas, demipas;

  /* Points correspondant a la region */
  CvPoint ptUL, ptLR; 

  /* Distribution du mouvement */
  MotionDistribution* md; 

  /* seuil de detection du mouvement (distance comprise entre 0 et 1) */
  float tau;

  /* Nombre maximum de blobs dans la mixture */
  int nbmaxmotionblobs;

  /*! \param GausianMixture *gm
   *  \brief This is a gaussian mixture resulting of the detection
   */
  GaussianMixture* gm;

  /* Constructeur
     w : largeur des images d'entree
     h : hauteur des images d'entree
     imgB : producteur d'images (traitements)
     cov : matrice de covariance des elements du melange de gaussiennes
     downsample : si 1 alors on realise un filtrage Gaussien de l'image
              sinon on utilise l'image telle quelle
  */
  motionDetector(string file, ImgProducer* imgB=NULL);
  motionDetector(int w, int h, ImgProducer* imgB, double* cov,double tau_, int rw_, int rh_, int nu_, int pas_); 

  /* Fonction d'init permet de faire l'alloc */
  void init(double* cov);

  /* Destructeur */
  ~motionDetector();

  /* Fonction de detection */
  GaussianMixture* process(int offsetX=0, int offsetY=0, double scale=1);

};
#endif
