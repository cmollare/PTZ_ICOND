#ifndef MULTIBSPLINE2D_H
#define MULTIBSPLINE2D_H

#include "def_bspline.h"

/**Class to manage the 2D bsplines
   and a set of splines parts to combime various configurations1
  *@author Ludovic Brethes
  */

class MultiBSpline2D {
public: 
  //MultiBSpline2D(const char *ficspline, const char *ficconfig);
  MultiBSpline2D(char *ficspline, char *ficconfig);
  MultiBSpline2D(int deg, int nknots, double * inknots, Point2D * pts);
  ~MultiBSpline2D();
  

  /* Liste des points generes = points de la forme */
  Point2D * points;

  /* Nombre de points (trace) de la forme */
  int numpoints;

  /* Liste de vecteurs normaux */
  Vector2D * normals;
  /** Number of points to generate for each interval */
  int density;
  
  /* Points definissant le rectangle englobant */
  CvPoint Posmin,Posmax,PosminGlobal,PosmaxGlobal;

  /* Nombre de parties correspondant a la spline */
  int nbparts;

  /* Nombre de pts de ctrl par partie */
  int *nbctrlpts_bypart;
  
  /* Liste des numeros de pts de ctrl par partie */
  int **numctrlpts_bypart;
  
  /* Nombre de points de ctrl par masque */
  int *nbctrlpts_bymask;

  /* Liste des points de ctrl du masque de chaque partie */
  int **numctrlpts_bymask;

  /* Nombre de configurations */
  int nbconfigs;
  
  /* Nombre parties par configuration */
  int *nbparts_byconfig;  

  /* Enchainement des parties par config */
  int **numparts_byconfig;
  
  /* Liste des nombres de pts de ctrl par config */
  int *nbctrlpts_byconfig;

  /* Liste des numeros de pts de ctrl par config */
  int **numctrlpts_byconfig;

  /* Tableau indiquant pour chaque configuration
     si une partie fait ou non partie de la config */
  int **ispart_byconfig;
  
  /* choix du rectangle englobant sur une partie si ==-1 alors rectangle englobant de la forme complete
   sinon on detecte le rectangle englobant de la partie designee */
  int numenglob;

 protected: // Protected attributes
  /**  */
  int degree;
  /**  */
  int knot_nr;
  /**  */
  double * knots;
  /**  Points de controle d'origine */
  Point2D * controlpts_init;
  /** Points de controle apres transformation */ 
  CvPoint * controlpts_trans;
  /** Points utilises pour le trace des regions dans le trace du masque */
  CvPoint *controlpts_draw;
  /* Liste de points pour le trace */
  CvPoint *pts;

  double *coeffx;  /* might need adjustment! */
  double *coeffy;

 public: // Public methods
  /** No descriptions */
  void genpoints();

  /** For each of the generated points it creates a vector that is normal to the spline */
  void gennormals();
  /** this method generates new control points translating, rotating and scaling the base ones  */
  void transform(double x, double y, double theta, double scale, int model=0);
  /** Draws the spline with the current transformation on the image */
  void draw(IplImage * img, CvScalar color,int fill=0,int epaisseur=2);
  
  void draw_rect(IplImage *img,CvScalar color,int epaisseur=2);
  void draw_rect_mask(IplImage *img);
  void draw_global_rect(IplImage *img,CvScalar color=CV_RGB(255,255,255));
  void draw_global_rect_mask(IplImage *img);
  void draw_normals(IplImage * img,int size,CvScalar color,int epaisseur=2);

/* Trace de tous les masques avec comme label le numero de masque + 1*/
  void draw_mask(IplImage * img);
/* Trace de tous les masques en fausse couleur */
  void draw_mask_fcol(IplImage * img);
/* Trace d'un masque dans l'image avec comme couleur le numero de masque + 1 */
  void draw_one_mask(IplImage * img,int masknum);
/* Trace d'un masque dans l'image en fausse couleur */
  void draw_one_mask_fcol(IplImage * img,int masknum);
  void draw_ctrlpoints(IplImage * img,CvScalar color);
  void DrawMask(IplImage *img);

  /** No descriptions */
  inline Point2D deboor2D(double u, int interval);

  //void LoadSpline(const char *fichier);
  //void LoadConfig(const char *fichier);

  void LoadSpline(char *fichier);
  void LoadConfig(char *fichier);

/* Generation des configurations a partir des points de controle charges et d'apres la description */
  void genconfigs();

  void draw_all_regions_fcol(IplImage * img);
  void draw_all_regions(IplImage * img);

private: // Private attributes
  /** number of intervals in the spline
 */
  int intnum;
};

#endif
