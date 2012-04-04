#ifndef SAMPLE_H
#define SAMPLE_H

#include <iostream>
using namespace std;
#include <cv.h>

/*! \class Sample
 *  \brief This class contain the data of a particle
 *  \author Ludovic Brethes
 *  \date    2002-2005
 *
 */
class Sample
{
 public:
  
  /*! \param int nCP
   *  \brief this is number of elements in ContinusP vector
   */
  int nCP; 

  /*! \param int nCPdemi
   *  \brief this is half number of elements in ContinusP vector
   */
  int nCPdemi;

  /*! \param T* ContinusP
   *  \brief Vector of continuous parameters
   */
  double* ContinusP;

  /*! \param T* ContinusPcenter
   *  \brief Pointer on the half of the vector of continuous parameters
   */
  double* ContinusPcenter;

  /*! \param int CPsize
   *  \brief this is the size in byte of the ContinusP vector
   */
  int CPsize;

  /*! \param int demiCPsize
   *  \brief this is the half size in byte of the ContinusP vector
   */
  int demiCPsize;
   
  /*! \param int nDP
   *  \brief this is number of elements in DiscretsP vector
   */
  int nDP;
  
  /*! \param int* DiscretsP
   *  \brief Vector of discret parameters
   */
  int* DiscretsP;

  /*! \param int DPsize
   *  \brief this is the size in byte of the DiscretsP vector
   */
  int DPsize;

  /*! \param int idparent
   *  \brief index of the particles' parent
   */
  int idparent;

  /*########## Constructor/Destructor ########*/

  /*! \fn Sample::Sample(TrackingContext *context) 
   *  \brief Class constructor
   *  \param nCP the number of Continuous params
   *  \param nDP the number of Discrets params
   */
  Sample(int nCP, int nDP);

  /*! \fn Sample::~Sample() 
   *  \brief Class destructor
   */
  ~Sample();
  
  /*########## Methods ########*/

  /*! \fn Sample operator=(const Sample&) 
   *  \brief Operator = overloading
   *  \param Sample to be copied
   */
  Sample operator = (const Sample&);

  /*! \fn double getContinusP(int i)
   *  \brief This method return the continuous parameter i
   *  \param i the paramter to be returned
   */
  inline double getContinusP(int i) {return ContinusP[i];};

  /*! \fn int getDiscretsP(int i)
   *  \brief This method return the discret parameter i
   *  \param i the paramter to be returned
   */
  inline int getDiscretsP(int i) {return DiscretsP[i];};

  /*! \fn void setContinusP(int i, double val)
   *  \brief This method set the continuous parameter i to val
   *  \param i the paramter to be set
   *  \param val the value to assign
   */
  inline void setContinusP(int i, double val) {ContinusP[i]=val;};

  /*! \fn void setDiscretsP(int i, int val)
   *  \brief This method set the discret parameter i to val
   *  \param i the paramter to be set
   *  \param val the value to assign
   */
  inline void setDiscretsP(int i, int val) {DiscretsP[i]=val;};

  /*! \fn void ResetContinusP()
   *  \brief this method reset the particle continuous parameters
   */
  void ResetContinusP();

  /*! \fn void ResetDiscretsP()
   *  \brief this method reset the particle discret parameters
   */
  void ResetDiscretsP();

  /*! \fn void Reset()
   *  \brief this method reset the particle parameters
   */
  void Reset();

  /*! \fn void Disp()
   *  \brief this function display the sample values
   */
  void Disp(); 

  /*! \fn void DispAll()
   *  \brief this function display the sample values and all informations
   */
  inline void DispAll() {this->Disp();};

  void SplCpy(Sample* in);

  void SplCpyPast(Sample* in);
};

#endif
