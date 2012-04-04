#ifndef GLOBALSHAPEDESCRIPTION_H
#define GLOBALSHAPEDESCRIPTION_H

#include <cv.h>
#include <highgui.h>
#include <stdio.h>

#include "shapeutils.h"

/*
  Fonctions de representation de la forme par des courbes de rayon 
  et d'angle entre un point et tous les autres points de la forme 
*/
class GlobalShapeDesc
{
 public:
  
  /* Nombre de points decrivant la forme */
  int nbpts;

  /* indice du point courant */
  int ptfin;
  
  /* Liste des coordonnees des points correspondant a la forme de base */
  CvPoint *ptlist;

  CvPoint center;

  /* Indice du point de reference */
  int refid;

  /* Liste des rayons de ref*/
  double *rayons_reference;

  /* rayons candidats */
  double *rayons;

  /* Liste des angles de ref */
  double *angles_reference;

  /* angles candidats */
  double *angles;

  /* Constructeur */
  GlobalShapeDesc(int nb);
  ~GlobalShapeDesc();

  /* Affichage de la representation de la forme */
  void DispRayons();
  void DispAngles();
  void DispShapeDescRef();
  void DispShapeDesc();

  /* Calcul de la forme de ref a partir d'une liste de points */
  void CalcGlobalShapeDescRef(CvPoint *center, CvPoint *pts);
  void CalcGlobalShapeDescRef(CvPoint *pts); 

  /* Calcul de la forme de ref a partir des points deja connus */
  void CalcGlobalShapeDescRef();
  /* Calcul de la forme candidate a partir d'une liste de points */
  void CalcGlobalShapeDesc(CvPoint *pts); 
  void CalcGlobalShapeDesc(CvPoint *pts,int *mask);
  void CalcGlobalShapeDesc(CvPoint *center,CvPoint *pts,int *mask);

  /* Comparaison de la forme avec une forme candidate */
  double GlobalShapeDescCompar(int *mask, int nbpts); 
  double GlobalShapeDescCompar2(int *mask);
  double GlobalShapeDescCompar(CvPoint *ptsref,CvPoint *ptscomp);

  /* Ajout d'un point a la liste de points */
  void Add(CvPoint *ptnew);
};
#endif
