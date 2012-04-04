#ifndef CONTDYNAMICALLOC_H
#define CONTDYNAMICALLOC_H

#include <string.h>
using std::string;

/********************************************************************************/
/* Je laisse seulement RW pour le moment car pas besoin des autres sur le robot */
/********************************************************************************/

//#include "ContDynamicMonoAR.h"
//#include "ContDynamicMultiAR.h"
//#include "ContDynamicXXDot.h"
//#include "ContDynamicMultiXXDot.h"
#include "ContDynamicRW.h"
#include "externParams.h"

// #define MONOAR 0
// #define MULTIAR 1
// #define XXDOT 2
// #define MULTIXXDOT 3
#define RW 0

/*
 *  Fonction qui permet d'allouer un des modeles de dynamique
 */
inline ContDynamicModel* ContDynamicAlloc(int choix, string file)
{
  ContDynamicModel* newDyn;

  switch(choix)
    {
//     case MONOAR:
//       {
// 	return new ContDynamicMonoAR<S,TCP,TW>(file,dispdec);
//       }
//       break;
//     case MULTIAR:
//       {
// 	return new ContDynamicMultiAR<S,TCP,TW>(file,dispdec);
//       }
//       break;

//     case XXDOT:
//       {
// 	return new ContDynamicXXDot<S,TCP,TW>(file,dispdec);
//       }
//       break; 
    
//     case MULTIXXDOT:
//       {
// 	return new ContDynamicMultiXXDot<S,TCP,TW>(file,dispdec);
//       }
//       break;

    case RW:
      {
	newDyn = new ContDynamicRW(file);
      }
      break;

    default :
      {
	cout << "|ERROR|--> ContDynamicAlloc \t:\t Bad dynamic number !!!!" << endl;
	newDyn = NULL;
      }
    }

  /* Mise a jour de l'ID de la dynamique */
  newDyn->dynamicID = choix;

  return newDyn;
}

inline ContDynamicModel* ContDynamicAlloc(string file)
{
  ifstream fichier;
  string tmp;
 
  fichier.open(file.c_str(), ios::in);
  if(!fichier)
    {
      cout << "|ERROR|--> ContDynamicAlloc \t:\t Opening file [" << file << "] ERROR" << endl;
      return 0;
    }
  
  /* lecture du type de dynamique a charger */
  FindStr(fichier,"<ContDynamicType>");
  if(fichier.eof()) { cout << "|ERROR|--> ContDynamicAlloc \t:\t <ContDynamicType> not found" << endl; return 0;}
  fichier >> tmp;

  /* fermeture du fichier */
  fichier.close();

  /* selection du type de dynamique */
  ContDynamicType = tmp;

  return ContDynamicAlloc(ContDynamicType.i(),file);
}
#endif
