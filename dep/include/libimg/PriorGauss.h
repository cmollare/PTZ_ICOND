#ifndef PRIORGAUSS_H
#define PRIORGAUSS_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Prior.h"
#include "GaussianAlloc.h"

/*
 *  Definition d'un prior gaussien
 */
class PriorGauss: public Prior
{
 public:
  
  Gaussian* gPrior;

  PriorGauss(string nomfic);
  ~PriorGauss();

  int Load(string nomfic);
  void Draw(Sample* s);
  void Draw(double* mm, Sample* s);
  double Eval(Sample* s);
  void Disp();

  inline void getMean(double* m) { memcpy(m,gPrior->mean,sizeof(double)*gPrior->dim); };
  inline double* getMean() { return gPrior->mean; };
};
#endif
