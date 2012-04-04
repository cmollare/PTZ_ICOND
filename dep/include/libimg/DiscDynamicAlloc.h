#ifndef DISCDYNAMICALLOC_H
#define DISCDYNAMICALLOC_H

#include <string.h>
using std::string;

#include "DiscDynamicModel.h"
#include "externParams.h"

#define TRANSMAT 0

/*
 *  Fonction qui permet d'allouer un des modeles de dynamique discrete
 */
inline DiscDynamicModel* DiscDynamicAlloc(int choix, int PPos, string file)
{
  DiscDynamicModel* newDiscDyn;

  switch(choix)
    {
    case TRANSMAT:
      {
	newDiscDyn = new DiscDynamicModel(file,PPos);
      }
      break;
    default : 
      {
	cout << "|ERROR|--> DiscDynamicAlloc \t:\t Bad dynamic number !!!!" << endl;
	newDiscDyn = NULL;
      }
    }

  /* Mise à jour de l'id */
  newDiscDyn->discdynID = choix;

  return newDiscDyn;
}

inline DiscDynamicModel* DiscDynamicAlloc(string file)
{
  ifstream fichier;
  string tmp;
  int PPos = 0;
  
  fichier.open(file.c_str(), ios::in);
  if(!fichier)
    {
      cout << "|ERROR|--> DiscDynamicAlloc \t:\t Opening file [" << file << "] ERROR" << endl;
      return 0;
    }
  
  /* lecture du type de dynamique a charger */
  FindStr(fichier,"<DiscDynamicType>");
  if(fichier.eof()) { cout << "|ERROR|--> DiscDynamicAlloc \t:\t <DiscDynamicType> not found" << endl; return 0;}
  fichier >> tmp;

  /* lecture de la position dans le vecteur d'etat discret */
  FindStr(fichier,"<PPos>");
  if(!fichier.eof())
    fichier >> PPos;
  
  /* fermeture du fichier */
  fichier.close();
  
  /* selection du type de dynamique */
  DiscDynamicType = tmp;

  return DiscDynamicAlloc(DiscDynamicType.i(),PPos,file);
}

#endif
