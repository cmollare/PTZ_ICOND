#ifndef COLORMODEL_H
#define COLORMODEL_H

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
using std::string;
using namespace std;

#include "ColorBase.h"
#include "matrixutils.h"
#include "histogrammes.h"

/*! \class ColorModel
 *  \brief this is a class that manage color model
 */
class ColorModel
{
public:

  /* Base de couleur consideree contenant le nom et les parametres */
  ColorBase cb;

  /***************** Statistiques du modele de couleur ********************/
  

  /* moyenne de couleur sur chaque plan */
  int mC1;
  int mC2;
  int mC3;

  int* mLum;
  int* mChrom1;
  int* mChrom2;

  /* Ecart type sur chaque plan */
  float sigC1;
  float sigC2;
  float sigC3;

  float* sigLum;
  float* sigChrom1;
  float* sigChrom2;

  /* min et max sur chaque plan */
  int minC1, maxC1;
  int minC2, maxC2;
  int minC3, maxC3;

  int* minLum,* maxLum;
  int* minChrom1,* maxChrom1;
  int* minChrom2,* maxChrom2;

  /* validite de la base de couleur pour l'apprentissage */
  int valid;

  /* Covariance sur les plans chromatiques */
  CvMat* cov;

  /* histogramme de chrominence de l'objet */
  CvHistogram* hobj;

  /* histogramme total (de l'apprentissage) */
  CvHistogram* htotal;
  
  /* rapport d'histogramme */
  CvHistogram* histo;

  ColorModel(int base=0);
  ColorModel(string nomfic);
  ~ColorModel();

  int AllocHistos();

  int load(string nomfic);
  int save(string nomfic);
  int loadBasic(string nomfic);
  int saveBasic(string nomfic);
  void raz();


  inline int getmLum() { return *mLum; };
  inline int getmChrom1() { return *mChrom1; };
  inline int getmChrom2() { return *mChrom2; };
  inline float getsigLum() { return *sigLum; };
  inline float getsigChrom1() { return *sigChrom1; };
  inline float getsigChrom2() { return *sigChrom2; };
  inline int getminLum() { return *minLum; };
  inline int getmaxLum() { return *maxLum; };
  inline int getminChrom1() { return *minChrom1; };
  inline int getmaxChrom1() { return *maxChrom1; };
  inline int getminChrom2() { return *minChrom2; };
  inline int getmaxChrom2() { return *maxChrom2; };


  void disp();

};



#endif
