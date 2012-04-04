#ifndef CVTCOLORALLOC_H
#define CVTCOLORALLOC_H

#include "cvtcolor.h"
#include "constparams.h"

/* Fonction d'allocation d'un objet convertisseur de couleur */
inline
CvtColor* CvtColorAlloc(int from, int choix, int w, int h)
{
  cout << "--> CvtColorAlloc \t:\t Color converter allocation with image size = " << w << " x " << h << endl;
  switch(from)
    {
    case baseRGB:
      {
	switch(choix)
	  {
	  case baseYCrCb : return new CvtColorRGB2YCrCb(w,h);
	  case baseHSV   : return new CvtColorRGB2HSV(w,h);
	  case baseLab   : return new CvtColorRGB2Lab(w,h);
	  case basergbN  : return new CvtColorRGB2rgbN(w,h);
	  case baseIrg  : return new CvtColorRGB2Irg(w,h);
	  case baseBGR :return new CvtColorRGB2BGR(w,h);
	  default : return NULL;
	  }
      }
      break; 

    case baseBGR:
      {
	switch(choix)
	  {
	  case baseYCrCb : return new CvtColorBGR2YCrCb(w,h);
	  case baseHSV   : return new CvtColorBGR2HSV(w,h);
	  case baseLab   : return new CvtColorBGR2Lab(w,h);
	  case basergbN  : return new CvtColorRGB2rgbN(w,h);
	  case baseIrg  : return new CvtColorBGR2Irg(w,h);
	  case baseRGB :return new CvtColorBGR2RGB(w,h);
	  default : return NULL;
	  }
      }
      break;
    default : return NULL;
    }
}

inline CvtColor* CvtColorAlloc(int from, int choix, double factor, int w=320, int h=240)
{ return CvtColorAlloc(from,choix,(int)(w*factor),(int)(h*factor)); }

#endif
