#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H

#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "ImgProducer.h"
#include "twoDDetector.h"
#include "externParams.h"
#include "constparams.h"

class faceDetector : public twoDDetector
{
public:

  /*! \param CvHaarClassifierCascade* cascade
   *  \brief this is the haar classifier cascade used to detect faces
   */
  CvHaarClassifierCascade* cascade;
  
  /*! \param IplImage *imgMEDIUM
   *  \brief this image is a PyrDownsampled image to make the process faster
   */
  IplImage* imgIN; 
  
  /*! \param CvMemStorage* storage
   *  \brief this is the memory storage used by the classifier to store a sequence of
   *  detected faces
   */
  CvMemStorage* storage;

  /*! \param CvSeq* faces
   *  \brief this is a sequence where detected faces are stored
   */
  CvSeq* faces;

  /*! \param int scaleFactor
   *  \brief this is the scale factor (1 when the full image is used or 2 when PyrDown sampled image is used)
   */ 
  int scaleFactor;  

  /*! \param int PyrDown
   *  \brief flag to select between full image or PyrDown sampled image
   */ 
  int PyrDown;

  int detectionsAJeter[256];
  int detectionsAJeterSize;

  /* Constructeur
     w : largeur des images d'entree
     h : hauteur des images d'entree
     imgB : producteur d'images (traitements)
     cov : matrice de covariance des elements du melange de gaussiennes
     downsample : si 1 alors on realise un filtrage Gaussien de l'image
              sinon on utilise l'image telle quelle
  */
  faceDetector(int w, int h, ImgProducer* imgB, double* cov, int downsample=1); 
  faceDetector(string file, ImgProducer* imgB=NULL);

  /* Fonction d'init permet de faire l'alloc */
  void init(double* cov);

  /* Destructeur */
  ~faceDetector();

  /* Fonction de detection */
  GaussianMixture* process(int offsetX=0, int offsetY=0, double scale=1);

  /**********************************************************************/
  /*     Fonctions relatives a la detection de visages seule            */
  /**********************************************************************/

  /*! \fn  void newFD(void)
   *  \brief Haar classifier cascade allocation and loading of the cascade from a xml file
   */
  void newFD(void);

  /** Fonction de filtrage des detections superposees */
  void cleanSuperposedFaces(int coeff=3);

};
#endif
