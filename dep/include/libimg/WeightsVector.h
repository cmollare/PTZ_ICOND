#ifndef WEIGHTSVECTOR_H
#define WEIGHTSVECTOR_H

#include <iostream>
#include <string>
using namespace std;

/*! \class WeightsVector
 *  \brief This class is a vector of weights used by SampleSet for
 *  particle filtering and functions to manipulate weights are implemented
 *  here
 */
class WeightsVector
{
 public:
  /*! \param int nbw
   *  \brief this is the vector size
   */
  int nbw;

  /*! \param int vectorSize
   *  \brief this contain the vector size in byte
   *  and is used to make processing faster
   */
  int vectorSize;
  
  /*! \param CvMat *w
   *  \brief weights vector 
   */
  double *w;

  /*! \param double* normalizedw
   *  \brief weights vector 
   */
  double* normalizedw;     
  
  /*! \param CvMat *cumulativew
   *  \brief cumulative weights vector 
   */
  double *cumulativew;

  /*! \param bool normalized
   *  \brief this flag indicate if the vector w is normalized
   */
  bool normalized;

  /*! \param bool wcumulcalculed
   *  \brief this flag indicate if the cumulative weights vector is calculated
   */
  bool wcumulcalculed;

  /*! \param double initVal
   *  \brief this is the initial value used to initialise the vector
   */
  double initVal;
  
  /*! \param double sum
   *  \brief weights sum  
   */  
  double sum;    

  /*! \param double coeff
   *  \brief a coefficient used for weight normalisation \f$coeff = \frac{1}{sum}\f$ 
   */
  double coeff;   

  /*! \fn WeightsVector(int taille)
   *  \brief this is the vector constructor
   *  \param taille is the number of weights stored in the vector
   */
  WeightsVector(int taille);

  /*! \fn ~WeightsVector()
   *  \brief class destructor
   */
  ~WeightsVector();

  /*! \fn void ResetVector()
   *  \brief this function initialise WeightsVector parameters 
   *  to be able to set new weights
   */
  void ResetVector();

  /*! \fn void ResetAllVector()
   *  \brief this function initialise WeightsVector parameters 
   *  to be able to set new weights
   */
  void ResetAllVector();

  /*! \fn void InitVector()
   *  \brief this function initialise the vector to initVal
   */
  void InitVector();

  /*! \fn void InitVector(double val)
   *  \brief this function initialise the vector to val
   *  \param val is the value used to initialise the vector
   */
  void InitVector(double val);

  /*! \fn int NormVector()
   *  \brief this function normalize the vector by its sum
   */
  int NormVector(); 

  /*! \fn int NormVector(WeightsVector* normw)
   *  \brief this function normalise the vector and puts the result in normw
   *  \return a pointer on the normalised weights vector
   */
  int NormVector(WeightsVector* normw);

  /*! \fn int NormVector(double *normw)
   *  \brief this function normalise the vector and puts the result in normw
   *  \return a pointer on the normalised weights vector
   */
  int NormVector(double *normw);

  /*! \fn int CalcCumulativeW()
   *  \brief this function compute cumulative weights vector
   */
  int CalcCumulativeW();

 /*! \fn int CalcCumulativeW(WeightsVector* normw)
   *  \brief this function compute cumulative weights vector
   */
  int CalcCumulativeW(WeightsVector* normw);

 /*! \fn int CalcCumulativeW(double *normw)
  *  \brief this function compute cumulative weights vector
  */
 int CalcCumulativeW(double *normw);

 /*! \fn int NormVector(WeightsVector *normw)
  *  \brief this function normalise the vector and the cumulative weights vector and puts the result in normw
  */
 int NormAndCumulVector(WeightsVector *normw);

 /*! \fn int NormVector()
  *  \brief this function normalise the vector and the cumulative weights vector
  */
 int NormAndCumulVector();

  /*! \fn double* getCumulativeWptr()
   *  \brief this function compute the cumulative weights if it is not done and return
   *  a pointer on the datas
   *  \return the pointer on the cumulative weights
   */
  double* getCumulativeWptr();

  /*! \fn inline double getCumulativeW(int id)
   *  \brief this function compute the cumulative weights if it is not done and return
   *  the id cumulative weight
   *  \return the cumulative weight at index id
   */
  inline double getCumulativeW(int id) {return cumulativew[id];};

 /*! \fn double* getNormalizedWptr()
   *  \brief this function compute the normalized weights if it is not done and return
   *  a pointer on the datas
   *  \return the pointer on the normalized weights
   */
  double* getNormalizedWptr();

  /*! \fn inline double getNormalizedW(int id)
   *  \brief this function compute the normalized weights if it is not done and return
   *  the id cumulative weight
   *  \return the normalized weight at index id
   */
  inline double getNormalizedW(int id) {return normalizedw[id];};

  /*! \fn inline double* getWptr()
   *  \brief this function return a pointer on the w vector
   */
  inline double* getWptr() {return w;};
  
  /*! \fn inline double getW(int i)
   *  \brief function that return the i weight
   *  \param i the index
   */
  inline double getW(int i) {return w[i];};

  /*! \fn inline void setW(int i, double val) {w->data.db[i] = val;};
   *  \brief this function is used to set the weight number i to val
   *  \param i the index
   *  \param val the value to set 
   */
  inline void setW(int i, double val) {w[i] = val; sum+=val;};

  /*! \fn void DispW()
   *  \brief this function display the weights vector
   */
  void DispW();

  /*! \fn void DispCumulativeW()
   *  \brief this function display the cumulative weights vector
   */
  void DispCumulativeW();

 /*! \fn void DispNormalizedW()
  *  \brief this function display the cumulative weights vector
  */
 void DispNormalizedW();

 /*! \fn void Disp()
  *  \brief this function display all the vectors
  */
 void Disp();
  
};

#endif
