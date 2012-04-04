#ifndef WATERSHED_H
#define WATERSHED_H

/***************************************************/
/* CONTIENT LES CLASSES Watershed2D et Watershed1D */
/***************************************************/ 

#include <iostream>
#include <cv.h>
#include <queue>
#include <deque>
using std::deque;
using namespace std;

/* Classe qui permet de gerer le calcul du partage des eaux sur un tableau 2d
   de type generique */
template<class T>
class Watershed2d
{
private:

  /* Dimensions des tableaux traites */
  int dim1;
  int dim2;
  int size;

  /* dimension pour memcpy */
  int tabSize;

  /* Files d'attentes pour traiter les indices des coordonnees */
  queue<int> niveaux[256];
  queue<int> file;

  /* Vecteur pour le voisinage d'un pixel */
  int voisList[8];

  /* tableau masque de traitement */
  int* tabMask;

  /* Tableau de vecteurs contenant les labels associes aux pixels */
  int** tabLabels;

public:
  
  Watershed2d();

  /* Constructeur avec dimensions des tableaux traites */  
  Watershed2d(int dim1, int dim2);

  /* Destructeur */
  ~Watershed2d();

  void alloc(int dim1, int dim2);

  /* Fonction de normalisation */
  void Normalize(T* tabIn);
  void Normalize(T* tabIn, float coeff);

  /* Fonction utilitaire qui teste si un pixel appartient a une region */
  bool InReg(int pos, int region);

  /* Fonction d'extraction de marqueurs */
  int ExtractMax(T* tabIn, T* tabClustered, queue<int> & picList, double seuil, int seuilpic=0);

  /* Fonction de calcul du partage des eaux */
  void Process(T* tabIn, T* tabClustered, queue<int> & marqueurs, int inverse=1);

  /* Calcule une image en fausse couleur */
  void CalcFcol2d(T* tabClustered, IplImage* imgOut);

};


/* Classe qui permet de gerer le calcul du partage des eaux sur un vecteur 1d
   de type generique */
template<class T>
class Watershed1d
{
private:

  /* Dimensions des tableaux traites */
  int size;

  /* dimension pour memcpy */
  int vectSize;

  /* Files d'attentes pour traiter les indices des coordonnees */
  queue<int> niveaux[256];
  queue<int> file;

  /* vecteur masque de traitement */
  int* vectMask;

  /* Tableau de vecteurs contenant les labels associes aux pixels */
  int** vectLabels;

public:
  
  Watershed1d();

  /* Constructeur avec dimensions des tableaux traites */  
  Watershed1d(int size);

  /* Destructeur */
  ~Watershed1d();

  void alloc(int size);

  /* Fonction de normalisation */
  void Normalize(T* tabIn);
  void Normalize(T* tabIn, float coeff);

  /* Fonction utilitaire qui teste si un pixel appartient a une region */
  inline bool InReg(int pos, int region) 
  { 
    if(this->tabLabels[pos][0]==region || this->tabLabels[pos][1]==region) return true;
    else return false;
  };

  /* Fonction d'extraction de marqueurs */
  inline int ExtractMax(T* vectIn, T* vectClustered, queue<int> & picList, double seuil, int seuilpic) 
  { return  ExtractMax(vectIn,vectClustered,picList,seuil,seuilpic,0); };

  int ExtractMax(T* vectIn, T* vectClustered, queue<int> & picList, double seuil, int seuilpic, int startreg);

  /* Fonction de calcul du partage des eaux */
  void Process(T* vectIn, T* vectClustered, queue<int> & marqueurs, int inverse=1);
};



//#include "watershed.cpp"






template<class T>
Watershed2d<T>::Watershed2d()
{
  cout << "--> Watershed2d (Constructor) \t:\t Construction de watershed sans parametres\n";
}

template<class T>
Watershed2d<T>::Watershed2d(int dim1, int dim2)
{
  cout << "--> Watershed2d (Constructor) \t:\t Construction de watershed " << dim1 << " x " << dim2 << "\n";
  this->alloc(dim1,dim2);
}

template<class T>
void Watershed2d<T>::alloc(int dim1, int dim2)
{
  cout << "--> Watershed2d (alloc) \t:\t Alloc de watershed " << dim1 << " x " << dim2 << "\n";
  this->dim1 = dim1;
  this->dim2 = dim2;
  this->size = dim1*dim2;

  //this->picValList = new T[this->size];
  //for(int i=0;i<this->size;i++) this->picValList[i] = 255;

  this->tabSize = this->size*sizeof(T);

  /* Init des offsets pour acceder aux voisins d'un pixel */
  this->voisList[0] = -this->dim1-1;
  this->voisList[1] = -this->dim1;
  this->voisList[2] = -this->dim1+1;
  this->voisList[3] = -1;
  this->voisList[4] = 1;
  this->voisList[5] = this->dim1-1;
  this->voisList[6] = this->dim1;
  this->voisList[7] = this->dim1+1;

  /* tableau masque de traitement (contient le nb de labels associes) */
  this->tabMask = new int[this->size];
  memset(this->tabMask,0,this->tabSize);

  /* Tableau de labels */
  this->tabLabels = new int*[this->size];
  for(int i=0;i<this->size;i++)
    {
      this->tabLabels[i] = new int[8];
      memset(this->tabLabels[i],0,8*sizeof(int));
    }

}

template<class T>
Watershed2d<T>::~Watershed2d()
{
  //delete [] this->picValList;
  
  delete [] this->tabMask;
  
  for(int i=0;i<this->size;i++)
    delete [] this->tabLabels[i];
  
  delete [] this->tabLabels;
}

/* Nomalisation pour obtenir des valeurs entre 0 et 255 */
template<class T>
void Watershed2d<T>::Normalize(T* tabIn)
{
  float max = 0;
  float coeff;

  for(int i=0;i<this->size;i++)
    if(tabIn[i]>max) max = tabIn[i];
   
  this->Normalize(tabIn,255.0/max);
}

template<class T>
void Watershed2d<T>::Normalize(T* tabIn, float coeff)
{
  for(int i=0;i<this->size;i++)
    tabIn[i] = (T)(tabIn[i]*coeff);
}

/**************************************************************************/
/* Selection des marqueurs pour watershed sur histogramme de chrominance  */
/**************************************************************************/
//Etape 1 : recherche des maximums locaux
//Etape 2 : determination des vallées entre les maximums locaux
//Etape 3 : calcul du contraste pour chaque maximum
//Etape 4 : selection des pics dont le contraste normalisé est > a seuil (cf Article Albiol ICIP01)

//Représentation des données :

/*
     Pour représenter l'appartenance d'un pixel a une ou plusieurs régions si il est en frontière, on va 
  utiliser une matrice de tableaux. Chaque tableau de taille 9 contiendra les labels regions voisines du pixel 
  correspondant a la position de ce tableau dans la matrice, ainsi que le nombre de régions voisines.
     Si un pixel appartient a une seule region, le tableau contient un label en position 1 et en 0 le nbre = 1
      ___________________________________
     |_1_|_8_|_0_|_0_|_0_|_0_|_0_|_0_|_0_|

     Si un pixel est en frontiere de deux ou plus de régions on trouvera le nombre de regions voisines en position 0 
     puis les labels des regions voisines
      ___________________________________
     |_3_|_8_|_6_|_4_|_0_|_0_|_0_|_0_|_0_|

Dans cette version, on utilise un masque qui contient le nombre de regions et le vecteur de labels ne contient que les
labels associes au pixel

     On utilise des files d'attente hiérarchisées pour stocker les coordonnées des pixels de niveau de gris n
 



  A partir de l'image de chrominance (en niveau de gris 256niv):
  
  1/ Parcours de l'image de chrominance :
       Si un pixel p a un niveau de gris ng et ng!= 0 alors on empile ses coordonnées dans file[ng]

       rq : cette étape permet de ne pas par la suite parcourir l'image 256 fois 


  2/ On parcours les files d'attente du niveau 255 a 0
     - Pour chaque points de la file[i]
       * si pixel non traité alors : 
           on lui attribut un nouveau label L
	   on stocke sa valeur comme étant le max de la region de label L
	   on fait un grossissement a partir de ce point (cad on propage les L tant que les voisins sont < au pixel courant)
	   les coordonnées des points appartenant a une meme region sont stockées dans une file de numero = label L

  3/ On traite les pics en partant du pic maximum
         Pour chaque pic P :
	     Si c'est le pic le plus haut son contraste = a sa hauteur
	     Sinon :
	        On cherche les pixels minimums appartenant au pic P et a l'un des pics plus haut que P (precedemment traités)
		On calcule le contraste pour chaque minimum i Ci = H - m   (H = hauteur du pic, m = valeur du minimum) 
                Le contraste du pic = Min(Ci)

   4/ On calcule pour chaque pic le contraste normalizé : Cnorm = C/H
      Les Regions dont Cnorm > seuil sont conservées comme marqueurs pour le watershed

*/
template<class T>
int Watershed2d<T>::ExtractMax(T* tabIn, T* tabClustered, queue<int> & picList, double seuil, int seuilpic)
{
  int pic,pt,vois;
  int nbregions = 0,nb;
  T val,valpix,valvois,nblab;
  double contraste, contrasteNorm;

  /* Init des regions clusterisees */
  memset(tabClustered,0,this->tabSize);

  /* Parcours de l'image et mise dans les files correspondantes
     Sauf le contour */
  for(int pos=0;pos<this->size;pos++)
    {
      val = cvRound(tabIn[pos]);      
      //if(val>255 || val<0) cout << "ERROR " << val << " out of image\n";
      if(val>0) this->niveaux[(int)val].push(pos);
    }

  /* Raz des pixels traites */
  memset(this->tabMask,0,this->tabSize);

  /* Parcours des files d'attentes = parcours des niveaux de gris du max au min
     On cherche ici les pics */
  nb=0;
  nbregions=0;
  for(int i=255;i>0;i--)
    {
      /* Pour chaque file */
      while(!this->niveaux[i].empty())
	{
	  /* Tant que file non vide */
	  pic = this->niveaux[i].front();
	  this->niveaux[i].pop();

	  //if( (pic < 0) || (pic > this->size) ) cout << "ERROR out of tab\n";

	  /* On regarde si le pixel est traite. Si oui, il appartient a une region au moins. Si non, c'est un nouveau pic */	  
	  if( (!tabMask[pic]) && (tabIn[pic] > seuilpic) )
	    {
	      /*
		pixel non traite
		nouvelle region : 
		 - on incremente le nb de regions
	         - on labelise le point
	         - on sauve la valeur du pic
	         - on ajoute dans la file le pt = depart du grossissement
	         - on ajoute le point dans la file correspondant a la region a laquelle il appartient
	      */
	      nbregions++;

	      /* On augmente le nombre de labels associes au pixel */
	      this->tabMask[pic]++;

	      /* On lui affecte le label correspondant a la nouvelle region */
	      this->tabLabels[pic][0] = nbregions;    

	      /* On initialise la liste pour traiter le voisinage de pic */
	      this->file.push(pic);

	      /* Init de contraste a 0 */
	      contraste = 0;

	      /* Grossissement autour du max local (region i) */
	      while(!this->file.empty())
		{
		  /* On recupere un element de la file puis on étend son label aux voisins si valeur <= pixel courant */
		  pt = this->file.front();
		  this->file.pop();

		  /* Recuperation de la valeur du pixel courant */
		  valpix = tabIn[pt];

		  /* On traite les voisins */
		  for(int v=0;v<8;v++)
		    {
		      /* On calcule l'indice du voisin */
		      vois = pt + this->voisList[v];

		      /* 
			 Si hauteur du voisin <= hauteur du pixels et voisin non labelise du label courant :
		         - on étend le label
		         - Si voisin a un seul Label (le precedent) on l'ajoute a la liste des points de la region
		           et on le met dans la file pour le grossissement
		           Sinon on le met dans la liste des points frontière 
		      */		      
		      
		      /* Teste si on est dans le tableau */
		      if( (vois>=0) && (vois<this->size) )
			{
			  /* Recuperation de la valeur du pixel voisin */
			  valvois = tabIn[vois];

			  /* Nombre de labels associes au voisin (indique si il fait partit d'une autre region) */
			  nblab = this->tabMask[vois];
			  
			  /* Si pixel non null et sa valeur est inferieure au pixel courant 
			     et il ne fait pas deja partit de la region alors on ajoute le label */
			  if(valvois && (!this->InReg(vois,nbregions)))
			    {		
			      if(valvois<=valpix)
				{     
				  /* On augmente le nombre de labels associes au pixel */
				  this->tabMask[vois]++;			     

				  /* On lui affecte le label correspondant a la nouvelle region */
				  this->tabLabels[(int)(vois)][(int)(nblab)] = nbregions;
								  
				  /* Si le pixel vient d'etre labelise on l'ajoute a la liste de traitement sinon il
				     appartient a la frontiere entre regions */
				  if(!nblab) this->file.push(vois);
				  else if(valvois>contraste) contraste = valvois;
				}
			    }
			}
		    }
		}

	      /* Calcul du contraste normalise */
	      contrasteNorm = (i-contraste)/i;

	      /* La file est vide, on a donc traite toute la region
		 Region grossie, on calcule le contraste normalisé pour décider si on garde ou non le pic */
	      if( (!contrasteNorm) || (contrasteNorm > seuil) )
		{
		  /* On garde cette region comme marqueur */
		  picList.push(pic);

		  /* On sauvegarde la valeur du pic */
		  //this->picValList[nb] = tabIn[pic];

		  /* On incremente le nombre de regions conservees */
		  nb++;
		  
		  /* On trace dans le tableau de sortie (label a partir de 1 donc apres incrementation de nb) */
		  tabClustered[pic] = nb;		  
		}
	    }
	}
    }
  
  /* On retourne le nombre de pics conserves */
  return nb;
}


template<class T>
  bool Watershed2d<T>::InReg(int pos, int region)
  {
    for(int i=0;i<this->tabMask[pos];i++) if(this->tabLabels[pos][i]==region) return true;

    return false;
  }



/********** Fonctions de partage des eaux **********/
/*                                                 */
/* im doit etre une image en niv de gris (1 plan)  */
/* out est l'image contenant les labels des sources*/
/* markeurs = liste des points sources             */
/***************************************************/
template<class T>
void Watershed2d<T>::Process(T* tabIn, T* tabClustered, queue<int> & marqueurs, int inverse)
{
  int i;
  int pt,vois;
  int niv;
  T coul;
  
  /* Init de la liste des niveaux 0 */
  swap(this->niveaux[0],marqueurs);
  
  for(i=0;i<256;i++)
    {
      //inondation
      while(!this->niveaux[i].empty())
	{
	  //tant que file[i] non vide
	  //Lire un point dans la file
	  pt = this->niveaux[i].front();
	  this->niveaux[i].pop();
	  
	  coul = tabClustered[pt];
	  //cout << "Traitement de " << pt << " de la region " << coul << endl;
	  
	  /* On traite les voisins */
	  for(int v=0;v<8;v++)
	    {
	      /* On calcule l'indice du voisin */
	      vois = pt + this->voisList[v];
	      
	      //si voisin pas traité alors 
	      //      elargir l'image label 
	      //             et
	      //      mettre les coordonnées du voisin dans la file :
	      //         file[max(gradient,i)]
	      
	      /* Teste si on est dans le tableau */
	      if(vois>=0 && vois<this->size )
		{
		  //cout << "voisin position " << vois << "tabIn = " << tabIn[vois] << " et tabClustered = " <<  tabClustered[vois] << endl;
		  /* Si le pixel n'est pas labelise et non null dans le tableau original */
		  if(tabIn[vois] && !tabClustered[vois])
		    {	
		      //cout << "ON LABELISE\n";
		      
		      //voisin non traité
		      //on affecte la couleur et on empile les coordonnées
		      tabClustered[vois] = coul;
		      
		      niv = (int)(tabIn[vois]);
		      if(inverse) niv = 255 - niv;

		      //cout << "niveau actuel = " << i << "  niv = " << niv << endl;
		      
		      if(niv<i) this->niveaux[i].push(vois);
		      else this->niveaux[niv].push(vois);		      
		    }
		}		
	    }
	}
    }
}



template<class T>
void Watershed2d<T>::CalcFcol2d(T* tabClustered, IplImage* imgOut)
{
  int pos=0;
  for(int i=0;i<imgOut->height;i++)
    for(int j=0;j<imgOut->width;j++)
      {
 	CvScalar couleur = SCalcFcol(tabClustered[pos++]);
 	cvSet2D(imgOut,i,j,couleur);
      }
}



/****************************************************************************************************************/
/*                                             PARTIE WATERSHED 1D                                              */
/****************************************************************************************************************/

template<class T>
Watershed1d<T>::Watershed1d()
{
  cout << "--> Watershed1d (Constructor) \t:\t Construction de watershed 1d sans parametres\n";
}

template<class T>
Watershed1d<T>::Watershed1d(int size)
{
  cout << "--> Watershed1d (Constructor) \t:\t Construction de watershed 1d " << size << "\n";
  this->alloc(size);
}

template<class T>
void Watershed1d<T>::alloc(int size)
{
  cout << "--> Watershed1d (alloc) \t:\t Alloc de watershed 1d " << size << "\n";
  this->size = size;

  /* Dimention du vecteur */
  this->vectSize = this->size*sizeof(T);

  /* tableau masque de traitement (contient le nb de labels associes) */
  this->vectMask = new int[this->size];
  memset(this->vectMask,0,this->vectSize);
}

template<class T>
Watershed1d<T>::~Watershed1d()
{
  delete [] this->vectMask;
}

/* Nomalisation pour obtenir des valeurs entre 0 et 255 */
template<class T>
void Watershed1d<T>::Normalize(T* vectIn)
{
  float max = 0;
  float coeff;

  for(int i=0;i<this->size;i++)
    if(vectIn[i]>max) max = vectIn[i];
   
  this->Normalize(vectIn,255.0/max);
}

template<class T>
void Watershed1d<T>::Normalize(T* vectIn, float coeff)
{
  for(int i=0;i<this->size;i++)
    vectIn[i] = (T)(vectIn[i]*coeff);
}

/********************************************/
/* Selection des marqueurs pour watershed   */
/********************************************/
/*
  Ici on peut le faire en un parcours en regardant pour chaque pic le minimum
  qui les separent des pics a gauche et a droite
*/
template<class T>
int Watershed1d<T>::ExtractMax(T* vectIn, T* vectClustered, queue<int> & picList, double seuil, int seuilpic, int startreg)
{
  int val,nb=startreg;
  int nbregions;
  int pic,vois;
  double contraste,contrasteNorm;  

  /* Init des regions clusterisees */
  memset(vectClustered,0,this->vectSize);

  /* Parcours de l'image et mise dans les files correspondantes
     Sauf le contour */
  for(int pos=0;pos<this->size;pos++)
    {
      val = cvRound(vectIn[pos]);   
      if(val>0) this->niveaux[(int)val].push(pos);
    }

  memset(this->vectMask,0,this->vectSize);

  /* Remplissage pour trouver les separations des pics et calcul du CN pour les conserver ou non */ 
  nbregions=0;
  for(int i=255;i>0;i--)
    {
      /* Pour chaque file */
      while(!this->niveaux[i].empty())
	{
	  /* Tant que file non vide on traite les points */
	  pic = this->niveaux[i].front();
	  this->niveaux[i].pop();
	  
	  /* On regarde si le pixel est traite. Si oui, il appartient a une region au moins. Si non, c'est un nouveau pic */	  
	  if( (!this->vectMask[pic]) && (vectIn[pic] > seuilpic) )
	    {
	      /*
		pixel non traite
		nouvelle region : 
		 - on incremente le nb de regions
	         - on labelise le point
	         - on sauve la valeur du pic
	         - on ajoute dans la file le pt = depart du grossissement
	         - on ajoute le point dans la file correspondant a la region a laquelle il appartient
	      */
	      nbregions++;

	      /* On augmente le nombre de labels associes au pixel */
	      this->vectMask[pic]=nbregions;

	      contraste = 0;

	      /**** RECHERCHE A GAUCHE ****/	      
	      vois = pic-1;

	      /* Recherche du min a gauche tant que le voisin est inferieur et qu'il n'a pas ete traite */
	      while(vois>=0 && !this->vectMask[vois] && vectIn[vois]<=vectIn[vois+1])
		{
		  /* On marque le pixel traite avec le label actuel */
		  this->vectMask[vois]=nbregions;

		  /* On passe au voisin suivant */
		  vois--;
		}
	      
	      /* Si on est arrete sur un min qui separe le pic d'un autre pic on affecte le contraste au pic */
	      if(this->vectMask[vois] && this->vectMask[vois]!=nbregions) contraste = vectIn[vois];

	      /**** RECHERCHE A DROITE ****/
	      vois = pic+1;
	      
	      /* Recherche du min a gauche tant que le voisin est inferieur et qu'il n'a pas ete traite */
	      while(vois<size && !this->vectMask[vois] && vectIn[vois]<=vectIn[vois-1])
		{
		  /* On marque le pixel traite avec le label actuel */
		  this->vectMask[vois]=nbregions;

		  /* On passe au voisin suivant */
		  vois++;
		}
	      
	      /* Si on est arrete sur un min qui separe le pic d'un autre pic on affecte le contraste au pic */
	      if(this->vectMask[vois] && this->vectMask[vois]!=nbregions)
		if(vectIn[vois]>contraste) contraste = vectIn[vois];		
	    	
	      /* Calcul du contraste normalise pour decider de conserver le pic */
	      contrasteNorm = (i-contraste)/i;
	      
	      /* La file est vide, on a donc traite toute la region
		 Region grossie, on calcule le contraste normalisé pour décider si on garde ou non le pic */
	      if( (!contrasteNorm) || (contrasteNorm > seuil) )
		{
		  //cout << "Pic niveau " << i << " conserve : contraste = " << contraste << "contrasteNorm = " << contrasteNorm << "\n";
		  
		  /* On garde cette region comme marqueur */
		  picList.push(pic);
		  
		  /* On incremente le nombre de regions conservees */
		  nb++;
		  
		  /* On trace dans le tableau de sortie (label a partir de 1 donc apres incrementation de nb) */
		  vectClustered[pic] = nb;		  
		}
	    }
	}
    }
  /* Nombre de regions conservees */
  return nb;
}


/********** Fonctions de partage des eaux **********/
/*                                                 */
/* im doit etre une image en niv de gris (1 plan)  */
/* out est l'image contenant les labels des sources*/
/* markeurs = liste des points sources             */
/***************************************************/
template<class T>
void Watershed1d<T>::Process(T* vectIn, T* vectClustered, queue<int> & marqueurs, int inverse)
{
  int i;
  int pt,vois;
  int niv;
  T coul;
  
  /* Init de la liste des niveaux 0 */
  swap(this->niveaux[0],marqueurs);
  
  for(i=0;i<256;i++)
    {
      //inondation
      while(!this->niveaux[i].empty())
	{
	  //tant que file[i] non vide
	  //Lire un point dans la file
	  pt = this->niveaux[i].front();
	  this->niveaux[i].pop();
	  
	  coul = vectClustered[pt];

	  /* VOISIN DE GAUCHE */
	  vois = pt - 1;
	  if(vois >=0 && vectIn[vois] && !vectClustered[vois])
	    {
	      vectClustered[vois] = coul;
	      niv = (int)(vectIn[vois]);
	      if(inverse) niv = 255 - niv;
	      if(niv<i) this->niveaux[i].push(vois);
	      else this->niveaux[niv].push(vois);	
	    }

	  /* VOISIN DE DROITE */
	  vois = pt + 1;
	  if(vois<256 && vectIn[vois] && !vectClustered[vois])
	    {
	      vectClustered[vois] = coul;
	      niv = (int)(vectIn[vois]);
	      if(inverse) niv = 255 - niv;
	      if(niv<i) this->niveaux[i].push(vois);
	      else this->niveaux[niv].push(vois);	
	    }
	}
    }  
}




#endif
