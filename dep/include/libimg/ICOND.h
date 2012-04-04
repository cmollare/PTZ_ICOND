#ifndef ICOND_H
#define ICOND_H

#include <string.h>
#include <cv.h>
#include "ParticleFilter.h"



/*! \class ICONDFilter
 *  \brief Class that implements ICondensation particle filter
 *  \author Ludovic Brèthes
 *  \date 2002-2005
 *
 *  This class is inherited from ParticleFilter and implement the  
 *  ICondensation algorithm 
 */
class ICONDFilter:public ParticleFilter
{

 public:

  Sample** spsTmp;
  int cptTmp;

  /*! \param CvRNG rng_state
   *  \brief this is the random generator used to choose the sampling method
   */
  CvRNG rng_state;

  /*! \param double q
   *  \brief this is the probability to generate sample from method 1
   *  if\f$(\alfa<q)\f$ method 1
   */
  double q;

  /*! \param int r
   *  \brief this is the probability used to generate sample from method 2
   *  if\f$(q<=\alfa<q+r)\f$ method 2
   */
  double r;

  /*! \param double qr
   *  \brief this is the probability used to generate sample from method 3 (condensation)
   *  if\f$(\alfa>=q+r)\f$ method 3
   */
  double qr;

  /*! \param CvMat* alfa
   *  \brief this is a vector of nbSamples uniformely distribued real values between 0 and 1
   *  and is used to choose the sampling method
   */
  CvMat* alfa;

  /*! \param int* idvector
   *  \brief this is a vector of indexes used in resampling step
   */
  int* idvector;

  /*! \param Gaussian<TCP,TW>* posNoise
   *  \brief this is a 2D gaussian containing postition dynamic noise
   */
  Gaussian* posNoise;

  /*! \fn ICONDFilter(TrackingContext *context)
   *  \brief The filter constructor 
   *  \param context a pointer to the tracking context structure
   */
  ICONDFilter(string nomfic, ImgProducer* imgproducer=0, twoDDetector* detector=0, Prior* prior=0, 
	      ContDynamicModel* ContDynamic=0, DiscDynamicModel** DiscDynamic=0);

  /*! \fn ~ICONDFilter()
   *  \brief The filter destructor 
   */
  ~ICONDFilter(); 
 
  /*! \fn int step(IplImage* obs)
   *  \brief This is the main processing step. This method correspond to a step of the
   *  algorithm. Calling step for each image achieve a RB-HS-SIR filtering.
   */
  int step(IplImage* obs);

};
#endif
