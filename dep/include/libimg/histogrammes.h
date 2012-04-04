#ifndef HISTOGRAMMES_H
#define HISTOGRAMMES_H

#include <cv.h>
#include <highgui.h>
#include "calclut.h"
#include "constparams.h"

void Hist2DCalcRapport(CvHistogram *hist_peau, CvHistogram *hist_total, CvHistogram *histo);

void Hist2DDisplay(CvHistogram *histo,const char *fen,int scale=1);
void Hist2DDisplayZoom(CvHistogram *histo,const char *fen,int scale=1,int coul=GRIS,int autozoom=ON);

void Hist1DDisplay(CvHistogram *histo,char *fen,int scale=1,CvScalar couleur=CV_RGB(255,255,255));
void Hist1DDisplayBarre(CvHistogram *histo,char *fen,int scale=1,CvScalar couleur=CV_RGB(255,255,255));
IplImage * Hist1D2IplImage(CvHistogram *histo,double scale=1,CvScalar couleur=CV_RGB(255,255,255));

//Dynamise l'histogramme en etirant ses valeurs entre 0 et 255 
void Hist2DDyn2(CvHistogram *histo,float ech=255);

void Hist2DDyn(CvHistogram *histo,int ech=255);
void Hist1DDyn(CvHistogram *histo,int ech=255);

/** Determine les positions min et max de l'histogramme **/
void Hist2DPosMinMaxBin(CvHistogram *histo,int *xmin,int *ymin,int *xmax,int *ymax);

/** Fonction qui rempli une matrice correspondant aux valeurs de l'histogramme **/
void Hist2DGetBins(CvHistogram *histo,CvMat **out);
/** Fonction qui rempli l'histogramme avec les valeurs d'une matrice **/
void Hist2DSetBins(CvMat *mat, CvHistogram *out);

/** Fonction de Dilatation d'un Histogramme 2D **/
void Hist2DDilate(CvHistogram *histo,int taille_se);
/** Fonction d'Erosion d'un Histogramme 2D **/
void Hist2DErode(CvHistogram *histo,int taille_se);
/* Fonction qui fait une ouverture de taille nb*/
void Hist2DClose(CvHistogram *histo,int taille_se=3, int nb=1);
/* Fonction qui fait une ouverture de taille nb*/
void Hist2DOpen(CvHistogram *histo,int taille_se=3, int nb=1);

/** Dilatation de l'histogramme 1D **/
void Hist1DDilate(CvHistogram *hist,int taille_es);

/** Calcul de l'histogramme a partir de deux vecteurs **/
void CalcHistoObj(CvMat *mat1,CvMat *mat2,double taille, CvHistogram *histo, int dyn);

void CalcMatHisto(CvMat *mat1,CvMat *mat2,double taille, CvHistogram *histo, int dyn);

void CalcHistoPlanes(IplImage **planes,CvHistogram **out);

/** Convertit un histogramme en une image **/
void Histo2Img(CvHistogram *histo,IplImage **img);

#endif
