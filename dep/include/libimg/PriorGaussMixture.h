#ifndef PRIORGAUSSMIXTURE_H
#define PRIORGAUSSMIXTURE_H

#include "Prior.h"
#include "GaussianMixture.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 *  Definition d'un prior gaussien
 * TCP type des parametres continus
 * TW type des evaluations
 */
class PriorGaussMixture: public Prior
{
 public:
  
  GaussianMixture* gmPrior;

  PriorGaussMixture(string nomfic);
  ~PriorGaussMixture();

  int Load(string nomfic);
  void Draw(Sample* s);
  void Draw(double* mm, Sample* s);
  double Eval(Sample* s);
  void Disp();

  inline void getMean(double* m) { memcpy(m,gmPrior->getMean(),sizeof(double)*gmPrior->dim); };
  inline double* getMean() { return gmPrior->getMean(); };

};
#endif
