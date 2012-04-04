#ifndef DISPLAYUTILS_H
#define DISPLAYUTILS_H

#include <cv.h>
#include <highgui.h>
#include "calclut.h"

/* Affichages divers en utilisant opencv */

void Show( char* nm,IplImage* imgview, int pause);
void Show( char* nm,IplImage* imgview, int x, int y, int pause);
void DispIma(IplImage *img, char *fen, int pause);
void DispIma(IplImage *img, char *fen, int x, int y,int pause);
/** Affichage d'une image en fausse couleur **/
void DispFcol(IplImage *img, char *fen);
void DispResizedFcol(IplImage *img, char *fen,int height, int width);

#endif
