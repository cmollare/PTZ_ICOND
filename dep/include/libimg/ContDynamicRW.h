#ifndef CONTDYNAMICRW_H
#define CONTDYNAMICRW_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using std::string;

#include "ContDynamicModel.h"
#include "Gaussian.h"
#include "matrixutils.h"
#include "stringutils.h"

/* Classe qui implemente une dynamique de marche aleatoire (random walk) */
class ContDynamicRW : public ContDynamicModel
{
 public :

  /* Matrice de dynamique (ici identitee) */
  double* DynMatrix;

  /* matrice globale de bruit de dynamique */
  double* NoiseVector; 
  double* CholNoiseVector;
  double* InvNoiseVector;
  double* NoiseMatrix;
  double* tmpVector;

  int sizetmpVector;

  /* Somme des ln de Qii * -0.5 calcule en avance pour le coeff */
  double coeffSumlnQii;

  /* Partie 2 * pi du coeff pour calculer la gaussienne complete */
  double deuxpicoeff;

  /* Gaussienne associee au bruit de dynamique global */
  Gaussian* DynNoiseGauss;
  
  /* dimension des matrices */
  int dimDynMatrix;
  int dimNoiseVector;
  int dimNoiseMatrix;

  /* taille des matrices individuelles (en octet) */
  int sizeDynMatrix;
  int sizeNoiseVector;
  int sizeNoiseMatrix;

  /* borne max normalisee et borne min */
  //float* bound_max_norm; 
  //float* bound_min;

  /*! \param CvRNG rng_state
   *  \brief this is the random generator used for add noise to the prediction for example
   */
  CvRNG rng_state;
  
  /*! \param CvMat *RandSCPVector
   *  \brief this vector will contain the noise of the process resulting of TempCPVector * NoiseCovariance
   */
  CvMat *RandVector;

  /*! \param TCP* ptRand
   *  \brief this is the Rand data pointer
   */
  double* ptRand;

  /* coeff pour le choix du tir */
  //float betaU;
  //float un_moins_betaU;

  /* valeur tiree pour selection du tir */
  double val;

  /* Poids associe a la loi uniforme */
  //double Unipds;
  
  ContDynamicRW(string nomfic);
  ~ContDynamicRW();

  //Chargement des modeles de dynamique
  int Load(string nomfic);
  
  //Prediction de la partie continue d'une particule en fonction de la dynamique avec ajout du bruit
  inline void ContDrawFromDynWithNoise(Sample* Spin, Sample* Spout, int model) 
  { this->ContDrawFromDynWithNoise(Spin, Spout); };
  
  inline void ContDrawFromDynWithNoise(Sample* s, int model)  
  { this->ContDrawFromDynWithNoise(s); };
  
  inline void ContDrawFromDynWithNoise(Sample* s) 
  { this->ContDrawFromDynWithNoise(s, s); };
  
  inline void ContDrawFromDynWithNoise(Sample* Spin, Sample* Spout)
  { this->DynNoiseGauss->Draw(Spin->ContinusP,Spout->ContinusP); }; 

  //Prediction de la partie continue d'une particule en fonction de la dynamique sans bruit
  inline void ContDrawFromDynWithOutNoise(Sample* Spin, Sample* Spout, int model) 
  {this->ContDrawFromDynWithOutNoise(Spin,Spout);};

  inline void ContDrawFromDynWithOutNoise(Sample* s, int model) 
  {this->ContDrawFromDynWithOutNoise(s);};
  
  inline void ContDrawFromDynWithOutNoise(Sample* s) 
  { this->ContDrawFromDynWithOutNoise(s,s); };  
  
  void ContDrawFromDynWithOutNoise(Sample* Spin, Sample* Spout);
  
  //Fonction d'ajout du bruit de dynamique (dans ce cas ca revient a la prediction avec bruit car la dynamique c'est l'identitee)
  inline void ContAddDynNoise(Sample* Spin, Sample* Spout, int model) 
  { this->ContAddDynNoise(Spin,Spout); };
  
  inline void ContAddDynNoise(Sample* s, int model) 
  { this->ContAddDynNoise(s); };
  
  inline void ContAddDynNoise(Sample* s)
  { this->ContAddDynNoise(s,s); };
  
  inline void ContAddDynNoise(Sample* Spin, Sample* Spout) 
  { this->ContDrawFromDynWithNoise(Spin,Spout); };

  //Methode d'evaluation d'une particule en fonction de la dynamique
  inline double ContEval(Sample* sk, Sample* skm, int model) 
  { return this->ContEval(sk,skm);};
  
  inline double ContEval(Sample* sk, Sample* skm) 
  //{  return this->Unipds + (this->un_moins_betaU*this->DynNoiseGauss->Eval(sk->ContinusP,skm->ContinusP)); };
  {  return this->DynNoiseGauss->Eval(sk->ContinusP,skm->ContinusP); };

  //Methode d'affichage du modele
  void Disp();

  inline double* getDynMatrPtr(int model=0) { return this->DynMatrix; };

  //Methode de recuperation de la matrice de bruit de dynamique associee au modele 
  inline double* getDynamicNoiseMatr(int model=0) { return this->DynNoiseGauss->cov; };

  //Methode de recuperation de la racine de la matrice de bruit de dynamique associee au modele 
  inline double* getDynamicNoiseMatrSqrt(int model=0) { return this->DynNoiseGauss->cholcov; };

  //Retourne la matrice inverse 
  inline double* getDynamicNoiseMatrInv(int model=0) { return this->DynNoiseGauss->invcov; };

  inline double* getDynamicNoiseVectInv(int model=0) { return this->InvNoiseVector; };

  //Methode de recuperation de la matrice de bruit de dynamique complete ( associee au modele 
  inline double* getFullDynamicNoiseMatr(int model=0) { return this->NoiseMatrix; };

  /* Fonction qui calcule un coefficient a partir de  Q (bruit de dynamique) car c'est utilise dans JMSUKF */
  /* on calcule la somme des log de la diagonale de Q (Sk etant diagonale) c'est le determinant a une exp pres */
  void CalcQSumln();
};
#endif

