#ifndef ROIMANAGER_H
#define ROIMANAGER_H

#include <cv.h>
#include <fstream>
#include <string>
using namespace std;

#include "stringutils.h"
#include "matrixutils.h"
#include "imageutils.h"

/* Classe qui gere la construction, transformation et affichage d'un patch rectangle seul */

class RoiManager
{
 public:

  /* Dimensions des images traitees */
  int imgW, imgH;

  /* Nombre de regions (total) */
  int nbp;

  /********** Patch central **************/

  /* Largeur de la zone */
  int w;

  /* hauteur de la zone */
  int h;

  /* Demi largeur */
  int demiw;

  /* Demi hauteur */
  int demih;

  /* Position du centre */
  CvPoint center;

  /********* Description des autres patchs en relatif par rapport au patch central (coin UL) *********/

  /* Nombre de patchs supplementaires */
  int nbpsup;

  /* Liste des offsets selon x */
  int* offsetX;

  /* Liste des offsets selon y */
  int* offsetY;

  /* Liste des largeurs */
  int* wlist;

  /* Liste de hauteurs */
  int* hlist;

  /********* Suite *********/

  /* Echelle */
  float scale;

  /* Nombre total de pixels */
  int* nbpix;

  /* Coins des rectangles */
  CvPoint* ptULlist;
  CvPoint* ptLRlist;

  RoiManager(int w, int h, string nomfic);
  ~RoiManager();

  /* Methode qui charge les parametres */
  int Load(string nomfic);

  /* Methode qui positionne le rectangle a une position avec une echelle donnee */
  int* transform(int x, int y, float s=1.0);

  /* Methode qui positionne le rectangle selon les parametres de l'objet */
  int* transform();

  /* Methode qui trace le rectangle sur une image */
  inline void draw(IplImage* img, CvScalar color=CV_RGB(255,0,0), int ep=2)
  { 
    //cvCircle(img,this->center,2,color,-1);
    for(int i=0;i<this->nbp;i++)
      cvRectangle(img,this->ptULlist[i], this->ptLRlist[i],color,ep);     
  };

  /* Methode qui trace le rectangle sur une image */
  inline void draw(int num, IplImage* img, CvScalar color=CV_RGB(255,0,0), int ep=2)
  { cvRectangle(img,this->ptULlist[num], this->ptLRlist[num],color,ep); };

  /* Methode qui retourne une pointeur sur le coin UL */
  inline CvPoint* getUL() { return this->ptULlist; };

  /* Methode qui retourne une pointeur sur le coin LR */
  inline CvPoint* getLR() { return this->ptLRlist; };

  /* Methode qui retourne la taille en pixels des zones couvertes */
  inline int* getnbPix() { return this->nbpix; };
};
#endif
