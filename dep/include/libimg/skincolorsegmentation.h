#ifndef SKINCOLORSEGMENTATION_H
#define SKINCOLORSEGMENTATION_H

#include <cv.h>
#include <iostream>
#include <string>
using std::string;
using namespace std;

#include "skincolormodel.h"
#include "cvtcoloralloc.h"

/* Classe qui permet de segmenter la couleur peau */
class SkinColorSegmentation
{
public :

  /* Dimensions des images */
  int width;
  int height;

  /* Convertisseur couleur */
  CvtColor* colorconverter;

  /* Modele de couleur peau */
  SkinColorModel cm;

  /* Image de probabilite */
  IplImage* imgProba;

  /* Images pour la separation en plans */
  IplImage* imgP1;
  IplImage* imgP2;
  IplImage* imgP3;

  /* Liste d'images pour la projection dans l'histogramme */
  IplImage** images;

  /* Image pour le changement de base */
  IplImage* imgConverted;

  /* Constructeur de la segmentation */
  SkinColorSegmentation(string base="RGB", int w=img_width, int h=img_height);

  /* Destructeur */
  ~SkinColorSegmentation();
  
  /* Methode de calcul de la carte de probabilite avec conversion couleur ou non */
  IplImage* process(IplImage* imgIn);
  IplImage* process(IplImage* imgIn, int cvtcolor);

  IplImage* processThresh(IplImage* imgIn);
  IplImage* processThresh(IplImage* imgIn, int cvtcolor);

  /* Definition d'un seuil pour la segmentation */
  inline void setThreshold(double seuil) { this->cm.threshold(seuil); };
};
#endif
