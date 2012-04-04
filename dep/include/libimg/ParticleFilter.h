#ifndef PARTICLEFILTER_H
#define PARTICLEFILTER_H

#include <cv.h>
#include <iostream>
#include <string>
using namespace std;

#include "Prior.h"
#include "ContDynamicAlloc.h"
#include "DiscDynamicModel.h"
#include "TargetAlloc.h"
#include "Target.h"
#include "WeightsVector.h"
#include "Sample.h"
#include "calclut.h"
#include "ImgProducer.h"
#include "twoDDetector.h"
#include "stringutils.h"

/* Valide le log des particules sur fichier pour traiter sous matlab */
//#define SAVELOG

/* Valide la visualisation des etapes intermediaires de filtrage */
//#define VIEWALL

/* Active les algo avec fonction d'importance uniquement sur les mesures */
//#define IMPORTANCE_JUSTE_MESURE 

/* Valide la sauvegarde du trace des particules dans l'image imgParticles */
//#define SAUVEIMGPARTICULES

/*! \def NBMAXSTATES 20
 *  \brief number max of possible state for a discret parameter
 */
#define NBMAXSTATES 20

/*! \class ParticleFilter
 *  \brief Generic class for Particle filtering algorithme
 *  \author Ludovic Brethes
 *  \date    2002-2005
 *
 *  In this class all the methods and objects necessary to achieve a particle filtering
 *  are implemented. Each particle filter will be herited from this class and will use/combine 
 *  the functions and algorithms grouped here. 
 */
class ParticleFilter
{
 public:

  ImgProducer* imgBank;

  /*! \param int TargetFirstPass
   *  \brief 1 if there is a first pass target model 
   */
  int TargetFirstPass;
  
  /* Fichier de config de la cible */
  /*! \param string TGFile
   *  \brief this is the filename of the first pass target configuration
   */
  string TGFirstPassFile; 
  
  /*! \param  Target* target
   *  \brief this is on other target that will be only used during the 
   *  first pass of the algorithm
   */
  Target* target_first_pass;

  /* Fichier de sortie du log des particules a chaque instant */
  ofstream ficLog;

  /* Compteur d'instant */
  int numStep;

  string logFilename;

  /* nom du filtre */
  string nmfiltre;

  IplImage* imgTmp;

  /* Image des particules */
  IplImage* imgParticles;

  /*! \param int nbSamples
   *  \brief this is the number of samples in the sample set
   */
  int nbSamples;   
  
  /*! \param int nCP
   *  \brief this is number of elements in ContinusP vector
   */
  int nCP;

  /*! \param int nDP
   *  \brief this is number of elements in DiscretsP vector
   */
  int nDP;
  
  /*! \param Sample **sps
   *  \brief sps is a vector of Samples = particles sample set
   */
  Sample** sps;
  
  /*! \param Sample **spsnew
   *  \brief spsnew is a vector of new Samples = particles sample set after prediction or redistribution
   */
  Sample** spsnew;
  
  /*! \param WeightsVector* curw
   *  \brief this is a pointer to the weight line corresponding to the current weights
   */  
  WeightsVector* curw; 
  
  /*! \param  WeightsVector* prevw;
   *  \brief this is a pointer to the weight line corresponding to the previous weights
   */  
  WeightsVector* prevw;

  /*! \param Sample *pfState
   *  \brief this is the best sample calculated by the filter
   */
  Sample* pfState;

  /*! \param double Neff
   *  \brief This parameter represent the filter efficacity
   */
  double Neff;
  double sumNeff;

  /*! \param double Ns
   *  \brief This is a threshold before resampling when \f$Neff < Ns\f$
   */
  double Ns;

  /*! \param double **VectProbByDState
   *  \brief this matrix is used to compute the likelihood of each possible state for each discret parameter
   *   in order to choose the most likely state of each discret parameter
   */
  double** VectProbByDState;

  /*! \param double *Pkk
   *  \brief This is the covariance ok the continuous parameters computed with all the particles
   */
  double* Pkk;   

  /*! \param CvRNG rng_state
   *  \brief this is the random generator used for add noise to the prediction for example
   */
  CvRNG rng_state;
  
  /*! \param  Target* target
   *  \brief this is the target
   */
  Target* target;

  /*! \param string TGFile
   *  \brief this is the filename of the target configuration
   */
  string TGFile; 

  /*! \fn ParticleFilter::ParticleFilter(int nbSpl, int target_type, string nomfic) 
   *  \brief Class constructor
   */
  ParticleFilter(string nomfic, ImgProducer* imgproducer=0, twoDDetector* detector=0, Prior* prior=0, 
		 ContDynamicModel* ContDynamic=0, DiscDynamicModel** DiscDynamic=0);

  /*! \fn ParticleFilter::~ParticleFilter() 
   *  \brief Class destructor
   */
  ~ParticleFilter();

  /* Fonction d'enregistrement de l'etat */
  void SaveState();

  /*! \fn double ParticleFilter::CalcNeff()
   *  \brief Calcul of the filter efficacity :
   *  \f$N_{eff} \propto \frac{1}{\sum_{i=1}^{N} (w_k^i)^2}\f$
   *  \return Neff the filter efficacity
   */
  double CalcNeff(WeightsVector* weights);
  inline double CalcNeff() { return this->CalcNeff(this->curw); };

  /*! \fn void ParticleFilter::CalcPkk()
   *  \brief Processing of the SampleSet covariance at time k given k
   *  \f$P_{k|k} = \sum_{i=1}^{N} (w_k^i * x_k^i * (x_k^i)^T) - \sum_{i=1}^{N} (w_k^i * x_k^i) *  \sum_{i=1}^{N} (w_k^i * x_k^i)^T\f$
   */
  inline void CalcPkk() { CalcPkk(this->sps, this->curw); };

  /*! \fn void ParticleFilter::CalcPkk()
   *  \brief Processing of the SampleSet covariance at time k given k
   *  \f$P_{k|k} = \sum_{i=1}^{N} (w_k^i * x_k^i * (x_k^i)^T) - \sum_{i=1}^{N} (w_k^i * x_k^i) *  \sum_{i=1}^{N} (w_k^i * x_k^i)^T\f$
   */
  void CalcPkk(Sample** Spl, WeightsVector* weights);

  /*! \fn void ParticleFilter::Select()
   *  \brief Selection of the best sample by posterior mean computation
   *  from samples and WeightsVector in parameters
   */
  void Select(Sample** spl, WeightsVector* wv);

  /*! \fn void ParticleFilter::SelectContinusP()
   *  \brief Computation of the posterior mean on the continuous parameters 
   *  from samples and WeightsVector in parameters
   */
  void SelectContinusP(Sample** spl, WeightsVector* wv);

  /*! \fn void ParticleFilter::SelectDiscretsP()
   *  \brief Selection of the best state of each discrets parameters
   *  from samples and WeightsVector in parameters
   */
  void SelectDiscretsP(Sample** spl, WeightsVector* wv);

  /*! \fn void ParticleFilter::Select()
   *  \brief Selection of the best sample by posterior mean computation 
   */
  inline void Select() { Select(this->sps, this->curw); };
  
  /*! \fn int ParticleFilter::CheckDiscretsP()
   *  \brief Checking of the discret parameter of the sample snum, this method look if its state are the same of those 
   *  computed in SelectDiscretsP()
   *  \param snum : number of the particle to be checked
   *  \return an int that indicate if the particle snum is ok 
   *  @arg 1 --> ok 
   *  @arg 0 --> not ok
   */
  int CheckDiscretsP(Sample* spl);

  /*! \fn virtual void ParticleFilter::step()
   *  \brief This method must be defined in each filter inherited from this class
   *  this correspond to the filtering loop.
   */
  virtual int step(IplImage* obs=0)=0;

  /*! \fn int Process()
   *  \brief This method perform the filtering loop with filter step and target model update 
   */
  int Process();

  /*! \fn int InitSamplesFromPrior()
   *  \brief This method initialize the filter by drawing the particles around a prior mean vector
   *  with a prior covariance.
   */
  inline int InitSamplesFromPrior() { return InitSamplesFromPrior(this->sps); }; 

  /*! \fn int InitSamplesFromPrior(Sample** splset)
   *  \brief This method initialize samples from a prior mean vector
   *  with a prior covariance.
   */
  int InitSamplesFromPrior(Sample** splset); 

  /*! \fn int InitSamplesFromPrior(double* m)
   *  \brief This method initialize the filter by drawing the particles around a vector m
   *  with a prior covariance.
   */
  inline virtual int InitSamplesFromPrior(double* m) { return InitSamplesFromPrior(this->sps,m); };

  /*! \fn int InitSamplesFromPrior(double* m)
   *  \brief This method initialize the filter by drawing the particles around a vector m
   *  with a prior covariance.
   */
  int InitSamplesFromPrior(Sample** splset,double* m);

  /*! \fn int InitSamplesFromDetection()
   *  \brief This method initialize the filter by drawing the particles from the target
   *  detector result. The parameters that can't be initialized from detection are initialized
   *  using the target prior
   */
  inline int InitSamplesFromDetection() { return InitSamplesFromDetection(this->sps); }; 

  /*! \fn int InitSamplesFromDetection()
   *  \brief This method initialize the filter by drawing the particles from the target
   *  detector result. The parameters that can't be initialized from detection are initialized
   *  using the target prior
   */
  virtual int InitSamplesFromDetection(Sample** splset);

  /*! \fn int InitOneSampleFromDetection(Sample** spl, int i)
   *  \brief This method initialize one sample from the target detector result. The parameters 
   *  that can't be initialized from detection are initialized using the target prior.
   *  Detection must have been achieved before
   */
  inline int InitOneSampleFromDetection(int i) { return InitOneSampleFromDetection(this->sps,i); };
    
  /*! \fn int InitOneSampleFromDetection(Sample** spl, int i)
   *  \brief This method initialize one sample from the target detector result. The parameters 
   *  that can't be initialized from detection are initialized using the target prior.
   *  Detection must have been achieved before
   */
  int InitOneSampleFromDetection(Sample** spl, int i);

  /*! \fn void  InitDiscFromUniform(Sample *Splin)
   *  \brief This method initialize the discret parameters of the particle
   *  with a uniform random generation of the state
   */
  void InitDiscFromUniform(Sample* spl);

  /*! \fn void ParticleFilter::DispSamples()
   *  \brief Print values of all the particles on the screen 
   */
  void DispSamples();

  /*! \fn void ParticleFilter::DispOneSample()
   *  \brief Print values of one particle on the screen
   *  \param num the particle to be printed 
   */
  void DispOneSample(int num);
  
  /*! \fn void TraceAllSamples(IplImage* img);
   *  \brief draw the sample set on the image given in parameter
   *  \param img is the image on witch the samples must be drawed
   */
  void TraceAllSamples(IplImage* img, CvScalar coul); 

  /* Fonction pour tracer et enregistrer les particules dans imgParticles */
  void SaveSamplesImg(IplImage* imgIn, Sample** ss,WeightsVector* weights);
  inline void SaveSamplesImg(IplImage* imgIn) {this->SaveSamplesImg(imgIn,this->sps,this->curw);};

  /*! \fn void TraceAllSamples(IplImage* img, Sample** s);
   *  \brief draw the sample set in parametr on the image given in parameter
   *  \param img is the image on witch the samples must be drawed
   */
  void TraceAllSamples(IplImage* img, Sample** ss, CvScalar coul);

  /* Trace des particules dont les indices sont dans le vecteur ivector */
  void TraceAllSamples(IplImage* img, Sample** ss, int* ivector, CvScalar coul);
  
  /*! \fn void TraceAllSamples(IplImage* img, Sample** s);
   *  \brief draw the sample number i from the sample set in parameter on the image given in parameter
   *  \param img is the image on witch the sample must be drawed
   *  \param ss the samples
   *  \param i the sample index to draw
   *  \param color the color
   */
  void TraceOneSample(IplImage *img, Sample** ss, int i, CvScalar color=CV_RGB(255,0,0));

  /*! \fn void PlotPkk(IplImage *img,MultiBSpline2D *models,CvScalar couleur=CV_RGB(0,0,255))
   *  \brief draw the SampleSet covariance 
   *  \param img is the image on witch the samples must be drawed
   *  \param couleur the color of the particles
   */
  void PlotPkk(IplImage *img,CvScalar couleur=CV_RGB(0,0,255)); 

  /*! \fn int EdgeStep()
   *  \brief this method achieve contour step to estimate 
   *  the target parameters using edge information
   *  This is the SIR filter that can be used to refine initialisation
   *  using contours. 
   *  \return a flag to say if the estimated parameters are good
   */
  int EdgeStep();

  /* Sauvegarde des particules (etat et proba) 
     spl est la particule
     num le numero de la particule
     pos l'etape dans l'algorithme
  */
  void LogOneSample(Sample* spl, double pds, int num, string stepnm);
  
  /* Log des particules avec un indice d'etape pos (= etape du pas de filtrage) nbs defini le nombre de particules */
  void LogSamples(Sample** ss, WeightsVector* wv, int nbs, string stepnm); 
    
  /* Log des particules avec un indice d'etape pos (= etape du pas de filtrage) */
  inline void LogSamples(string stepnm) { this->LogSamples(this->sps,this->curw,this->nbSamples,stepnm); };

  /*########## Methods from old SampleSet class ########*/
  
  /*! \fn void SwitchW()
   *  \brief Method that make a switch between curw and prevw
   */
  void SwitchW(); 
  
  /*! \fn void SampleSet::SwitchSpl()
   *  \brief Method that make a switch between sps and spsnew
   */
  void SwitchSpl();

  /*########## END Methods from old SampleSet class ########*/




  /*! \fn void InitColorModel(double *pos)
   *  \brief this function initialise the color distribution model of the 
   *  tracker using the position pos
   */
  void InitColorModel(double *pos); 
 
  /*! \fn void InitColorModel()
   *  \brief this function initialise the color distribution model of the 
   *  tracker using the position estimated by the filter
   */
  void InitColorModel();



  /* Fonction d'init des sigma pour les mesures des filtres */
  virtual inline void InitTargetSigma(double* sig)
  { this->target->InitSigma(sig); };

  /* Fonction d'init des penalites pour les mesures des filtres */
  virtual inline void InitTargetPenality(double* pen)
  { this->target->InitPenality(pen); };







  /*########### Resampling methods from old class DrawSample ###########*/
  
  /*! \fn   void Resample();
   *  \brief this method resample the current samples using the current weights vector 
   */
  inline void Resample() {Resample(this->sps,this->spsnew,this->curw,this->nbSamples,this->nbSamples); SwitchSpl();};

  /*! \fn   void Resample(Sample** Splin, Sample** Splout, WeightsVector* wv);
   *  \brief this method resample a sample vector to an other sample vector
   *  using the weights in wv
   *  \param Splin is the sample vector to resample
   *  \param Splout is the resampled vector
   *  \param wv is the weights vector
   */
  inline void Resample(Sample** Splin, Sample** Splout, WeightsVector* wv) 
  { Resample(Splin,Splout,wv,this->nbSamples,this->nbSamples); };

  /*! \fn   void Resample(Sample** Splin, Sample** Splout, WeightsVector* wv, int nbS, int nbR);
   *  \brief this method resample a sample vector to an other sample vector
   *  using the weights in wv
   *  \param Splin is the sample vector to resample
   *  \param Splout is the resampled vector
   *  \param wv is the weights vector
   *  \param nbS is the number of samples in Splin vector
   *  \param nbR is the number of sample to resample from the weights vector
   */
  void Resample(Sample** Splin, Sample** Splout, WeightsVector* wv, int nbS, int nbR);

   /*! \fn void ResampleIndex(WEIGHTS *curw, int *idvector, int nbS, in nbR)
   *  \brief this function resample nb indexes from the weights in curw
   *  \param curw is the structure containing the weights vector
   *  \param idvector is the resulting vector containing the resampled indexes
   *  \param nbS is the number of oriiginal samples 
   *  \param nbR is the number of indexes that must be sampled
   */
  void ResampleIndex(WeightsVector* curw, int* idvector, int nbS, int nbR);  

  /*! \fn void ResampleIndex(WEIGHTS *curw, int *idvector)
   *  \brief this function resample ct->nbSamples indexes from the weights in curw
   *  \param curw is the structure containing the weights vector
   *  \param idvector is the resulting vector containing the resampled indexes
   */
  inline void ResampleIndex(WeightsVector* curw, int* idvector) { ResampleIndex(curw,idvector,this->nbSamples,this->nbSamples); };
  
  /*! \fn void DispState()
   *  \brief this function display the filter state (the target is displayed with pfState as parameter)
   */ 
  void DispState(); 

  /*! \fn void DispState(IplImage* img)
   *  \brief this function display the filter state (the target is displayed with pfState as parameter)
   */ 
  void DispState(IplImage* img);
  void DispState(IplImage* img,CvScalar couleur);

};

#endif
