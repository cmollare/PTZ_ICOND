#ifndef TEMPS_CPU_H
#define TEMPS_CPU_H

/**************************************************************************************/
/* Adapte par Ludovic Brethes simplement pour l'utiliser comme librairie de fonctions */
/**************************************************************************************/

// Visual C++ : Définit _Windows
#if defined(_MSC_VER)
#  define _Windows
#endif

#include <stdio.h>
#ifdef linux
#  include <unistd.h>
#  include <string.h>
#  include <stdlib.h>
#  define NOMFICH_CPUINFO "/proc/cpuinfo"
#elif defined(_Windows)
#  include <windows.h>
#endif

//---------------------------------------------------------------------------

#if defined(_Windows)

// Définit les types uint32 et uint64 sous Windows
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;

// Définit le convertion uint64 vers double
double uint64_to_double (const uint64 x)
{
#if defined(_MSC_VER)
  // Petit hack pour convertir du 64 bits en double
  // Ce hack dépend de l'endian (ici ça marche sur Intel x86)
  typedef uint32 uint64_32[2];
  uint64_32 *hack = (uint64_32 *)&x;
  double dbl;

  dbl  = (*hack)[1];
  dbl *= 4294967296;
  dbl += (*hack)[0];

  return dbl;
#else
  return (double)x;
#endif
}

#endif

double RDTSC(void);
void AfficheFrequence (double frequence);
int LitFrequenceCpu (double* frequence);
void get_time_start();
double get_time_stop(int disp=1);
void pause(int nbms);


//---------------------------------------------------------------------------
#endif
