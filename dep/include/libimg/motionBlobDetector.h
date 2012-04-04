#ifndef MOTIONBLOBDETECTOR_H
#define MOTIONBLOBDETECTOR_H


#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "imageutils.h"
#include "twoDDetector.h"
#include "externParams.h"
#include "constparams.h"

/* Classe qui permet d'extraire des blobs a partir d'une image en niveaux de gris
   par exemple une image de prob couleur peau --> detection de blobs couleur peau
*/
class motionBlobDetector : public twoDDetector
{
public:

  /*! \param IplImage *img_reduced 
   *  \brief this is the subsampled image
   */
  IplImage *img_reduced;
  IplImage *img_reduced_prec;
  
  /*! \param IplImage *img_mask_haut
   *  \brief this is a mask of the values greater than a threshold
   *  This image is used to achieve a hysteresis threshold
   */
  IplImage *img_mask_haut;  

  /*! \param IplImage *img_mask_bas
   *  \brief this is a mask of the values lower than a threshold
   *  This image is used to achieve a hysteresis threshold
   */
  IplImage *img_mask_bas;

  /*! \param IplImage *img_tmp
   *  \brief this is a temporary image that is used 
   *  during the blob selection
   */
  IplImage *img_tmp;
  
  /*! \param IplImage *img_tmp2
   *  \brief this is a temporary image that is used 
   *  during the blob selection
   */
  IplImage  *img_tmp2;

  /*! \param IplImage *img_regions
   *  \brief this is the resulting region detection image
   */
  IplImage *img_regions;

  /*! \param int SeuilProbaHaut
   *  \brief this is the upper threshold for the hysteresis selection of the regions
   */
  int SeuilProbaHaut;

  /*! \param int SeuilProbaBas
   *  \brief this is the lower threshold for the hysteresis selection of the regions
   */
  int  SeuilProbaBas;

  /*! \param int SeuilProba
   *  \brief this is the threshold for histogram segmentation
   */
  int  SeuilProba;

  /*! \param CvMemStorage *storage
   *  \brief this is the memory storage where detected contours are stored
   */
  CvMemStorage *storage;

  /*! \param CvSeq *contour
   *  \brief this is the sequence containing the detected contours
   *  corresponding to the detected regions 
   */
  CvSeq *contour;

 /*! \param int factor
   *  \brief this is the scale factor used to downsample the input image
   *  (typically about 10)
   */
  int factor;
  double ffactor;
  CvSize imgSZ;

  IplImage* img_proba;

  /* Constructeur
     w : largeur des images d'entree
     h : hauteur des images d'entree
     imgB : producteur d'images (traitements)
     cov : matrice de covariance des elements du melange de gaussiennes
     scale : echelle du resize pour la detection
  */
  motionBlobDetector(string file, ImgProducer* imgB=NULL);
  motionBlobDetector(int w, int h, ImgProducer* imgB, double* cov, int fact=10,int th=100,int thB=160,int thH=190); 

  /* Fonction d'init permet de faire l'alloc */
  void init(double* cov);

  /* Destructeur */
  ~motionBlobDetector();

  /* Fonction de detection */
  GaussianMixture* process(int offsetX=0, int offsetY=0, double scale=1);
};
#endif
