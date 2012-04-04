/***************************************************************************
                          bspline2d.h  -  description
                             -------------------
    begin                : Thu Jul 25 2002
    copyright            : (C) 2002 by Paulo Menezes
    email                : pm@deec.uc.pt
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef BSPLINE2D_H
#define BSPLINE2D_H

#include "def_bspline.h"


/**Class to manage the 2D bsplines
  *@author Paulo Menezes
  */

class BSpline2D {
public: 
  BSpline2D(int deg, int nknots, double * inknots, Point2D * pts);
  ~BSpline2D();
  

  CvPoint *pts;
  Point2D * points;
  int numpoints;
  Vector2D * normals;
  /** Number of points to generate for each interval */
  int density;

  CvPoint Posmin,Posmax;


  /* Nombre de parties correspondant a la spline */
  int nbparts;

  /* Nombre de pts de ctrl par partie */
  int *nbctrlpts_bypart;
  
  /* Liste des numeros de pts de ctrl par partie */
  int **numctrlpts_bypart;
  
  /* Nombre de configurations */
  int nbconfigs;
  
  /* Nombre de pts de ctrl par config */
  int *nbctrlpts_byconfig;  
  
  /* Liste de configs (suite de num de pts de ctrl) construite a partir des configs decrites  */
  int * liste_configs;
  
  /* Description des config (associations de parties de la forme) */
  int **configs_description;
  

  

protected: // Protected attributes
  /**  */
  int degree;
  /**  */
  int knot_nr;
  /**  */
  double * knots;
  /**  */
  Point2D * controlpts;
  Point2D * controlpts2;
  CvPoint *ctrlpts;

  double *coeffx;  /* might need adjustment! */
  double *coeffy;

public: // Public methods
  /** No descriptions */
  void genpoints();

  /** For each of the generated points it creates a vector that is normal to the spline */
  void gennormals();
  /** this method generates new control points translating, rotating and scaling the base ones  */
  void transform(double x, double y, double theta, double scale);
  /** Draws the spline with the current transformation on the image */
  void draw(IplImage * img, CvScalar color,int fill=0);
  void draw_normals(IplImage * img,int size,CvScalar color);
  void draw_parts(IplImage * img);
  void draw_mask(IplImage * img);
  void draw_ctrlpoints(IplImage * img,CvScalar color);
  void draw_ctrlpoints_old(IplImage * img,CvScalar color);

  void DrawMask(IplImage *img);

  /** No descriptions */
  inline Point2D deboor2D(double u, int interval);
private: // Private attributes
  /** number of intervals in the spline
 */
  int intnum;
};

#endif
