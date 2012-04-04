#ifndef GAUSSIANDIAG2D_H
#define GAUSSIANDIAG2D_H

#include "Gaussian.h"

class GaussianDiag2D : public Gaussian
{
public :
  
  /*! \fn Gaussian(string nomfic)
   *  \brief Class constructor
   *  \param nomfic the filename where gaussian parameter are to be loaded
   */
  GaussianDiag2D(string nomfic, string dispdec=""); 
  
  /*! \fn Gaussian(int dim)
   *  \brief Class constructor
   *  \param dim the gaussian dimension
   */
  GaussianDiag2D(int dim, string dispdec=""); 
  
  /*! \fn Gaussian(int dim, float *m, float *cov)
   *  \brief Class constructor
   *  \param dim the gaussian dimension
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix
   */
  GaussianDiag2D(int dim, double* m, double* c, string dispdec="");
  
  /*! \fn Gaussian* Clone()
   *  \brief this method create a new gaussian identical to this one and return
   *  a pointer on this cloned gausssian
   */
  inline GaussianDiag2D* Clone() 
  { return new GaussianDiag2D(this->dim,this->mean,this->cov,this->dispdec); };

  /*! \fn double Eval(float *v)
   *  \brief This function evaluate the gaussian value for the vector v
   *  \f$p(v) = \frac{1}{2*\pi*\sqrt{|cov|}}*exp(-0.5*(v-mean)^T*cov^{-1}*(v-mean))\f$
   *  \param v is the input vector to be evaluated
   */
  double Eval(double *v);
  
  /*! \fn double Eval(float *v, float *m)
   *  \brief This function evaluate the gaussian value for the vector v
   *  considering m as mean of the gaussian
   *  \f$p(v) = \frac{1}{2*\pi*\sqrt{|cov|}}*exp(-0.5*(v-m)^T*cov^{-1}*(v-m))\f$
   *  \param v is the input vector to be evaluated
   *  \param m is the mean that must be used to evaluate the vector v
   */
  double Eval(double *v, double *m);
  
  /*! \fn void Draw(float *vout)
   *  \brief This method draw a vector from the gaussian
   *  \return vout is an allocated vector that will contain the result of drawing
   */
  void Draw(double* vout);
  
  /*! \fn void Draw(float *vout)
   *  \brief This method draw a vector from the gaussian
   *  \return vout is an allocated vector that will contain the result of drawing
   */
  void Draw(double* mm, double* vout); 
  
  /*! \fn void AddNoise(T* vin, T*vout)
   *  \brief This method add a Noise to vin in vout using cov of the gaussian
   *  \return vout is an allocated vector that will contain the result of drawing
   */
  void AddNoise(double* vin, double* vout);
};

#endif
