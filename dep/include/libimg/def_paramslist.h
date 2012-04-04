#ifndef DEF_PARAMSLIST_H
#define DEF_PARAMSLIST_H

#include "paramslist.h"
#include "paramsrange.h"
#include <fstream>
using namespace std;

/* Liste des options possibles pour les differents traitements */
ParamsList ContDynamicType(icuConfigPath+"/objectslist/ContDynamicList.txt");
ParamsList DiscDynamicType(icuConfigPath+"/objectslist/DiscDynamicList.txt");
ParamsList PriorType(icuConfigPath+"/objectslist/PriorList.txt");
ParamsList twoDDetectorType(icuConfigPath+"/objectslist/twoDDetectorList.txt");
ParamsList TargetType(icuConfigPath+"/objectslist/TargetList.txt");
ParamsList ColorBaseType(icuConfigPath+"/objectslist/ColorBaseList.txt");

/* dimensions des images traitees */
int img_width=320;
int img_height=240;

/* Pour logger les infos */
string ficlog = "infos.txt";
ofstream logout;

#endif
