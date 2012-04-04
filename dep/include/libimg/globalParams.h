#ifndef GLOBALPARAMS_H
#define GLOBALPARAMS_H

#include <cv.h>
#include <string>
using std::string;

#define DEC ""
#define DECAL DEC


/*************** Definition des repertoires de travail ****************/

//Repertoires d'installation du logiciel
// #define INSTALLPATH installpath.c_str()
// #define MODELPATH "/home/lbrethes/DEVEL/NewTrack2d/track2d/config"
// #define SEQUENCESPATH "/home/lbrethes/SEQ/"
// #define DEFAULTPATH "Models/couleur/"
// #define DEFAULTSEQPATH "./apprentissage"
// #define DEFAULTFICSTATS "Bureau.dat"
// #define DEFAULTAPPRENTFOND "./fond/"
// #define DEFAULTAPPRENTMAIN "./main/"
// #define DEFAULTTRAITEMENTPATH "Models/couleur/traitement/"
// #define DEFAULTCAPTUREPATH "Models/couleur/capture/"
// #define VIDEOPATH "/home/lbrethes/"

//longueur maximale des noms de chemin (en nb de caracteres)
#define MAXPATH 100

//longueur maximale des noms de fichier (en nb de caracteres)
#define MAXFIC 50

/***************** Definition de constantes globales *******************/
#define OFF 0
#define ON 1

//nombre d'elements dans les histogrammes
#define NBBINS 256

//Type d'affichage des histogrammes
#define GRIS 0
#define FCOL 1
#define TEINTE 2

/*************** Valeurs particulieres d'angles ********************/
#define DEUXPI 6.28318530717959
#define TROISPISURDEUX 4.71238898038469
#define PI 3.14159265358979
#define PISURDEUX 1.57079632679490

/*************** Espaces de couleur disponibles ********************/
#define baseRGB 0
#define baseBGR 1
#define baseYCrCb 2
#define baseHSV 3
#define baseI1I2I3 4
#define baseIrg 5
#define basergbN 6
#define baseLab 7


#warning la suite devrait pouvoir etre supprimee apres modif de colorsegmentation


// //base RGB
// #define _RGB 0

// //nombre de bases de couleur hors RGB
// #define _NBBASES 5

// //YCrCb
// #define _YCrCb 1

// //I1I2I3
// #define _I1I2I3 2

// //HSV avec V en premier plan
// #define _VHS 3

// //Irg rgb normalise avec I le plan Intensite
// #define _Irg 4

// //Lab
// #define _Lab 5

// //Nombre total de bases de couleur dispo
// #define NBPOSSIBLECOLORBASE 6


/***************** Structures de donnees particulieres ******************/

//Structure contenant les infos sur une base de couleur
typedef struct _BaseInfos
{
  //Numero de base
  int num;
  
  //nom de la base
  char nom[10];

  //Bornes min et max sur chaque plan
  float rangeC1[2];
  float rangeC2[2];
  float rangeC3[2];

  //Nombre de valeur possibles sur chaque composantes binsC1 binsC2 binsC3
  int dims[3];

}BaseInfos;


//Structure contenant les stats pour une base de couleur
typedef struct _BaseStats
{
  //Moyennes sur chaque plans
  int m1,m2,m3;

  //Ecarts types sur chaque plan
  int sig1,sig2,sig3;

  //Covariance entre les plans chromatiques
  CvMat *cov;

  //Histogramme h_peau (peut etre une autre couleur)
  CvHistogram *h_peau;

  //Histogramme h_total
  CvHistogram *h_total;

  //Rapport d'Histogramme h_couleur/h_total
  CvHistogram *histo;  

  //min et max des composantes chromatiques
  int minC2,minC3;
  int maxC2,maxC3;

}BaseStats;

//nombre de regions max
#define NBREGMAX 256

/* Stats par region */
typedef struct _REGSTATS
{
  int numreg;
  int nbpixels;
  CvScalar couleur;
  double sumC1;
  double sumC2;
  double sumC3;
}REGSTATS;

#endif
