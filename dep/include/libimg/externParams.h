#ifndef EXTERPARAMS_H
#define EXTERPARAMS_H

#include "paramslist.h"
#include "paramsrange.h"

/************************* Ce fichier contient l'ensemble des declarations externes *********************************/


/* chemin vers les repertoires de configuration */
extern string icuConfigPath;

/* liste des parametres disponibles pour les differents objets */
extern ParamsList ContDynamicType;
extern ParamsList DiscDynamicType;
extern ParamsList PriorType;
extern ParamsList twoDDetectorType;
extern ParamsList TargetType;
extern ParamsList ColorBaseType;

extern int img_width;
extern int img_height;

extern string ficlog;
extern ofstream logout;

#endif
