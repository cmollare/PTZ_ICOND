#ifndef BLOBDETECTOR_H
#define BLOBDETECTOR_H


#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

#include "twoDDetector.h"
#include "externParams.h"
#include "constparams.h"

/* Classe qui permet d'extraire des blobs a partir d'une image en niveaux de gris
   par exemple une image de prob couleur peau --> detection de blobs couleur peau
*/
class blobDetector : public twoDDetector
{
public:





};
#endif
