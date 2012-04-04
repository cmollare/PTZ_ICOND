#ifndef TARGETICU_H
#define TARGETICU_H

#include <string.h>

#include "Target.h"
#include "externParams.h"
#include "displayutils.h"

/* Inclusions pour mesure de forme */
#include "ShapeModels.h"
#include "multibspline2d.h"
#include "likelihoodutils.h"


/* Inclusions pour mesure distrib couleur */
#include "RoiManager.h"
#include "ColorDistribution.h"
#include "MotionDistribution.h"

#include "paramsrange.h"

class TargetICU:public Target
{
 public :

  /*********/
  /* FORME */
  /*********/

  /* Flag d'utilisation de l'attribut forme */
  bool shapeCue;

  /* Flag d'utilisation d'un masque sur le mouvement */
  bool useflowmask;

  /* Classe contenant la definition des modeles de forme */
  ShapeModels *ShM;

  /* Pointeur sur la spline correspondant a la forme */
  MultiBSpline2D* spline;


  /*******************/
  /* DISTRIB COULEUR */
  /*******************/

  /* Flag d'utilisation de l'attribut couleur */
  bool colorCue;

  /* MultiPatch (forme de la cible) */
  RoiManager* colorPatch;
  
  /* Histogrammes de reference */
  ColorDistribution* coldistref;
  
  /* Histogrammes de test */
  ColorDistribution* coldist;
  
  /* Liste des coefficients de mise a jour de l'histogramme de reference */
  double* coefflist;


  /*****************/
  /*  DISTRIB MVT  */
  /*****************/

  /* Flag d'utilisation de l'attribut mvt */
  bool motionCue;  

  /* MultiPatch (forme de la cible) */
  RoiManager* motionPatch;
  
  /* Histogramme pour le calcul de la distrib mvt */
  MotionDistribution* md;

  /* Liens vers les images de mesure */
  IplImage *imgRGB;
  IplImage *imgEDGE;
  IplImage *imgFLOWMASK;

  /* Constructeur */
  TargetICU(string nomfic, ImgProducer* imgBank=NULL, twoDDetector* detector=NULL, Prior* prior=NULL, 
	      ContDynamicModel* ContDynamic=NULL, DiscDynamicModel** DiscDynamic=NULL);
  ~TargetICU();

  /* Fonction de chargement des parametres de la cible (avec allocation des objets) */
  int Load(string nomfic);

  /* Fonction d'affichage de la cible */
  void Disp();

  /* Fonction de trace de la cible avec en parametre la particule et une image pour tracer */
  void Trace(Sample* spl, IplImage* param, CvScalar couleur,int ep=2);
  void Trace(Sample* spl);
  
  /* Cette fonction connecte les images utilisees pour les traitements */
  virtual void LinkImages();

  /* Fonction pour le calcul de la vraissemblance */
  double CalcLikelihood(Sample* spl);

  /* Fonction d'update du modele de la cible (utile pour les cibles qui ont un modele a mettre a jour comme
     par exemple un modele de couleur */
  void UpdateModel(Sample* spl);

  /* Fonction d'initialisation du modele de la cible */
  inline void InitModelFromPrior(){ InitModelFromPrior(priormean); };
  void InitModelFromPrior(double* mean);
  void InitModelFromDetection();
};
#endif
