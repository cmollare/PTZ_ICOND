#ifndef MOTIONDISTRIBUTION_H
#define MOTIONDISTRIBUTION_H

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <string>
#include "matrixutils.h"
#include "calclut.h"
#include "imageutils.h"

using namespace std;

class MotionDistribution
{
 public:

  /* Distance */
  double dist;
  
  /*! \param double** data
   *  \brief this is the motion distribution datas (n bins histograms)
   *  formed by a vector of nb bins
   */
  double** data;

  /*! \param int nbbins
   *  \brief this is the number of bins
   */
  int nbbins;

  /*! \param double* unifHist
   *  \brief this is the reference uniform histogram
   */
  double* unifHist;

  /*! \param int nbHist
   *  \brief this is the number of histograms stored in this color distribution model
   */
  int nbHist;

  /*! \param int vectSize
   *  \brief this is the vector size in byte
   */
  int vectSize;

  /*! \param int* bins_mask
   *  \brief this is the bins mask used to compute only once each 
   *  RGB to bins
   */
  int* bins_mask;

  /*! \param int* bins_mask_ref
   *  \brief this is the bins mask reference used to initialise the bins_mask
   *  faster
   */
  int* bins_mask_ref;

  /*! \param int maskSize
   *  \brief this is the bins_mask size in byte
   */
  int maskSize;

  /*! \param double incr
   *  \brief this is the increment value used to compute a normalized histogram
   *  directly (usable if the number of pixels used to compute histogram is fixed)
   *  incr = 1.0/nbPix
   */
  double* incr;

  /*! \param int* nbPix
   *  \brief this is the number of pixels in each parts of the multipart area
   */
  int* nbPix;

  int moncpt;

  /*! \fn ColorDistribution()
   *  \brief class constructor
   *  \param nbb the number of bins
   *  \param nbH the number of parts in the distribution
   *  \param w is the width of the treated images
   *  \param h is the height of the treated images
   */
  MotionDistribution(int nbb, int nbH, int w, int h);
  
  /*! \fn ColorDistribution()
   *  \brief class constructor
   *  \param nbb the number of bins
   *  \param nbH the number of parts in the distribution
   *  \param w is the width of the treated images
   *  \param h is the height of the treated images
   *  \param nbPix is the number of pixels (in case of fixed size)
   *  to be considered in each distribution computation
   */
  MotionDistribution(int nbb, int nbH, int w, int h, int* nbPix);

  /*! \fn ColorDistribution()
   *  \brief class destructor
   */
  ~MotionDistribution();

  /*! \fn void Alloc(int w, int h)
   *  \brief this function allocate and initialize the bins mask and bins mask ref
   *  \param nbb the number of bins
   *  \param nbH the number of parts in the distribution
   *  \param w is the width of the treated images
   *  \param h is the height of the treated images 
   */
  void Alloc(int nbb, int nbH, int w, int h);

  /*! \fn void InitMask()
   *  \brief this function initialise the bins mask
   */
  inline void InitMask() { memcpy(this->bins_mask,this->bins_mask_ref,this->maskSize); };

  /*! \fn void CalcFromRect(int histnum, IplImage* img_mask, CvPoint& ptUL, CvPoint& ptLR, double incr)
   *  \brief this method compute color distribution histogram in a rectangle
   *  defined by its upper left and lower right corners
   *  \param img the absolute difference input image
   *  \param histnum is the histogram to compute with the ptUL ptLR rectangle
   *  \param ptUL the upper left corner of the bounding rectangle
   *  \param ptLR the lower right corner of the bounding rectangle
   *  \param incr = 1.0/(number of pixels)
   */
  void CalcFromRect(int histnum, IplImage* img, CvPoint& ptUL, CvPoint& ptLR, double incr);
  inline void CalcFromRect(int histnum, IplImage* img, CvPoint& ptUL, CvPoint& ptLR) { CalcFromRect(histnum,img,ptUL,ptLR,this->incr[histnum]); };

  /*! \fn void CalcFromRect(int histnum, IplImage* img, CvRect& r, double incr)
   *  \brief this method compute color distribution histogram in a rectangle
   *  defined by CvRect structure
   *  \param img the absolute difference input image
   *  \param histnum is the histogram to compute with the ptUL ptLR rectangle
   *  \param r the englobant rectangle
   *  \param incr = 1.0/(number of pixels)
   */
  void CalcFromRect(int histnum, IplImage* img, CvRect& r, double incr); 
  inline void CalcFromRect(int histnum, IplImage* img, CvRect& r) { CalcFromRect(histnum,img,r,this->incr[histnum]); }; 

  /*! \fn void CalcFromRectList(IplImage* img_mask, CvPoint* ptUL, CvPoint* ptLR, int *nbPix)
   *  \brief this method compute color distribution histogram in a list of rectangle
   *  defined by their upper left and lower right corners. Each rectangle is used for one histogram
   *  \param img the absolute difference input image
   *  \param ptUL the upper left corner list of the bounding rectangles
   *  \param ptLR the lower right corner list of the bounding rectangles
    *  \param nbPix is the number of pixels of each rectangles
   */
  void CalcFromRectList(IplImage* img, CvPoint* ptUL, CvPoint* ptLR, int *nbPix);
  inline void CalcFromRectList(IplImage* img, CvPoint* ptUL, CvPoint* ptLR) { CalcFromRectList(img,ptUL,ptLR,this->nbPix); };

  /*! \fn void CalcFromRectList(IplImage* img, CvRect* r, int *nbPix)
   *  \brief this method compute color distribution histogram in a rectangle
   *  defined by CvRect structure
   *  \param img the absolute difference input image
   *  \param r the englobant rectangle
   *  \param nbPix is the number of pixels of each rectangles
   */
  void CalcFromRectList(IplImage* img, CvRect* r, int *nbPix); 
  inline void CalcFromRectList(IplImage* img, CvRect* r) { CalcFromRectList(img,r,this->nbPix); }; 

  /*! \fn void CalcFromMask(IplImage* img, CvPoint& ptUL, CvPoint& ptLR, IplImage* img_mask, double incr)
   *  \brief this method compute color distribution histogram in the masked region in the rectangle
   *  defined by its upper left and lower right corners
   *  \param img the absolute difference input image
   *  \param ptUL the upper left corner of the bounding rectangle
   *  \param ptLR the lower right corner of the bounding rectangle
   *  \param img_mask is the mask witch indicate the pixels to be used for computing the histogram
   */
  void CalcFromMask(IplImage* img, CvPoint& ptUL, CvPoint& ptLR, IplImage* img_mask);

  /*! \fn void Display()
   *  \brief this function display the histogram
   */
  void Disp(string fen="HISTO", int pause=1);

  /*! \fn double BhattaDistance(int histum, double* histo)
   *  \brief this method calculate a bhattacharrya distance between the histogram in this color distribution and
   *  an other color distribution histogram
   *  \param histnum is the histogram number to be compared with histo
   *  \param histo is the histogram data (vector 8)
   */
  double BhattaDistance(int histum, double* histo);
  
  /*! \fn double BhattaDistance(int histum, double* histo, float deuxsigcarre)
   *  \brief this method calculate a bhattacharrya distance between the histogram in this color distribution and
   *  an other color distribution histogram.
   *  \param histnum is the histogram number to be compared with histo
   *  \param histo is the histogram data (vector 8)
   *  \param deuxsigcarre is the coefficient used to compute the exponential distance
   */
  double BhattaDistance(int histum, double* histo, float deuxsigcarre);
  
  /*! \fn void BhattaDistance(MotionDistribution* histref, double* dist)
   *  \brief this function compute the multihistogram distance
   */
  void BhattaDistance(MotionDistribution* histref, double* dist);
  double BhattaDistance(MotionDistribution* histref); 

  /*! \fn void BhattaDistance(MotionDistribution* histref, float deuxsigcarre, double* dist)
   *  \brief this function compute the multihistogram distance
   *  \param deuxsigcarre is the coefficient used to compute the exponential distance
   */
  void BhattaDistance(MotionDistribution* histref, float deuxsigcarre, double* dist); 
  double BhattaDistance(MotionDistribution* histref, float deuxsigcarre);

  /*  \fn double BhattaDistance(float deuxsigcarre)
   *  \brief functions that compute distance with uniform histogram 
   */
  double BhattaDistance(float deuxsigcarre);
  double BhattaDistance();
  inline double BhattaDistance(int histnum, float deuxsigcarre) { return BhattaDistance(histnum, this->unifHist, deuxsigcarre); }

  /*! \fn void Update(int histnum, double* hist, double alfa)
   *  \brief this method update the color distribution by taking account of the histogram in parameter
   */
  void Update(int histnum, double* hist, double alfa);
  
  /*! \fn void Update(int histnum, double* hist, double* alfa)
   *  \brief this method update the color distribution by taking account of the histogram in parameter
   *  \param coldist is the color distribution to use for update
   *  \param alfa is a vector of coefficients (one by color histogram) to use for update
   */
  void Update(MotionDistribution* coldist, double* alfa);
};
#endif