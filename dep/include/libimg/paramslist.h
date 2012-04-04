#ifndef PARAMSLIST_H
#define PARAMSLIST_H

#include <string>
#include <iostream>
#include <fstream>
using std::string;
using namespace std;

#define NBMAXPARAMS 20

class ParamsList
{
private:
  
  /* the number of parameters that can be stored */
  int nbparams;

  /* number of added params */
  int nb;
  
  /* string list */
  string* strlist;//[NBMAXPARAMS];

  /* current selected index */
  int curselected;

  /* decalage a utiliser pour indiquer la position d'un parametre */
  int offset;

public:
  ParamsList(int offset=0);
  ParamsList(string nomfic);
  ParamsList(ParamsList const& pl); 

  ~ParamsList();

  inline void reset() { this->nb = 0; this->curselected = 0; };

  /* return the number of parameters */
  inline int getnb() { return this->nb; };

  /* return the equivalent index for a given string */
  int getIndex(string str); 
  int getIndexWithOffset(string str);

  /* offset acces */
  inline void setOffset(int ofs) { this->offset = ofs; };
  inline int getOffset() { return this->offset; };
  
  /* return the equivalent index for a given string */
  inline int getSelectedIndex() { return this->curselected; };

  /* return the string associated to a given index */
  inline string getStr(int id){ return strlist[id]; };

  /* return the string associated to a given index */
  inline string getSelectedStr(){ if(this->nb) return this->strlist[this->curselected]; };

  inline int i() { return this->curselected; };
  inline string s() { return this->strlist[this->curselected]; };
  inline const char* c() { return (this->strlist[this->curselected]).c_str(); };

  /* add new string in the list */
  int add(string str);
  int add(char* str);
  
  /* overload operators */
  ParamsList &operator=(const int id);
  ParamsList &operator=(const string str);
  ParamsList &operator=(const char* chaine);
  ParamsList &operator=(ParamsList const& pl); 

  bool operator==(int n) const;
  bool operator==(string str) const; 
  bool operator==(char* chaine) const;

   void Disp();
  void DispStrList();

  void Load(string nomfic);
};

ostream & operator << (ostream & os, ParamsList &pl);
istream & operator >> (istream & is, ParamsList &pl);

#endif
