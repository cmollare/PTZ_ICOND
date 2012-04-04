#ifndef CONSTPARAMS_H
#define CONSTPARAMS_H

/* Ce fichier contient l'ensemble des constantes */

/* PI */
#define PI 3.14159265358979

/* 2xPI */
#define DEUXPI 6.28318530717959

/* PI/2 */
#define PISURDEUX 1.57079632679490

/* (3xPI)/2 */
#define TROISPISURDEUX 4.71238898038469

/*! \def  #define NBMAXFACES 20
 *  \brief the maximum number of faces to be detected
 */
#define NBMAXFACES 20

/*! \def  #define NBMAXBLOBS 20
 *  \brief the maximum number of blobs to be detected
 */
#define NBMAXBLOBS 50

/****************************************/
/* Constantes relatives aux histogrammes */
/****************************************/
#define OFF 0 
#define ON 1 
 
//nombre d'elements dans les histogrammes 
#define NBBINS 256 
 
//Type d'affichage des histogrammes 
#define GRIS 0 
#define FCOL 1 
#define TEINTE 2 

/*************************************************/
/* Constantes pour designer les bases de couleur */
/*************************************************/
#define baseRGB 0
#define baseBGR 1
#define baseYCrCb 2
#define baseHSV 3
#define baseI1I2I3 4
#define baseIrg 5
#define basergbN 6
#define baseLab 7


#endif
