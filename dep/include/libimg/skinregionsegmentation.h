#ifndef SKINREGIONSEGMENTATION_H
#define SKINREGIONSEGMENTATION_H

#include <cv.h>
#include <string>
using namespace std;
#include "watershed.h"
#include "imageutils.h"
#include "displayutils.h"
#include "histogrammes.h"
#include "ColorBase.h"
#include "cvtcoloralloc.h"
#include "paramslist.h"
#include "skincolormodel.h"
#include "skincolorsegmentation.h"
#include "temps_cpu.h"

#define NBMAXREG 50

/* Classe qui permet de segmenter l'image en regions de couleur peau */
class SkinRegionSegmentation
{
public:

  /* base de couleur utilisee (a partir de la liste des bases) */
  ParamsList base;

  /* Image des regions */
  IplImage* imgReg;

  /* Image de Probabilite de la couleur peau */
  IplImage* imgProba;

  /* Image de probabilite de la couleur peau seuillee */
  IplImage* imgProbaSeuillee;

  /* Image source convertie dans une autre base */
  IplImage* imgBase;

  /* Images pour separation en trois plans */
  IplImage* imgP1;
  IplImage* imgP2;
  IplImage* imgP3;

  /* Image temporaire */
  IplImage* imgTMP;

  /* Images pour le calcul des contours */
  IplImage* imgEDGE;
  IplImage* imgGRAY;
  IplImage* imgMEDIUM;

  /* Pointeur vers l'image source */
  IplImage* imgIn;

  /* Plan chromatique */
  IplImage* planChrom[2];

  /* Pour la segmentation couleur peau */
  SkinColorSegmentation skinprob;

  /* Convertisseur couleur */
  CvtColor* colorconverter;

  /* Informations sur la base de couleur utilisee pour le clustering */
  ColorBase colBase;

  /* Valeur de seuillage de l'image de probabilite */
  double seuilProb;

  /* Seuil de l'image de probabilite peau */
  double seuilSkinProb;

  /* Histogramme de Chrominance (2D) */
  CvHistogram* histoChrom;

  /* Histogramme de Chrominance Clusterise (2D) */
  CvHistogram* histoChromClust;

  /* Histogramme de Luminance (1D) */
  CvHistogram* histoLum;

  /* Histogramme de Luminance Clusterise (1D) */
  CvHistogram* histoLumClust;

  /* Pointeurs sur les donnees des histogrammes pour les traiter directement */
  CvMat* histBins;
  CvMat* histClustBins;
  CvMat* histLumBins;
  CvMat* histLumClustBins;

  /* Nombre total de bins dans les histogrammes de chrominance */
  int nbbins;

  /* Histogramme temporaire pour les traitements */
  float* tmpHist;

  /* Objet de calcul du partage des eaux pour clusteriser l'histogramme de chominance */
  Watershed2d<float> ws;

  /* Objet de calcul du partage des eaux pour clusteriser l'histogramme de luminance */
  Watershed1d<float> wsLum;

  /* Liste de pics retenus pour le calcul de partage des eaux */
  queue<int> picList;

  /* Nombre de regions obtenues dans l'histogramme */
  int nbreg;

  /* Taille du vecteur de donnees d'un histogramme */
  int sizeHist;

  /* Seuil pour le calcul de contraste normalise */
  double seuilContrasteNorm;
  double seuilContrasteNormLum;

  /* Seuil pour la clusterisation des pics les plus importants */
  int seuilPic;
  int seuilPicLum;

  /* Image des regions apres reprojection par l'histogramme de chrominance clusterise */
  IplImage* imgRegions;
  IplImage* imgRegionsFiltrees;
  IplImage* imgRegionsMask;

  /***** Parametres pour le filtrage de l'image des regions *****/
  
  /* Une image masque */
  IplImage* imgMask;

  /* Espace de stockage des contours */
  CvMemStorage* storage;

  /* Seuil sur la taille des regions */
  int seuilRegSize;
  
  /***** Parametres pour le calcul de watershed couleur *****/
  
  /* Somme des couleurs dans les differentes regions */
  float sumR[NBMAXREG];
  float sumG[NBMAXREG];
  float sumB[NBMAXREG];

  /* Taille des vecteurs de sommes pour init rapide */
  int statsSumVectSize;

  /* Nombre de pixels par region */
  int nbRegpix[NBMAXREG];

  /* Taille du vecteur de nombre de pixels pour init rapide */
  int statsnbRegPixVectSize;

  /* Files d'attentes hierarchiques */
  queue<int> niveaux[256];

  /* Nombre total de pixels dans les images */
  int nbPixels;

  /* Pour acces rapide aux voisins d'un pixel */
  int voisList[8];

  /* Seuil de distance colorimetrique pour accepter ou non de labeliser un pixel */
  float seuilColdist;

   /* Init seuil de propagation des regions dans le watershed couleur */
  int seuilProbVois;

  /* Element structurant pour morpho math */
  IplConvKernel* eltStructurant;

  /******************************************************************************/

  /* Constructeur de la classe avec choix de la base de couleur */
  SkinRegionSegmentation(string basenm="Irg");
  ~SkinRegionSegmentation();

  /* Methode de recuperation de l'image des regions et de l'image masque */
  inline IplImage* getImgRegions() {return this->imgRegionsFiltrees; };
  inline IplImage* getImgRegionsMask() { return this->imgRegionsMask; };

  /* Methode d'allocation des histogrammes */
  int alloc_histos();

  /* Methode d'initialisation des parametres de segmentation */
  void init_params();

  /* Methode de pre traitement de l'histogramme pour augmenter sa dynamique et filtrer les trous */
  void hdyn(); 
  void lumdyn(); 
  
  /* Methode qui dilate l'histogramme avec un element structurant de taille 5 x 5 */ 
  void hdil();
  void lumdil();

  /* Methode de clusterisation de l'histogramme par watershed */
  void hclusterise();

  /* Segmentation selon la luminance des regions */
  void lumSeg();

  /* Methode de filtrage de l'image des regions */
  void filtrage();

  /* Watershed couleur qui permet de completer les regions en fonction de la couleur locale et de la probabilite */
  void color_watershed(IplImage* img_edge);
  inline void color_watershed() { color_watershed(this->imgEDGE); };

  /* Methode qui fait la segmentation region et retourne un pointeur vers l'image des regions */
  IplImage* processRegions(IplImage* imgIn);

  /* Methode qui fait la segmentation region et construit un masque des zones de penalite */
  IplImage* processRegionsMask(IplImage* imgIn);

  /********* Meme fonctions mais qui utilise l'image de contours passee en parametre (utile si elle a deja ete calculee) *************/

  /* Methode qui fait la segmentation region et retourne un pointeur vers l'image des regions */
  IplImage* processRegions(IplImage* imgIn, IplImage* img_edge);

  /* Methode qui fait la segmentation region et construit un masque des zones de penalite */
  IplImage* processRegionsMask(IplImage* imgIn, IplImage* img_edge);

  /* Calcul du masque des regions couleurs */
  void compute_region_mask(IplImage* imgIn);

};
#endif
