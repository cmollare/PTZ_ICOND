#ifndef SKINCOLORMODEL_H
#define SKINCOLORMODEL_H

#include <cv.h>
#include <iostream>
#include <string>
using std::string;

#include "displayutils.h"
#include "ColorBase.h"
#include "cvtcoloralloc.h"
#include "histogrammes.h"

typedef unsigned long int ulint;

/* Classe qui defini le modele de couleur peau */
class SkinColorModel
{
public:

  /* Dimension des histogrammes */
  int dim;

  /* Histogramme contenant le modele de couleur */
  CvHistogram* hist;

  /* Histogramme seuille contenant le modele de couleur */
  CvHistogram* hist_thresh;

  /* base de couleur utilisee (a partir de la liste des bases) */
  ParamsList base;
  
  /* Parametres de la base de couleur utilisee */
  ColorBase cb;

  /* Convertisseur couleur pour la conversion de pixels au cours de l'apprentissage */
  CvtColor* colorconverter;

  /* Flag indiquant si la classe contient un modele de couleur charge */
  bool modelLoaded;

  /* Flag pour savoir si l'apprentissage peut etre fait */
  bool readyForLearn;

  /* Pour convertir rapidement les valeurs 0 - 255 en indice de bin */
  int binLut[256];

  /*********************************************************************************************/

  /* Constructeur par defaut, il ne charge pas de modele (on l'utilise classiquement avant de charger un modele) */
  SkinColorModel();

  /* Constructeur qui ne fait que definir la base dans laquelle on travaille (on l'utilise avant de faire l'apprentissage) */
  SkinColorModel(string base);

  /* Destructeur */
  ~SkinColorModel();

  /* Methode d'apprentissage du modele de couleur en fonction d'un fichier contenant les occurences en RGB de
     la couleur peau et non peau */
  int learn(string skin_filename,string nonskin_filename);

  /* Apprentissage d'une distribution couleur a partir d'un fichier contenant un apprentissage */
  int learn_distribution(string skin_filename, double* hist);

  /* Enregistrement du modele de couleur dans un fichier */
  int save(string model_filename);

  /* Chargement d'un modele de couleur a partir d'un fichier */
  int load(string model_filename);

  /* Fonction de seuillage du modele de couleur */
  inline int threshold(double seuil) 
  { cvCopyHist(this->hist,&this->hist_thresh); cvThreshHist(this->hist_thresh,seuil); return 1;};

  /* Allocation des histogrammes en fonction de la base utilisee */
  int alloc_histos();
};
#endif
