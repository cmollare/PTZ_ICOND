#ifndef IMGPRODUCER_H
#define IMGPRODUCER_H

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;

#include "displayutils.h"
#include "skincolormodel.h"
#include "stringutils.h"

/* Classe contenant toutes les images et les fonctions pour le traitement */
class ImgProducer
{
public:

  /* Pointeur vers l'image originale RGB */
  IplImage* imgSRC;
  IplImage* imgSRCPrec;

  /* Vecteur d'images */
  vector<IplImage*> img;
  vector<IplImage*> imgPrec;

  /* Vecteur de noms associes aux images */
  vector<string> imgNM;

  /* Vecteur de flag */
  int* imgOK;
  int size;

  /* Definition d'une map pour associer le nom d'une image a son nom */
  map<const char *, int, less<const char *> > imgID;

  /* Compteur d'images traitees */
  int imgCpt;
  
  /* Dimensions de reference des images traitees */
  int width;
  int height;

  /* Constructeur */
  ImgProducer(int w, int h);

  /* Destructeur */
  ~ImgProducer();

  /* Ajout d'une image et allocation de celle ci */
  int imgRegister(const char* nm, int w, int h, int depth, int plane);

  /* Recuperation du pointeur vers l'image */
  inline IplImage* imgGetPtr(const char* nm)
  { return img[imgID[nm]]; };

  /* Recuperation du pointeur vers l'image precedente */
  inline IplImage* imgGetPtrPrec(const char* nm)
  { return imgPrec[imgID[nm]]; };

  inline IplImage* getImgPrec(const char* nm)
  { return imgPrec[imgID[nm]]; }

  /* methode d'affichage des images */
  void disp(int calcall=0);

  /* Initialise le producteur avec une nouvelle image */
  inline void set(IplImage* imgIn)
  {
    /* Recopie du pointeur */
    imgSRCPrec = imgSRC;
    imgSRC = imgIn;

    /* swap du vecteur d'images */
    img.swap(imgPrec);

    /* Mise a zero du vecteur flag */
    memset(imgOK,0,size);
  }

  /* Methode d'allocation de tous les parametres des modules de traitements */
  void alloc();

  /* Methode de traitement faisant le calcul de toutes les images */
  void process(IplImage* imgIn=0);


  /*********************************/
  /* METHODES DE CALCUL DES IMAGES */
  /*********************************/
  
  /* Retourne directement le pointeur vers l'image RGB */
  inline IplImage* imgRGB(){ return imgSRC; };
  inline IplImage* imgRGBPrec(){ return imgSRCPrec; };

  /*******************************************/
  /* Calcul image en niveau de gris          */
  /*******************************************/
  int idGRAY;
  
  inline IplImage* imgGRAY()
  {
    if(!imgOK[idGRAY]) calcGRAY();
    return img[idGRAY];    
  }         

  inline IplImage* imgGRAYPrec()
  { return imgPrec[idGRAY]; }         

  void allocGRAY();
  void calcGRAY();

  /*******************************************************************/
  /* Calcul image de difference absolue (en niveau de gris)          */
  /*******************************************************************/
  int idDIFFABS;
  
  inline IplImage* imgDIFFABS()
  {
    if(!imgOK[idDIFFABS]) calcDIFFABS();
    return img[idDIFFABS];    
  }         

  inline IplImage* imgDIFFABSPrec()
  { return imgPrec[idDIFFABS]; }         

  void allocDIFFABS();
  void calcDIFFABS();                                  

  /*******************************************/
  /* Calcul image filtree PyrDown samplee    */
  /*******************************************/
  int idPYRDOWN;
  
  inline IplImage* imgPYRDOWN()
  {
    if(!imgOK[idPYRDOWN]) calcPYRDOWN();
    return img[idPYRDOWN];    
  }         

  inline IplImage* imgPYRDOWNPrec()
  { return imgPrec[idPYRDOWN]; }

  void allocPYRDOWN();
  void calcPYRDOWN();

  /*******************************************/
  /*       Calcul image de contours          */
  /*******************************************/
  int idEDGE;
  
  inline IplImage* imgEDGE()
  {
    if(!imgOK[idEDGE]) calcEDGE();
    return img[idEDGE];    
  }         

  inline IplImage* imgEDGEPrec()
  { return imgPrec[idEDGE]; }

  void allocEDGE();
  void calcEDGE();                                  

  /*******************************************/
  /*       Calcul image GRAY filtree         */
  /*******************************************/
  int idFGRAY;
  int idMGRAY;   // image gris sous echantillonnee
  
  inline IplImage* imgFGRAY()
  {
    if(!imgOK[idFGRAY]) calcFGRAY();
    return img[idFGRAY];    
  }         

  inline IplImage* imgFGRAYPrec()
  { return imgPrec[idFGRAY]; }

  inline IplImage* imgMGRAYPrec()
  { return imgPrec[idMGRAY]; }

  void allocFGRAY();
  void calcFGRAY();                                  
  
  /*******************************************/
  /*       Calcul image SKIN PROBA           */
  /*******************************************/
  int idSKINPROB;
  int idP1;
  int idP2;
  int idP3;

  //  SkinColorSegmentation* scs;
  /* Modele de couleur peau */
  SkinColorModel skinModel;

  /* Liste d'images pour la projection dans l'histogramme */
  IplImage** images;


  inline IplImage* imgSKINPROB()
  {
    if(!imgOK[idSKINPROB]) calcSKINPROB();
    return img[idSKINPROB];    
  }         

  inline IplImage* imgSKINPROBPrec()
  { return imgPrec[idSKINPROB]; }
  
  inline void setSKINPROB_Thresh(double seuil) 
  { skinModel.threshold(seuil); };

  void allocSKINPROB();
  void calcSKINPROB();  

  /*******************************************/
  /*     Calcul du masque flot optique       */
  /*******************************************/
  int idFLOWMASK;
  int idGIMGX;
  int idGIMGY;

  CvTermCriteria criteria;
  double lambda;
  int xremainstep,yremainstep,mremainstep;
  
  inline IplImage* imgFLOWMASK()
  {
    if(!imgOK[idFLOWMASK]) calcFLOWMASK();
    return img[idFLOWMASK];    
  }         

  inline IplImage* imgFLOWMASKPrec()
  { return imgPrec[idFLOWMASK]; }

  void allocFLOWMASK();
  void calcFLOWMASK();

};
#endif
