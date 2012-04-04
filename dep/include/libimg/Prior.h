#ifndef PRIOR_H
#define PRIOR_H

#include <string.h>
using namespace std;

#include "Sample.h"

class Prior	
{
public:
  
  /* Identifiant du prior */
  int priorID;

  Prior()
  {
    //Pas d'operation
    cout << "Construction de Prior" << endl;
    this->priorID = -1;
  };

  virtual ~Prior()
  {
    cout << "Destruction de Prior" << endl;
  };  

  virtual int Load(string nomfic)=0;
  virtual void Draw(Sample* s)=0;
  virtual void Draw(double* mm, Sample* s)=0;
  virtual double Eval(Sample* s)=0;
  virtual void Disp()=0;
  virtual void getMean(double* m)=0;
  virtual double* getMean()=0;
};
#endif
