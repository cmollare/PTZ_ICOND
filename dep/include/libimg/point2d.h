/***************************************************************************
                          point2d.h  -  description
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

#ifndef POINT2D_H
#define POINT2D_H

#include "def_bspline.h"

class Vector2D; // forward class declaration
/**
  *@author Paulo Menezes
  */

class Point2D 
{
 public: 
  Point2D();
  Point2D(double ix,double iy);
  ~Point2D();
  /** No descriptions */
  
  friend Vector2D  operator - (const Point2D &a,const Point2D & b);
  inline double x(){return myx;}
  inline double y(){return myy;}
  /** multiply a point by a scalar */
  friend  Point2D operator *(const Point2D&,const double&);
  /** translate a point */
  Point2D operator +(const Point2D &pt);
   /** Rotate around origin */
  void rotate(double angle);
  void rotate(double angle, double xc, double yc);
  void rotate(double angle,Point2D pt);

  /** multiply a point by a scalar */
  friend Point2D operator*(const double& a,const Point2D &b);

  //protected: // Protected attributes
  /**  */
  double myx;
  double myy;
  
};

/**Based on the 2d point class this one provides manipulation of 2d vectors
 *@author Paulo Menezes
 */

class Vector2D : public Point2D  {
public:
	Vector2D(double ix=0,double iy=0):Point2D(ix,iy){};
	~Vector2D();
	/** returns a vector that is normal to the input one */
	Vector2D normal();
	
	
};


#endif
