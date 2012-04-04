#ifndef DISCDYNAMIC_H
#define DISCDYNAMIC_H

#include <cv.h>
#include <string>
#include <iostream>
#include <fstream>
#include "matrixutils.h"
#include "Sample.h"
#include "temps_cpu.h"
#include "stringutils.h"

using namespace std;

/*! \class class DiscDynamicModel
 *  \brief this class is a virtual class containing transition model
 *  of a discret parameter
 */
class DiscDynamicModel
{
 public :

  int discdynID;
  
  /*! \param int nbStates
   *  \brief this is states number of the discret parameter considered
   *  This number implies that the transition matrix dim must be nbStates x nbStates
   */
  int nbStates;

  /*! \param int ParamPos
   *  \brief this is the position of the discret parameter considered in the 
   *  sample discret parameters vector
   */
  int ParamPos;

  /*! \param double* TransMatr
   *  \brief this is the transition matrix of the discret parameter
   */
  double* TransMatr;

  /*! \param double* TransVect
   *  \brief this is a vector of WeightVectors used to predict the parameter
   *  each WeightVector corresponds to a state probability transition (a line of the transition matrix)
   */
  double** TransVect; 

  /*! \param double* CumulativeTransVect
   *  \brief this is a vector of WeightVectors used to predict the parameter
   *  each WeightVector corresponds to a state probability transition (a line of the transition matrix)
   */
  double** CumulativeTransVect; 

  /*! \param string dispdec
   *  \brief dispdec is a shift parameter used to display informations
   *  on the screen
   */
  string dispdec;

  /*! \param CvRNG rng_state
   *  \brief this is the random generator used for prediction
   */
  CvRNG rng_state;
 
  /*! \fn   DiscDynamicModel(string nomfic, int PPos, string dispdec="")
   *  \brief this is the class constructor
   *  \param nomfic is the filename of the Discret dynamic model to be loaded (in)
   *  \param PPos is the position of the considered parameter in the sample vector
   *  \param dispdec is the displaying shift
   */
  DiscDynamicModel(string nomfic, int PPos);

  /*! \fn   ~DiscDynamicModel()
   *  \brief this is the class destructor
   */
  virtual ~DiscDynamicModel();
  
  /*! \fn int Load(string fichier);
   *  \brief this is a function that load a dynamic model from file
   *  \param nomfic is the model filename (in)
   */
  int Load(string nomfic);
  
  /*! \fn inline double getPi(int rm, int r)
   *  \brief this function return the state transition probability from rm to r
   */
  inline double getPi(int rm, int r){ return this->TransVect[rm][r];};

  /*! \fn inline void DiscDrawFromDyn(S* sin, S* sout);
   *  \brief this function achieve the parameter prediction of a particle according to
   *  the transition matrix from state in sin to state in sout
   *  \param sin is the input sample (in)
   *  \return sout contain the prediction result
   */
  inline void DiscDrawFromDyn(Sample* sin, Sample* sout) 
  { sout->DiscretsP[this->ParamPos] = PredictState(sin->DiscretsP[this->ParamPos]); };

  /*! \fn inline void DiscDrawFromDyn(S* sin, S* sout);
   *  \brief this function achieve the parameter prediction of a particle according to
   *  the transition matrix from state in sin to state in sin
   *  \param sin the sample whose discret parameter must be predicted
   *  \return sin contain the predicted parameter
   */
  inline void DiscDrawFromDyn(Sample* sin) { DiscDrawFromDyn(sin,sin); };

  /*! \fn int PredictState(int stin)
   *  \brief this function return the predicted state from state stin according
   *  to the transition matrix
   *  \param curstate is the current state of the discret parameter that must be predicted
   *  \return the function return a predicted state according to the transition matrix
   */
  int PredictState(int curstate);

  /*! \fn void Disp()
   *  \brief this method display the loaded parameters
   */
  void Disp();

};
#endif
