#ifndef CVTCOLOR_H
#define CVTCOLOR_H

#include <cv.hpp>
//#include "colorconversion.h"

/***************************************************/
/*                 CLASSE DE BASE                  */
/***************************************************/

/*! \class CvtColor
 *  \brief this class achieve color image conversion from RGB to an other base
 */
class CvtColor
{
 public:
  /* dimensions des images a traiter */
  int width;
  int height;

  /* Image de 1 pixel pour faire de la conversion de pixel */
  IplImage* pixImg;
  IplImage* pixImg2;

  /* Flag indiquant si la conversion prend des RGB ou BGR en entree */
  int fromRGB;

  /* constructor */
  CvtColor(int w=320, int h=240, int fromRGB=0);
  virtual ~CvtColor();

  /* Conversion simple des valeurs RGB vers une autre base */
  void convert(uchar r, uchar g, uchar b, uchar* C1, uchar* C2, uchar* C3);

  /* conversion function */
  virtual void convert(IplImage* imgin, IplImage* imgout)=0;
  virtual void convert2(IplImage* imgin, IplImage* imgout)=0;
};

/**********************************************************/
/*                 CONVERSION VERS YCrCb                  */
/**********************************************************/

/*! \class CvtColorRGB2YCrCb
 *  \brief this class achieve color image conversion from RGB to YCrCb
 */
class CvtColorRGB2YCrCb:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorRGB2YCrCb(int w=320, int h=240):CvtColor(w,h,1){};
  ~CvtColorRGB2YCrCb(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_RGB2YCrCb); };  
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/*! \class CvtColorBGR2YCrCb
 *  \brief this class achieve color image conversion from BGR to YCrCb
 */
class CvtColorBGR2YCrCb:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorBGR2YCrCb(int w=320, int h=240):CvtColor(w,h,0){};
  ~CvtColorBGR2YCrCb(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_BGR2YCrCb); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/**********************************************************/
/*                 CONVERSION VERS HSV                  */
/**********************************************************/

/*! \class CvtColorRGB2HSV
 *  \brief this class achieve color image conversion from RGB to HSV
 */
class CvtColorRGB2HSV:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorRGB2HSV(int w=320, int h=240):CvtColor(w,h,1){};
  ~CvtColorRGB2HSV(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_RGB2HSV); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/*! \class CvtColorBGR2HSV
 *  \brief this class achieve color image conversion from BGR to HSV
 */
class CvtColorBGR2HSV:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorBGR2HSV(int w=320, int h=240):CvtColor(w,h,0){};
  ~CvtColorBGR2HSV(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_BGR2HSV); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/***************************************************************/
/*                 CONVERSION VERS RGB et BGR                  */
/***************************************************************/
/*! \class CvtColorRGB2BGR
 *  \brief this class achieve color image conversion from RGB to BGR
 */
class CvtColorRGB2BGR:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorRGB2BGR(int w=320, int h=240):CvtColor(w,h,1){};
  ~CvtColorRGB2BGR(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_RGB2BGR); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};


/*! \class CvtColorBGR2RGB
 *  \brief this class achieve color image conversion from BGR to RGB
 */
class CvtColorBGR2RGB:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorBGR2RGB(int w=320, int h=240):CvtColor(w,h,0){};
  ~CvtColorBGR2RGB(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_BGR2RGB); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/**********************************************************/
/*                 CONVERSION VERS Lab                  */
/**********************************************************/

/*! \class CvtColorRGB2Lab
 *  \brief this class achieve color image conversion from RGB to Lab
 */
class CvtColorRGB2Lab:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorRGB2Lab(int w=320, int h=240):CvtColor(w,h,1){};
  ~CvtColorRGB2Lab(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_RGB2Lab); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/*! \class CvtColorBGR2Lab
 *  \brief this class achieve color image conversion from BGR to Lab
 */
class CvtColorBGR2Lab:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorBGR2Lab(int w=320, int h=240):CvtColor(w,h,0){};
  ~CvtColorBGR2Lab(){};

  /* conversion function */
  inline void convert(IplImage* imgin, IplImage* imgout) { cvCvtColor(imgin,imgout,CV_BGR2Lab); };
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/**********************************************************/
/*                 CONVERSION VERS rgbN                   */
/**********************************************************/

/*! \class CvtColorRGB2rgbN
 *  \brief this class achieve color image conversion from RGB to rgbN
 */
class CvtColorRGB2rgbN:public CvtColor
{
 public:

  /* constructor */
  CvtColorRGB2rgbN(int w=320, int h=240);
  ~CvtColorRGB2rgbN();

  /* conversion function */
  void convert(IplImage* imgin, IplImage* imgout);
  void convert(IplImage* imgin, IplImage* s1out, IplImage* s2out, IplImage* s3out);
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/**********************************************************/
/*                 CONVERSION VERS Irg                    */
/**********************************************************/

/*! \class CvtColorRGB2Irg
 *  \brief this class achieve color image conversion from RGB to Irg
 */
class CvtColorRGB2Irg:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorRGB2Irg(int w=320, int h=240);
  ~CvtColorRGB2Irg();

  /* conversion function */
  void convert(IplImage* imgin, IplImage* imgout);
  void convert(IplImage* imgin, IplImage* s1out, IplImage* s2out, IplImage* s3out);
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/*! \class CvtColorBGR2Irg
 *  \brief this class achieve color image conversion from BGR to Irg
 */
class CvtColorBGR2Irg:public CvtColor
{
 public:

  uchar tblI[256][256][256];
  uchar tblr[256][256][256];
  uchar tblg[256][256][256];


  /* constructor */
  CvtColorBGR2Irg(int w=320, int h=240);
  ~CvtColorBGR2Irg();

  /* conversion function */
  void convert(IplImage* imgin, IplImage* imgout);
  void convert(IplImage* imgin, IplImage* s1out, IplImage* s2out, IplImage* s3out);
  //  void convert2(IplImage* imgin, IplImage* imgout);
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/**********************************************************/
/*                 CONVERSION VERS I1I2I3                  */
/**********************************************************/

/*! \class CvtColorRGB2I1I2I3
 *  \brief this class achieve color image conversion from RGB to I1I2I3
 */
class CvtColorRGB2I1I2I3:public CvtColor
{
 public:
  
  /* constructor */
  CvtColorRGB2I1I2I3(int w=320, int h=240);
  ~CvtColorRGB2I1I2I3();

  /* conversion function */
  void convert(IplImage* imgin, IplImage* imgout);
  void convert(IplImage* imgin, IplImage* s1out, IplImage* s2out, IplImage* s3out);
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

/*! \class CvtColorBGR2Irg
 *  \brief this class achieve color image conversion from BGR to Irg
 */
class CvtColorBGR2I1I2I3:public CvtColor
{
 public:

  uchar tblI[256][256][256];
  uchar tblr[256][256][256];
  uchar tblg[256][256][256];


  /* constructor */
  CvtColorBGR2I1I2I3(int w=320, int h=240);
  ~CvtColorBGR2I1I2I3();

  /* conversion function */
  void convert(IplImage* imgin, IplImage* imgout);
  void convert(IplImage* imgin, IplImage* s1out, IplImage* s2out, IplImage* s3out);
  //  void convert2(IplImage* imgin, IplImage* imgout);
  inline void convert2(IplImage* imgin, IplImage* imgout) { convert(imgin,imgout); };
};

#endif
