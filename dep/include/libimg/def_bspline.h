#ifndef DEF_BSPLINE_H
#define DEF_BSPLINE_H

//Nombre de points  max pour trace spline
#define NBMAXPTS 1000

inline int cmp(const void* a, const void* b)
{
  return ( *(int*)a - *(int*)b );
}

#endif

#include <cv.h>

#include <stdio.h>
#include <iostream>
using namespace std;
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "point2d.h"
#include "calclut.h"
#include "stringutils.h"

