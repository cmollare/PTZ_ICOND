#ifndef PARAMSRANGE_H
#define PARAMSRANGE_H

#include <iostream>
#include <string>
using std::string;

#define NBMAXPARAMSRANGE 10

template<class T>
class ParamsRange
{
 public:

  /* nombre de parametres */
  int nbparams;

  /* labels des parametres */
  string labels[NBMAXPARAMSRANGE];

  /* borne min des parametres */
  T min_bound[NBMAXPARAMSRANGE];

  /* borne max des parametres */
  T max_bound[NBMAXPARAMSRANGE];

  /* delta des bornes max-min */
  T delta_bound[NBMAXPARAMSRANGE];

  ParamsRange();
  ~ParamsRange();

  /* ajout d'un parametre dans la liste */
  int add(string lb, T min, T max);
  
  /* Met a jour les bornes du label lb */
  int update(string lb, T min, T max);

  /* check d'un parametre idp avec la valeur val */
  int check(int idp, T val);

  /* recuperation des bornes */
  inline T getMin(int idp) { return this->min_bound[idp]; };
  inline T getMax(int idp) { return this->max_bound[idp]; }; 
  inline T getDelta(int idp) { return this->delta_bound[idp]; };

  /* affiche les parametres avbec leur bornes */
  void disp();

  /* operateur = */
  ParamsRange<T> & operator=(const ParamsRange<T> &source);

};

template<class T>
ParamsRange<T>::ParamsRange()
{
  this->nbparams = 0;
}


template<class T>
ParamsRange<T>::~ParamsRange()
{
  //cout << "Destruction de PRanges" << endl;

}

/* ajout d'un parametre dans la liste */
template<class T>
int ParamsRange<T>::add(string lb, T min, T max)
{
  if(this->nbparams<NBMAXPARAMSRANGE)
    {
      this->labels[this->nbparams] = lb;
      this->min_bound[this->nbparams] = min;
      this->max_bound[this->nbparams] = max;
      this->delta_bound[this->nbparams] = max-min;
      this->nbparams++;
      return 1;
    }
  else 
    {
      cout << "|ERROR|--> ParamsRange (add) \t:\t Not enought space to store this param bound you must increase NBMAXPARAMSRANGE in paramsrange.h" << endl;
      return 0;
    }
}

template<class T>
int ParamsRange<T>::update(string lb, T min, T max)
{
  int i=0;
  while( (i<this->nbparams) && (this->labels[i]!=lb) ) i++;

  if(i<this->nbparams)
    {
      this->min_bound[i] = (min > this->min_bound[i]) ? min : this->min_bound[i];
      this->max_bound[i] = (max < this->max_bound[i]) ? max : this->max_bound[i];
      this->delta_bound[i] = this->max_bound[i]-this->min_bound[i];
    }
  else cout << "|ERROR|--> ParamsRange (update) \t:\t Update impossible car label non trouve\n";
  return 1;
}

/* check d'un parametre idp avec la valeur val */
template<class T>
int ParamsRange<T>::check(int idp, T val)
{
  //cout << "Checking param " << idp << " = " << val << " with range = [ " << this->min_bound[idp] << " ... " << this->max_bound[idp] << " ]" <<endl;
  return (val > this->min_bound[idp]) ? ( (val < this->max_bound[idp]) ? 1 : 0 ) : 0;
}

template<class T>
ParamsRange<T> &ParamsRange<T>::operator=(const ParamsRange<T> &source)
{
  this->nbparams = source.nbparams;

  for(int i=0;i<this->nbparams;i++)
    {
      this->labels[i] = source.labels[i];
      this->min_bound[i] = source.min_bound[i];
      this->max_bound[i] = source.max_bound[i];
      this->delta_bound[i] = source.delta_bound[i];
    }
    return *this;
}


/* affiche les parametres avbec leur bornes */
template<class T>
void ParamsRange<T>::disp()
{
  cout << "Parameters Bounds" << endl << "Labels\t\tmin\tmax" << endl;
  for(int i=0;i<this->nbparams;i++)
    cout << this->labels[i] << "\t\t" << this->min_bound[i] << "\t" << this->max_bound[i] << endl;
}

template<class T>
inline ostream & operator << (ostream & os, ParamsRange<T> &pr)
{
  pr.disp();
  return os ;
}

template<class T>
inline istream & operator >> (istream & is, ParamsRange<T> &pr) 
{
  string labeltmp;
  T mintmp, maxtmp;
  is >> labeltmp;
  is >> mintmp;
  is >> maxtmp;
  pr.add(labeltmp,mintmp,maxtmp);
  return is ;
}

#endif
