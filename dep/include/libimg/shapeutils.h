#ifndef SHAPEUTILS_H
#define SHAPEUTILS_H

#include <cv.h>
#include <highgui.h>
#include "constparams.h"
 
#define NORMALIZE



/* Fonctions de calcul du rayon et angles entre un point de ref
   et une liste de points (signature de la forme)
*/
void CalcShape(CvPoint *ptref, CvPoint *pts, double *ray, double *angl, int nbpts);
void CalcShape(CvPoint *ptref, CvPoint *pts, double *ray, double *angl, int nbpts, int *mask);


#endif
