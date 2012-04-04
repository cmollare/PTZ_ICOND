#ifndef SHAPEMODELS_H
#define SHAPEMODELS_H



#include <cv.h>
#include <highgui.h>
#include <iostream>
using namespace std;
#include <stdio.h>

#include "shape.h"
#include "multibspline2d.h"

/**
   Auteur : Ludovic Brèthes

   Description : Cette classe contient une liste de splines correspondant aux 
   modèles utilises dans le tracking et intègre toutes les methodes de 
   chargements et d'utilisation des modèles
*/
class ShapeModels
{

 private: 
  
  /* Nombre de modeles charges */
  int nbmodels;

  /* Nom du fichier contenant la spline */
  char splinefic[100];

  /* Nom du fichier contenant la configuration de la spline */
  char splineconfig[50];

  /* Extention du nom de fichier modele */
  char splineext[5];

  /* Couleur par defaut */
  CvScalar couleur;

 public:
  
  /* Attributs pour la description de la forme */
  GlobalShapeDesc *glsd;
  CvPoint * liste;


  /* Liste de modeles de splines */
  //BSpline2D ** models;

  MultiBSpline2D *models;

  /* Constructeurs */
  ShapeModels(const char *splinefic, const char *splineconfig, const char *splineext);

  /* Destructeur */
  ~ShapeModels();

  /* Methode qui permet de recuperer un modele dans la liste */
  MultiBSpline2D *GetShapeModels();

  /* Methode qui permet de charger un modele */
  //int LoadOneModel(int num);

  /* Methode qui permet de chager un ensemble de modeles */
  //int LoadModelList(int nb, int *list);

  /* Methode de visualisation d'un modele charge */
  void ViewModel(int num=-1, char *nomfen="Model");
  /* version noir sur fond blanc avec sauvegarde sur fichier */
  void ViewModel2(int num=-1, char *nomfen="Model");

  /* Methode de trace d'un modele dans une image */
  void DrawModel(IplImage *img,int num, double x, double y, double theta, double scale, CvScalar coul=CV_RGB(255,0,0));

};
#endif
