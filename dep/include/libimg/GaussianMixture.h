#ifndef GAUSSIANMIXTURE_H
#define GAUSSIANMIXTURE_H

#include <cv.h>
#include <highgui.h>
#include <fstream>
#include <string.h>
#include <iostream>

using namespace std;
using std::string;

#include "calclut.h"
#include "GaussianAlloc.h"
#include "stringutils.h"

/*!class GaussianMixture
 *  \brief This class is composed by a set of gaussian with coefficients in order to represent a mixture of gaussians
 *  \author Ludovic Brethes
 *  \date    2002-2005
 */
class GaussianMixture
{
public:
  
  /*! \param int nb
   *  \brief number of gaussian
   */
  int nb;
  
  /*! \param int dim
   *  \brief gaussians dimension
   */
  int dim;
  
  /*! \param int curnb
   *  \brief curent number of gaussian used (less than the nb allocated)
   */
  int curnb;
  
  /*! \param glist
   *  \brief vector of gaussian
   */
  Gaussian** glist;
  
  /*! \param coeff
   *  \brief vector of weights associated to each gaussian in the mixture
   */
  double *coeff;
  double *coeffCumul;
  
  /*! \param int areEquiprob
   *  \brief this flag indicate that all the gaussian are equiprobable
   *  in this case we use 1/curnb as coeff
   */
  int areEquiprob;
  
  /*! \param T EquiprobCoeff
   *  \brief this is the coefficient used when the gaussian are equiprobable
   */
  double EquiprobCoeff;
  
  /*! \param CvRNG rng_state
   *  \brief this is the random generator used for add noise to the drawed vector
   */
  CvRNG rng_state;
  
  string dispdec;
  
  /*! \fn GaussianMixture::GaussianMixture(string nomfic)
   *  \brief Class constructor from a file
   *  \param nomfic the filename containing gaussian mixture
   */
  GaussianMixture(string nomfic,string dispdec=""); 
  
  /*! \fn GaussianMixture::GaussianMixture(int nb, int dim)
   *  \brief Class constructor which only allocate ang initialise the class
   *  \param nb the number of gaussians in the mixture
   *  \param dim the gaussians dimension
   */
  GaussianMixture(int nb,int dim,string dispdec=""); 
  
  /*! \fn GaussianMixture(int nb, int dim, T *m, T *cov)
   *  \brief Class constructor
   *  \param nb the number of gaussians in the mixture
   *  \param dim the gaussian dimension
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix
   */
  GaussianMixture(int nb,int dim, double *m, double *cov,string dispdec="");

  /*! \fn GaussianMixture(int nb, Gaussian *g)
   *  \brief Class constructor
   *  \param nb the number of gaussians in the mixture
   *  \param g the gaussian used for gaussian mixture initialisation
   */
  GaussianMixture(int nb, Gaussian *g);  

  /*! \fn 
   *  \brief Function that load a gaussian mixture from file
   *  \param nomfic the filename containing gaussian mixture
   */
  int Load(string nomfic);

  /*! \fn void Alloc(int nb, int dim)
   *  \brief Gaussian Mixture initialisations and allocations
   *  \param nb the number of gaussians in the mixture
   *  \param dim the gaussians dimension 
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix
   */
  void Alloc(int nb, int dim, double *m, double *cov);
  
  /*! \fn GaussianMixture::~GaussianMixture() 
   *  \brief Class destructor
   */
  ~GaussianMixture();

  /*! \fn void Init(T *m, T *cov)
   *  \brief Initialisation of the gaussian with same mean and cov
   *  \param m the initial mean vector
   *  \param c the initial covariance matrix
   */
  void Init(double *m, double *cov);
  inline void Init(int num, double *m, double *cov) 
  { if(num<this->nb) this->glist[num]->Init(m,cov); };

  /*! \fn void Init(Gaussian *g)
   *  \brief Initialization of the gaussian mixture with the gaussian g
   *  \param g the gaussian used for gaussian mixture initialisation
   */
  void Init(Gaussian *g);
  inline void Init(int num, Gaussian *g) 
  { if(num<this->nb) this->glist[num]->Init(g->mean,g->cov); };

  /*! \fn void Transform(CvPoint *centerslist, int nbcenters)
   *  \brief This method is used to change the mixture 
   *  by positionning each gaussian of the mixture on the centers
   *  in parameter
   *  \param centerslist is the list of the centers on which the gaussian must be positionned
   *  \param nbcenters is the number of centers and must be lowed than nb
   */
  void Transform(CvPoint *centerslist, int nbcenters);

  /*! \fn double Eval(double *v)
   *  \brief This method evaluate the vector v in the gaussian mixture
   *  \param v the vector to evaluate
   *  \return a double corresponding to the likelihood of the vector
   */
  double Eval(double *v);

  /*! \fn double EvalEquiProb(double *v)
   *  \brief This method evaluate the vector v in the gaussian mixture
   *  where each gaussian are equiprobable
   *  \param v the vector to evaluate
   *  \return a TEV corresponding to the likelihood of the vector
   */
  double EvalEquiProb(double *v);
  
  /*! \fn double EvalWeighted(double *v)
   *  \brief This method evaluate the vector v in the gaussian mixture
   *  \param v the vector to evaluate
   *  \return a TEV corresponding to the likelihood of the vector
   */
  double EvalWeighted(double *v);

  /*! \fn void Draw(double *vout)
   *  \brief This function draw a vector from the gaussian mixture
   *  \param v the vector to evaluate
   */
  void Draw(double *v); 

  /*! \fn void Draw(double* mm, double *vout)
   *  \brief This function draw a vector from the gaussian mixture
   *  \param v the vector to evaluate
   */
  void Draw(double* mm, double *v);

  /*! \fn int Select()
   *  \brief This select un number corresponding to a gaussian index
   *  according to the gaussian weights
   *  \return an integer that is a gaussian index
   */
  int Select();
  
  /*! \fn void Disp()
   *  \brief Display the dim, mean and cov of each gaussian in the mixture
   */
  void Disp();

  /*! \fn void View(char *nm, int w=320, int h=240)
   *  \brief this function display a 2D gaussian mixture on an image
   */
  void ViewGM(char *nm, int w=320, int h=240);

  /*! \fn void ViewFromDraw(int nbpt, char *nm, int w=320, int h=240)
   *  \brief this function display a 2D gaussian mixture on an image with weighted points
   */
  void ViewFromDraw(int nbpt, char *nm, int w=320, int h=240);

  /* Retourne la moyenne d'une gaussienne de la mixture avec une proba correspondante au coeff */
  inline double* getMean()
  {  
    /* selection de la gaussienne */
    int selected = Select();
    
    /* tir du vecteur selon la gaussienne selectionnee */
    return glist[selected]->mean;
  }

  /* Remise a zero de la mixture (curnb) */
  inline void raz() { this->curnb = 0; };

  /* Ajout d'une gausienne (on incremente puis initialise) */
  inline void add(Gaussian* g) { this->add(g->mean,g->cov); };
  void add(double* m, double* c=NULL);

  int updateMixtureCoeff(double* coefflist, double coeffsum);

};

#endif
