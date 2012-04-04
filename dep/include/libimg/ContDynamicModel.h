#ifndef CONTDYNAMICMODEL_H
#define CONTDYNAMICMODEL_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#include "constparams.h"
#include "Sample.h"

/*! \class template<class T> class ContDynamicModel
 *  \brief this class is a virtual class containing the dynamic model for continuous parameters of the filter. class T is the same type as the continuous parameters of the sample (float or double). class S is the sample class that is considered
 *  Exemple of declaration : ContDynamicModel
 */
class ContDynamicModel
{

 public :
 
  int dynamicID;

  string dispdec;

  //Nombre de parametres a estimer
  int nDynCP;
  int nDynDP;

  int nCP;

  /* coeffQ = somme des ln(Qii) */
  double coeffQ;

  //Constructeur
  ContDynamicModel();
  virtual ~ContDynamicModel();
  
  //Chargement des modeles de dynamique
  virtual int Load(string nomfic)=0;
  
  //Prediction de la partie continue d'une particule en fonction de la dynamique avec ajout du bruit
  virtual void ContDrawFromDynWithNoise(Sample* sin, Sample* sout, int model)=0; 
  virtual void ContDrawFromDynWithNoise(Sample* sin, Sample* sout)=0; 
  virtual void ContDrawFromDynWithNoise(Sample* s, int model)=0; 
  virtual void ContDrawFromDynWithNoise(Sample* s)=0;
   
  //Prediction de la partie continue d'une particule en fonction de la dynamique sans bruit
  virtual void ContDrawFromDynWithOutNoise(Sample* sin, Sample* sout, int model)=0;
  virtual void ContDrawFromDynWithOutNoise(Sample* s, int model)=0;
  virtual void ContDrawFromDynWithOutNoise(Sample* sin, Sample* sout)=0;
  virtual void ContDrawFromDynWithOutNoise(Sample* s)=0;
   
  //Fonction d'ajout du bruit de dynamique
  virtual void ContAddDynNoise(Sample* sin, Sample* sout, int model)=0;
  virtual void ContAddDynNoise(Sample* s, int model)=0; 
  virtual void ContAddDynNoise(Sample* sin, Sample* sout)=0;
  virtual void ContAddDynNoise(Sample* s)=0;

  //Methode d'evaluation d'une particule en fonction de la dynamique
  virtual double ContEval(Sample* s1, Sample*s2, int model)=0; 
  virtual double ContEval(Sample* s1, Sample*s2)=0;

  //Methode d'affichage du modele
  virtual void Disp()=0;

  virtual double* getDynMatrPtr(int model=0)=0;

  //Methode de recuperation de la matrice de bruit de dynamique associee au modele 
  virtual double* getDynamicNoiseMatr(int model=0)=0;
  
  virtual double* getDynamicNoiseMatrInv(int model=0)=0; 
  virtual double* getDynamicNoiseVectInv(int model=0)=0;
  
  //Methode de recuperation de la racine de la matrice de bruit de dynamique associee au modele 
  virtual double* getDynamicNoiseMatrSqrt(int model=0)=0;

  //Methode de recuperation de la matrice de bruit de dynamique complete ( associee au modele 
  virtual double* getFullDynamicNoiseMatr(int model=0)=0; 

  /* Fonction qui calcule un coefficient a partir de  Q (bruit de dynamique) car c'est utilise dans JMSUKF */
  /* on calcule la somme des log de la diagonale de Q (Sk etant diagonale) c'est le determinant a une exp pres */
  virtual void CalcQSumln()=0;

};
#endif
