#ifndef DETECTOR_H
#define DETECTOR_H

#include <cv.h>
#include <highgui.h>
#include <iostream.h>
#include <map.h>
#include <vector.h>
#include <string.h>
using namespace std;

#include "displayutils.h"
#include "stringutils.h"
#include "ImgProducer.h"

/* Classe contenant toutes les images et les fonctions pour le traitement */
class Detector
{
public:

  /* Vecteur de melange de gaussiennes (GM) */
  vector<GaussianMixture*> gmList;

  /* Vecteur de noms associes aux GM */
  vector<string> gmNM;

  /* Vecteur de flag */
  int* gmOK;
  int size;

  /* Definition d'une map pour associer le nom d'une GM a son nom */
  map<const char *, int, less<const char *> > gmID;

  /* Constructeur */
  Detector(ImgProducer* imgBank=0);

  /* Destructeur */
  ~Detector();

  /* Ajout d'une GM et allocation de celle ci */
  int gmRegister(const char* nm, double dx, double dy, double* cov);

  /* Recuperation du pointeur vers la GM */
  inline GaussianMixture* gmGetPtr(const char* nm)
  { return gm[gmID[nm]]; };

  /* methode d'affichage des GM */
  void disp();

  /* Initialise le detecteur avec une nouvelle image */
  inline void set(IplImage* imgIn)
  {
#warning Attention ici on initialise le ImgProducer par l intermediaire du detecteur

    /* Init du producer */
    imgBank->set(imgIn);    

    /* Mise a zero du vecteur flag */
    memset(gmOK,0,size);
  }

  /* Methode d'allocation de tous les parametres des differents detecteurs */
  void alloc();

  /* Methode de traitement appelant tous les detecteurs et generant toutes les GM */
  void process(IplImage* imgIn);


  /*************************/
  /* METHODES DE DETECTION */
  /*************************/
  
  /*******************************************/
  /* Detection de visage                     */
  /*******************************************/
  int idFACE;
  
  inline GaussianMixture* gmFACE()
  {
    if(!gmOK[idFACE]) calcFACE();
    return gm[idFACE];    
  }         

  void allocFACE();
  void calcFACE();                                  

REVOIR ICI COMMENT ADAPTER POUR NE FAIRE QU'UNE DETECTION
MEME SI PLUSIEURS GM SONT GENEREES PAR LA MEME DETECTION

};
#endif
