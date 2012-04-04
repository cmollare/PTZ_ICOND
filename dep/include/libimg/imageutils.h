#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <cv.h>
#include <highgui.h>
#include <string>
#include <iostream>
using namespace std;
#include "point2d.h"
#include "imageutils.h" 


/* Export d'une image 1 plan vers matlab */
void exportImg2Matlab(string fname, IplImage* imgProba);

/** Seuillage d'une image **/
void Seuille(IplImage *img,IplImage *seuillee,int seuil);

/**
   Reechantillonnage d'une image avec un facteur factor
*/
int DownSample(IplImage *src, IplImage *dst, int factor);

/**
   Attention cette fonction ne fonctionne que pour une image sur 3 plans 
   elle effectue une moyenne dans un carre 2x2 sur les 3 plans
*/
void ImgPPPAverage2x2(IplImage * src, IplImage * dst);

/**
   Attention cette fonction ne fonctionne que pour une image sur 1 plan
   elle effectue une moyenne dans un carre 2x2
*/
void ImgPAverage2x2(IplImage * src, IplImage * dst);

/*
  Detecte les objets dans une image et extrait un contour par objet 
*/
void Contours(IplImage *img);

/**  Cohen-Sutherland algorithm for line segment clipping
     implementation 
     
     Given the image dimensions and the end points of a line segment,
     this method clips the line segment by adjusting the endpoints to
     the part of the segment that will be inside the image. In the
     case that the segment will have no points inside the image it
     will return false
*/
bool ClipLine(int right,int bottom,CvPoint *pt1,CvPoint * pt2);

/* Clipping de la ligne dans une region delimitee par minx,miny,bottom, et right */
bool ClipLine(int minx, int miny, int right,int bottom,CvPoint *pt1,CvPoint * pt2);

/* Fonction qui verifie la validite de parametres (position dans image)
   si le point est en dehors de l'image on modifie ses coordonnes pour le 
   mettre au bord de l'image
*/
void ClipPoint(CvPoint *pt,IplImage *img);
void ClipPoint(CvPoint *pt,int width, int height);
void ClipPoint(Point2D & pt,IplImage *img);
void ClipPoint(Point2D & pt,int width, int height);

/** Fonction qui calcule des points sur la normale a un segment passant par deux points */
int SegNormale(CvPoint pt1, CvPoint pt2, int taille, CvPoint *res);

/** Fonction qui calcule des points sur la normale a un segment passant par deux points */
int SegNormale2(CvPoint pt1, CvPoint pt2, int taille, CvPoint *res);


/** Calcul du gradient couleur **/
/*
  avec approche vectorielle Di Zenzo

  d² = p.cos²A + q.sin²A + 2t.sinA.cosA
  avec
  p = DRx² + DGx² + DBx²
  q = DRy² + DGy² + DBy²
  t = DRx.DRy + DGx.DGy + DBx.DBy
  
  d² maximale pour :
     A = 1/2.arctg(2t/(p-q))                                     {direction du gradient}
     |Gcoul|² = 1/2.[p + q + sqrt( (p+q)² - 4(pq-t²) )]             {module du gradient}
*/
void GradientCouleur(IplImage *img1,IplImage *img2,IplImage *img3, IplImage *edge);

// A = 1/2.arctg(2t/(p-q))
void GradientCouleurComplet(IplImage *img1,IplImage *img2,IplImage *img3, IplImage *edge, IplImage *dir);

/**
   Dilate the image
**/
void IplImageDilate(IplImage *img,int iter);

/**
   Erode the image
**/
void IplImageErode(IplImage *img,int iter);

/** Gradient Morphologique **/
/*
  G = Dil(img) - Ero(img)
*/
void MorphoGrad(IplImage *imgin,IplImage *imgout);




#endif
