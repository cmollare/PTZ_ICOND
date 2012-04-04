#ifndef LIKELIHOODUTILS_H
#define LIKELIHOODUTILS_H

#include <cv.h>
#include <math.h>

#include "multibspline2d.h"
#include "imageutils.h"
#include "externParams.h"


/* Intervient dans le calcul de la vraissemblance avec les contours */
#define SIGMA 24.0
#define MOINS_UN_SUR_DEUX_SIGMA_CARRE -0.00086806
//#define SIGMA 7.0
//#define MOINS_UN_SUR_DEUX_SIGMA_CARRE -0.01020408

/* largeur de recherche des points de contours */
#define SEARCHDISTANCE 5

/* C'est la penalite lorsque le point de contour n'est pas trouve */
#define MAXDISTCARRE 100

/* Penalite max pour un point hors de l'image */
#define MAXRO 100

/*! \fn template<class TW> TW EdgeMesuredst(MultiBSpline2D * spline, IplImage* img_mesure)
 *  \brief this function compute spline likelihood using img_mesure
 *  \param spline is the spline to draw in the image and to use for weight computing
 *  \param img_mesure is the measure image
 */
double CalcEdgeMesuredst(MultiBSpline2D * spline, IplImage* img_mesure, float coeff=MOINS_UN_SUR_DEUX_SIGMA_CARRE, float scale=1);

double CalcEdgeMesuredst(MultiBSpline2D * spline, IplImage* img_mesure, IplImage* img_mask, float ro, float coeff=MOINS_UN_SUR_DEUX_SIGMA_CARRE,float scale=1);


/* Mesure de vraisemblance a partir de l'image de distance eventuellement masquee */
double CalcDistMesuredst(MultiBSpline2D * spline, IplImage* img_mesure, float coeff=MOINS_UN_SUR_DEUX_SIGMA_CARRE, float scale=1);

double CalcDistMesuredst(MultiBSpline2D * spline, IplImage* img_mesure, IplImage* img_mask, float ro, float coeff=MOINS_UN_SUR_DEUX_SIGMA_CARRE, float scale=1);

#endif
