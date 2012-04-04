#ifndef COLORBASE_H
#define COLORBASE_H

#include <iostream>
#include <fstream>
#include <string>
using std::string;
using namespace std;

#include "stringutils.h"
#include "externParams.h"


/*! \class ColorBase 
 *  \brief this is a class that manage color base and associated parameters
 */
class ColorBase
{
public:

  /* numero de base */
  int num;

  /* nom de la base */
  string nm;

  /* numero du plan contenant la luminance */
  int pLum;

  /* bornes luminance */
  int* LumR;

  /* bornes luminance */
  int* ChromR1;
  int* ChromR2;

  /* bornes des plans */
  int rC1[2];
  int rC2[2];
  int rC3[2];

  /* dimensions des plans */
  int dimC1;
  int dimC2;
  int dimC3;

  /* dimensions luminance et chrominance */
  int* dimLum;
  int* dimChrom1;
  int* dimChrom2;

  ColorBase();
  ColorBase(string nomfic);
  ~ColorBase();

  int load(string nomfic);
  void disp();

  inline int rC1min() { return this->rC1[0]; };
  inline int rC1max() { return this->rC1[1]; };
  inline int rC2min() { return this->rC2[0]; };
  inline int rC2max() { return this->rC2[1]; };
  inline int rC3min() { return this->rC3[0]; };
  inline int rC3max() { return this->rC3[1]; };

  inline int getLumRmin() { return this->LumR[0]; };
  inline int getLumRmax() { return this->LumR[1]; };
  inline int getChrom1Rmin() { return this->ChromR1[0]; };
  inline int getChrom1Rmax() { return this->ChromR1[1]; };
  inline int getChrom2Rmin() { return this->ChromR2[0]; };
  inline int getChrom2Rmax() { return this->ChromR2[1]; };

  inline int getdimLum() { return *this->dimLum; };
  inline int getdimChrom1() { return *this->dimChrom1; };
  inline int getdimChrom2() { return *this->dimChrom2; };

  inline int getnum() { return num; };

};
#endif
