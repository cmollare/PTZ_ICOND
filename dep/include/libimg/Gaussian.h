#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include <cv.h>
#include <stdio.h>
#include <fstream>
#include <string.h>
using std::string;

#include "matrixutils.h"
#include "stringutils.h"
#include "cvwrap.h"
#include "temps_cpu.h"
#include "constparams.h"
#include "squarerootutils.h"

/* Pour la dependance croisee */
class Gaussian;
Gaussian* GaussianAlloc(string nomfic, string dispdec="");
Gaussian* GaussianAlloc(int dim, int diag, string dispdec="");
Gaussian* GaussianAlloc(int dim, double* m, double* c, string dispdec="");
Gaussian* GaussianAlloc(int dim, int diag, double* m, double* c, string dispdec="");

using namespace std;

/*!class Gaussian
 *  \brief This class implement a gaussian representation
 *  \author Ludovic Brethes
 *  \date    2002-2005
 */
class Gaussian
{
 public:

 /*! \param int covIsdiagonal
  *  \brief this flag indicate if the covariance is diagonal
  *  if yes then the process must be faster 
  */
 int covIsdiagonal;
 
  /*! \param dim
   *  \brief dimension of the gaussian 2,3,4,...
   */
  int dim;

  /*! \param meanMat
   *  \brief this is the mean vector
   */
  CvMat *meanMat;

  /*! \param T* mean
   *  \brief this is the meanMat data pointer
   */
  double* mean;

  /*! \param vectMat
   *  \brief this is the temporary vector candidate used to
   *  compute the gaussian value
   */
  CvMat *vectMat;

  /*! \param T* vect
   *  \brief this is the vectMat data pointer
   */
  double* vect;

  /*! \param covMat
   *  \brief this is the covariance matrix
   */
  CvMat *covMat;

  /*! \param T* cov
   *  \brief this is the covMat data pointer
   */
  double* cov; 

  /*! \param cholcovMat
   *  \brief this is the cholesky transformation of the covariance matrix
   *  cholcov * cholcov' = cov (if cov is diagonal then cholcov is the root square)
   */
  CvMat *cholcovMat;

  /*! \param double* cholcov
   *  \brief this is the meanMat data pointer
   */
  double* cholcov;

  /*! \param invcovMat
   *  \brief this is the inverse covariance matrix
   */
  CvMat *invcovMat;
  
  /*! \param double* invcov
   *  \brief this is the meanMat data pointer
   */
  double* invcov;
  
  /*! \param int meanSize
   *  \brief this is the size of mean
   *  (dim * sizeof(float)) to use when memcpy
   */
  int meanSize;

  /*! \param int covSize
   *  \brief this is the size of cov
   *  (dim * dim * sizeof(float)) to use when memcpy
   */
  int covSize;

  /*! \param detcov
   *  \brief this is the determinant of the cov matrix
   */
  double detcov;

  /*! \param double detcholcov
   *  \brief this is the cholcov matrix determinant
   */
  double detcholcov; 

  /*! \param double coeffcholcov
   *  \brief this is a coefficient used in JMSUKF 
   */
  double coeffcholcov;

  /*! \param coeff
   *  \brief coefficient used for evaluation of a vector
   */
  double coeff;
  
  /*! \param CvRNG rng_state
   *  \brief this is the random generator used for add noise to the drawed vector
   */
  CvRNG rng_state;

  /*! \param CvMat *RandVectorMat
   *  \brief this vector will contain the noise to be added on the drawed sample
   */
  CvMat *RandVectorMat;

  /*! \param double* RandVector
   *  \brief this vector will contain the noise to be added on the drawed sample
   */
  double* RandVector;

  string dispdec;

  /* Pour le cas 1D */
  double deuxsigcarre;

  /* Some temporary vectors */
  double* diff;
  double* yprim;

  /*! \fn Gaussian(string nomfic, string dispdec="")
   *  \brief Class constructor
   *  \param nomfic the filename where gaussian parameter are to be loaded
   */
  Gaussian(string nomfic, string dispdec=""); 

  /*! \fn Gaussian(int dim, string dispdec="")
   *  \brief Class constructor
   *  \param dim the gaussian dimension
   */
  Gaussian(int dim, string dispdec=""); 

  /*! \fn Gaussian(int dim, float *m, float *cov, string dispdec="")
   *  \brief Class constructor
   *  \param dim the gaussian dimension
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix
   */
  Gaussian(int dim, double* m, double* c, string dispdec="");

  /*! \fn int Load(string nomfic);
   *  \brief function that load gaussian from file
   *  \param nomfic the filename
   */
  int Load(string nomfic);

  /*! \fn void Gaussian<T,TEV>::Alloc(int dim)
   *  \brief gaussian allocator
   *  \param the gaussian size
   */
  void Alloc(int dim);

  /* 
     Operateur d'affectation
  */
  Gaussian &operator=(const Gaussian &source);

  /*! \fn Gaussian::~Gaussian() 
   *  \brief Class destructor
   */
  virtual ~Gaussian();

  /*! \fn void Gaussian::Init(float *m, float *cov)
   *  \brief initialisation of the gaussian with mean m and covariance cov
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix  
   */
  void Init(double* m, double* c);

  /*! \fn void Gaussian::Init(Gaussian* gin)
   *  \brief initialisation of the gaussian with mean m and covariance cov
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix  
   */
  void Init(Gaussian* gin);

  /*! \fn 
   *  \brief this method initialize somme parameters using current mean and covariance 
   */
  void CalcParams();
  
  /* mise a jour des parametres a partir de cholcov */
  void UpdateAllFromCholcov();

  /*! \fn void SetMeanVector(float *m)
   *  \brief This function set mean equal to mean vector
   *  there is not copy of the values but only pointer copy
   *  that makes mean to point on the vector m datas
   *  \param m the vector of datas
   */
  void SetMeanVector(double* m);

  /*! \fn void SetMean(float *m)
   *  \brief This function set mean values equal to mean vector
   *  values copying the datas
   *  \param m the vector of datas
   */
  void SetMean(double* m);

  /*! \fn void SetMean(float *m, int size)
   *  \brief This function set mean values equal to mean vector
   *  values copying size datas
   *  \param m the vector of datas
   *  \param size is the memory size to copy
   */
  void SetMean(double* m, int size);

  /*! \fn void SetCovVector(float *c)
   *  \brief This function set cov equal to cov matrix
   *  there is not copy of the values but only a pointer copy
   *  that makes cov to point on the vector c datas
   *  \param c the vector of datas
   */
  void SetCovVector(double* c);

  /*! \fn void SetCov(float *c)
   *  \brief This function set cov values equal to c matrix
   *  values copying the datas
   *  \param c the matrix of datas
   */
  void SetCov(double* c);

  /*! \fn Gaussian* Clone()
   *  \brief this method create a new gaussian identical to this one and return
   *  a pointer on this cloned gausssian
   */
 virtual Gaussian* Clone()=0;

  /*! \fn void Disp(char *label)
   *  \brief Display the dim, mean and cov of the gaussian and a label
   */
  void Disp(char *label);

  /*! \fn void Disp()
   *  \brief Display the dim, mean and cov of the gaussian
   */
  void Disp();

  /*! \fn Gaussian* Gaussian::ExtractContigousSubGauss(int nbparam, int startp, int endp)
   *  \brief Extraction of a sub part of the gaussian from contigous parameters
   *  \param nbparam is the number of parameters to extract
   *  \param startp is the first parameter position
   *  \param endp is the last parameter position
   *  \return a gaussian smaller that this one containing the gaussian sub part
   */
  Gaussian* ExtractContigousSubGauss(int nbparam, int startp, int endp);

  /*! \fn Gaussian* Gaussian::ExtractSubGauss(int nbparam, int *parlist)
   *  \brief Extraction of a sub part of the gaussian
   *  \param nbparam is the number of parameters to extract
   *  \param parlist is the parameter list
   *  \return a gaussian smaller that this one containing the gaussian sub part
   */
  Gaussian* ExtractSubGauss(int nbparam, int *parlist);

  /*! \fn double Eval(float *v)
   *  \brief This function evaluate the gaussian value for the vector v
   *  \f$p(v) = \frac{1}{2*\pi*\sqrt{|cov|}}*exp(-0.5*(v-mean)^T*cov^{-1}*(v-mean))\f$
   *  \param v is the input vector to be evaluated
   */
  virtual double Eval(double *v)=0;

  /*! \fn double Eval(float *v, float *m)
   *  \brief This function evaluate the gaussian value for the vector v
   *  considering m as mean of the gaussian
   *  \f$p(v) = \frac{1}{2*\pi*\sqrt{|cov|}}*exp(-0.5*(v-m)^T*cov^{-1}*(v-m))\f$
   *  \param v is the input vector to be evaluated
   *  \param m is the mean that must be used to evaluate the vector v
   */
  virtual double Eval(double *v, double *m)=0;

  /*! \fn void Draw(float *vout)
   *  \brief This method draw a vector from the gaussian
   *  \return vout is an allocated vector that will contain the result of drawing
   */
  virtual void Draw(double* vout)=0; 

  /*! \fn void Draw(double* mm, double* vout)
   *  \brief This method draw a vector from the gaussian using mm as mean
   *  \return vout is an allocated vector that will contain the result of drawing
   */
  virtual void Draw(double* mm, double* vout)=0; 

  /*! \fn void AddNoise(double* vin, double* vout)
   *  \brief This method add a Noise to vin in vout using cov of the gaussian
   *  \return vout is an allocated vector that will contain the result of drawing
   */
  virtual void AddNoise(double* vin, double* vout)=0;
  
  /* Calcul de p a partir de sa racine */
  double EvalFromCholCov(double* v, double* m);
  inline double EvalFromCholCov(double *v) { return EvalFromCholCov(v,this->mean); };

  /* Calcul de p a partir de sa racine en passant par un calcul en ln (meilleure conditionnement ) */
  double lnEvalFromCholCov(double *v, double* m);
  inline double lnEvalFromCholCov(double *v) { return lnEvalFromCholCov(v,this->mean); };

  /* Fonction qui calcule un coefficient a partir de  Sk (cholcov) car c'est utilise dans JMSUKF */
  /* on calcule la somme des log de la diagonale de Sk (Sk etant triangulaire) c'est le determinant a une exp pres */
  void CalcSkSumln();
  
  void CalcSkdet();

  void CopySk(Gaussian* gin);
 
};

#endif
