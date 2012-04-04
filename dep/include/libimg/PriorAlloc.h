#ifndef PRIORALLOC_H
#define PRIORALLOC_H

#include <string>
#include <iostream>
using namespace std;
#include "Prior.h"
#include "PriorGauss.h"
#include "PriorGaussMixture.h"
#include "externParams.h"

/*
  ATTENTION POUR GARDER LA COHERENCE IL FAUT S'ASSURER QUE LES DEFINE SUIVANTS SOIENT DANS LE MEME ORDRE
  QUE LA LISTE DES CAS CONTENUS DANS LE FICHIER PriorList.txt
*/
#define PRIORGAUSS 0
#define PRIORGAUSSMIX 1

/* Fonction qui retourne un objet prior selon le choix */
inline Prior* PriorAlloc(int choix, string file)
{
  Prior* newP;
  switch(choix)
    {
    case PRIORGAUSS: 
      {
	cout << "--> PriorAlloc \t:\t Gaussian prior allocation ... " << endl;
	newP = new PriorGauss(file);
      }
      break;

    case PRIORGAUSSMIX:
      {
	cout << "--> PriorAlloc \t:\t Gaussian mixture prior allocation ... " << endl;
	newP = new PriorGaussMixture(file);
      }
      break;

    default:
      {
	cout << "|ERROR|--> PriorAlloc \t:\t Bad prior number !!!!" << endl;
	newP = NULL;
      }
    }

  /* mise a jour du numero identifiant le type de prior */
  if(newP) newP->priorID = choix;

  return newP;
}

/* Fonction qui retourne un objet prior selon le choix */
inline Prior* PriorAlloc(string file)
{
  ifstream fichier;
  string tmp;
  
  fichier.open(file.c_str(), ios::in);
  if(!fichier)
    {
      cout << "|ERROR|--> PriorAlloc \t:\t Opening file [" << file << "] ERROR" << endl;
      return 0;
    }
  
  /* lecture du type de dynamique a charger */
  FindStr(fichier,"<PriorType>");
  if(fichier.eof()) { cout << "|ERROR|--> PriorAlloc \t:\t <PriorType> not found" << endl; return 0;}
  fichier >> tmp;
  
  /* fermeture du fichier */
  fichier.close();
  
  /* selection du type de dynamique */
  PriorType = tmp;

  /* Construction à partir du PriorType contenu dans le fichier */
  return PriorAlloc(PriorType.i(), file);
}


#endif
