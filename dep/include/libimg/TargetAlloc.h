#ifndef TARGETALLOC_H
#define TARGETALLOC_H

#include <string>
#include <iostream>
using namespace std;

#include "externParams.h"
#include "Target.h"
#include "TargetICU.h"

/*
  ATTENTION POUR GARDER LA COHERENCE IL FAUT S'ASSURER QUE LES DEFINE SUIVANTS SOIENT DANS LE MEME ORDRE
  QUE LA LISTE DES CAS CONTENUS DANS LE FICHIER TargetList.txt
*/
#define ICU 0

/* Fonction qui retourne un objet prior selon le choix */
inline Target* TargetAlloc(int choix, string file, ImgProducer* imgBank=NULL, 
			   twoDDetector* detector=NULL, Prior* prior=NULL, 
			   ContDynamicModel* ContDynamic=NULL, DiscDynamicModel** DiscDynamic=NULL)
{
  Target* newT;
  switch(choix)
    {
    case ICU: 
      {
	cout << "--> TargetAlloc \t:\t ICU Target allocation ... " << endl;
	newT = new TargetICU(file,imgBank,detector,prior,ContDynamic,DiscDynamic);
      }
      break;

    default:
      {
	cout << "|ERROR|--> TargetAlloc \t:\t Bad target number !!!!" << endl;
	newT = NULL;
      }
    }

  /* mise a jour du numero identifiant le type de prior */
  if(newT) newT->targetID = choix;

  return newT;
}

/* Fonction qui retourne un objet prior selon le choix */
inline Target* TargetAlloc(string file, ImgProducer* imgBank=NULL, twoDDetector* detector=NULL, Prior* prior=NULL, 
			   ContDynamicModel* ContDynamic=NULL, DiscDynamicModel** DiscDynamic=NULL)
{
  ifstream fichier;
  string tmp;
  
  fichier.open(file.c_str(), ios::in);
  if(!fichier)
    {
      cout << "|ERROR|--> TargetAlloc \t:\t Opening file [" << file << "] ERROR" << endl;
      return 0;
    }
  
  /* lecture du type de dynamique a charger */
  FindStr2(fichier,"<TargetType>");
  if(fichier.eof()) { cout << "|ERROR|--> TargetAlloc \t:\t <TargetType> not found" << endl; return 0;}
  fichier >> tmp;
  
  /* fermeture du fichier */
  fichier.close();
  
  /* selection du type de dynamique */
  TargetType = tmp;

  /* Construction à partir du PriorType contenu dans le fichier */
  return TargetAlloc(TargetType.i(),file,imgBank,detector,prior,ContDynamic,DiscDynamic);
}
#endif
