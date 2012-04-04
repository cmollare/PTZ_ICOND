#ifndef TARGET_H
#define TARGET_H

#include <string.h>
#include "stringutils.h"
#include "paramsrange.h"
#include "PriorAlloc.h"
#include "ContDynamicAlloc.h"
#include "DiscDynamicAlloc.h"
#include "twoDDetectorAlloc.h"
#include "likelihoodutils.h"
#include "ImgProducer.h"
#include "externParams.h"

class Target
{
 public :

  /* ID de la target */
  int targetID;

  /* taille des images */
  int width;
  int height;

  /* nombre de parametres continus a estimer */
  int nCP;
  
  /* nombre de parametres discrets a estimer */
  int nDP;

  /* Bornes des parametres continus */
  ParamsRange<double> ContPRanges;

  /* Bornes des parametres discrets */
  ParamsRange<int> DiscPRanges;

  /* Dynamique partie continue de la cible */
  ContDynamicModel* ContDynamic;
  bool localContDynamic;

  /* Dynamique partie discrete de la cible */
  DiscDynamicModel** DiscDynamic;
  bool localDiscDynamic;

  /* Prior de la cible */
  Prior* prior;
  bool localPrior;

  /* Detecteur de la cible */
  twoDDetector* detector;
  bool localDetector;

  /* Constructeur de donnees de mesure */
  ImgProducer* imgBank;
  bool localImgBank;

  /* Vecteur de coefficients sigma et un sur deux sigma carre */
  int nbSigma;
  double* sigma;
  double* deux_sigma_carre;
  double* moins_un_sur_deux_sigma_carre;
  
  /* Vecteur de penalites */
  int nbPenality;
  double* ofpenality;

  /* Vecteur contenant la moyenne a priori */
  double* priormean;

  /* Parametre de detection */
  double posDetected[2];

  /* Parametres */
  int posXk;
  int posYk;
  int posTk;
  int posSk;

  bool useTk;

  /* Constructeur a partir des elements contenus dans un fichier et eventuellement d'objets externes */
  Target(string nomfic, ImgProducer* imgBank=NULL, twoDDetector* detector=NULL, Prior* prior=NULL, 
	 ContDynamicModel* ContDynamic=NULL, DiscDynamicModel** DiscDynamic=NULL);
  ~Target();

  /* Fonction de chargement des parametres de la cible (avec allocation des objets) */
  int Load(string nomfic);

  /* Fonction d'affichage des parametres communs de la cible */
  void DispCommon();

  /* Fonction d'affichage de la cible */
  virtual void Disp()=0;

  CvScalar color;
  inline void setColor(CvScalar coul) { this->color = coul; };

  /* Fonction de trace de la cible avec en parametre la particule a tracer */
  inline void Trace(Sample* spl, IplImage* param, int ep=2) { Trace(spl,param,this->color,ep); }; 
  virtual void Trace(Sample* spl, IplImage* param,CvScalar couleur, int ep=2)=0;
  virtual void Trace(Sample* spl)=0;
  
  /* Cette fonction connecte les images utilisees pour les traitements */
  virtual void LinkImages(){ };

  /* Fonction pour le calcul de la vraissemblance */
  virtual double CalcLikelihood(Sample* spl)=0;

  /* Fonction d'update du modele de la cible (utile pour les cibles qui ont un modele a mettre a jour comme
     par exemple un modele de couleur */
  virtual void UpdateModel(Sample* spl)=0;

  /* Fonction d'initialisation du modele de la cible */
  virtual void InitModelFromPrior()=0;
  virtual void InitModelFromPrior(double* mean)=0;
  virtual void InitModelFromDetection()=0;

  /* Fonction qui fait un RAZ de certains parametres */
  inline virtual void RazModel(){};

  /* Fonctions pour modifier les sigma */
  inline void setSigma(int n, double val) 
  { 
    if(n<this->nbSigma) 
      {
	this->sigma[n] = val; 
	this->deux_sigma_carre[n] = 2*pow(this->sigma[n],2);
	this->moins_un_sur_deux_sigma_carre[n] = -1.0/this->deux_sigma_carre[n];
      }
  };
 
  inline double getSigma(int n) { if(n<this->nbSigma) return this->sigma[n]; };

  /* Fonction d'init des sigma pour les mesures des filtres */
  void InitSigma(double* sig); 
  
  /* Fonction d'init des penalites pour les mesures des filtres */
  void InitPenality(double* pen);
  
  /* Acces au vecteur de penalites */
  inline void setPenality(int n, double val) 
  { if(n<this->nbPenality) this->ofpenality[n] = val; };
 
  inline double getPenality(int n) { if(n<this->nbPenality) return this->ofpenality[n]; };
};
#endif
