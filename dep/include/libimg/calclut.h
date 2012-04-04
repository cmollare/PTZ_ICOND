#ifndef CALCLUT_H
#define CALCLUT_H

#include <cv.h>

#define CV_RGB_OLD(r,g,b) (int)((uchar)(b) + ((uchar)(g) << 8) + ((uchar)(r) << 16))

/* calcul lut fausse couleur */
void calcul_fcol(short *lutR,short *lutG,short *lutB);

/* retourne un double correspondant a la fausse couleur d'une classe i ( 0 <= i < 255) */ 
double DCalcFcol(int i);

/* retourne un CvScalar correspondant a la fausse couleur d'une classe i ( 0 <= i < 255) */ 
CvScalar SCalcFcol(int i);

/* Calcule l'indice correspondant a la couleur CvScalar */
int CalcIndSFcol(CvScalar coul,int nbcoulmax);

/* Calcule l'indice correspondant a la couleur double */
int CalcIndDFcol(double coul,int nbcoulmax);

/* retourne un double correspondant a la teinte pour une classe i ( 0 <= i < 255) */  
double DCalcTeint(int i);

/* retourne un CvScalar correspondant a la teinte pour une classe i ( 0 <= i < 255) */ 
CvScalar SCalcTeint(int i);

/* verifie l'egalitee de deux scalars */
int ScalarEqual(CvScalar s1,CvScalar s2);

/* LUT a partir des LUT matlab */
static int jet_lutB[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			  16,32,48,64,80,96,112,128,143,159,175,
			  191,207,223,239,255,255,255,255,255,255,
			  255,255,255,255,255,255,255,255,255,255,
			  255,239,223,207,191,175,159,143,128};

static int jet_lutG[] = {0, 0, 0, 0, 0, 0, 0, 0,16,32,48,64,80,96,
			 112,128,143,159,175,191,207,223,239,255,
			 255,255,255,255,255,255,255,255,255,255,
			 255,255,255,255,255,255,239,223,207,191,
			 175,159,143,128,112,96,80,64,48,32,16, 0, 
			 0, 0, 0, 0, 0, 0, 0, 0};

static int jet_lutR[] = {143,159,175,191,207,223,239,255,255,255,
			 255,255,255,255,255,255,255,255,255,255,
			 255,255,255,255,239,223,207,191,175,159,
			 143,128,112,96,80,64,48,32,16, 0, 0, 0, 
			 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			 0, 0, 0, 0, 0, 0, 0, 0};

inline void getJetRGB(int num, CvScalar & coul)
{ coul = cvScalar(jet_lutR[num], jet_lutG[num], jet_lutB[num], 0); }


static int summer_lutB[] = {0, 4, 8,12,16,20,24,28,32,36,40,45,49,53,57,61,65,69,73,77,81,85,89,93,97,101,105,109,113,117,121,125,130,134,138,142,146,150,154,158,162,166,170,174,178,182,186,190,194,198,202,206,210,215,219,223,227,231,235,239,243,247,251,255};


static int summer_lutG[] = {128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,215,217,219,221,223,225,227,229,231,233,235,237,239,241,243,245,247,249,251,253,255};

static int summer_lutR[] = {102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102};

inline void getSummerRGB(int num, CvScalar & coul)
{ coul = cvScalar(summer_lutR[num], summer_lutG[num], summer_lutB[num], 0); }

#endif
