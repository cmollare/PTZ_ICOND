#ifndef CVWRAP_H
#define CVWRAP_H

#include <cv.h>

/* Templates permettant l'acces a certaines donnees de structures
   opencv en specialisant selon le type (ex acces aux datas d'une
   matrice dont le type n'est instancie qu'a la compilation */

template<typename T>
struct mat_cell;

template<> struct mat_cell<float>
{
  static const int cv_type = CV_32F;
  static float* get_data(CvMat* mat)
  { return mat->data.fl; }
};

template<> struct mat_cell<double>
{
  static const int cv_type = CV_64F;
  static double* get_data(CvMat* mat)
  { return mat->data.db; }
};

template<> struct mat_cell<uchar>
{
  static const int cv_type = CV_8U;
  static uchar* get_data(CvMat* mat)
  { return mat->data.ptr; }
};
#endif
