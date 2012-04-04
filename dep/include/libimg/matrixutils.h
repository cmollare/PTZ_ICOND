/******************************************/
/*     Reprise de _cvmatrix.h             */
/******************************************/

#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <memory.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

template<class T>
inline void CopyVector(T* src,int len, T* dst) { memcpy(dst,src,len*sizeof(T)); }

template<class T>
inline void SetZero(T* dst, int len ) { memset(dst,0,len*sizeof(T)); }

template<class T>
inline void CopyMatrix(T* src, int  w, int h, T* dst ) { memcpy(dst,src,w*h*sizeof(T)); }

template<class T>
inline T* AllocVector(int size) { return new T[size]; }

/* new avec init a 0 */
template<class T>
inline T* newZero(int size) { T* tmp = new T[size]; memset(tmp,0,size*sizeof(T)); return tmp; }

template<class T>
inline T* AllocMatrix(int m, int n) { return AllocVector<T>(m*n); }

template<class T>
inline void DeleteVector(T* vec)  {delete [] vec;}

template<class T>
inline void DeleteMatrix(T* vec)  {delete [] vec;}

template<class T>
inline void DispVector(T* vect, int size, string dispdec="")
{
  int i=size;
  T* ptvect = vect;
  while(i--)
    cout << dispdec << *ptvect++ << "\t";
  cout << endl;
}

template<class T>
inline void DispMatrix(T* vect, int w, int h, string dispdec="")
{
  int i=h;
  T* ptvect = vect;
  while(i--)
    {
      DispVector<T>(ptvect,w,dispdec);
      ptvect+=w;
    }
}

template<class T>
inline void DispMatrix(T* vect, int t, string dispdec="")
{
  int i=t;
  T* ptvect = vect;
  while(i--)
    {
      DispVector<T>(ptvect,t,dispdec);
      ptvect+=t;
    }
}

/*! \fn void MatrixCopyByid(TCP* matIn, TCP* matOut, int taille, int* vectid)
 *  \brief this function copy datas from matIn to matOut using vectid indices as corresponding 
 *  indices
 *  matIn must be different than matOut
 */
template<class T>
void MatrixCopyByid(T* matIn, T* matOut, int taille, int* vectid)
{
  for(int i=0;i<taille;i++)
    matOut[i] = matIn[vectid[i]];
}


/*! \fn
 *  \brief
 */

/* On multiplie X'X */
template<class T>
void SquareMatrixMultXprimX(T* matIn, T* matOut, int taille)
{
  SetZero<T>(matOut,taille*taille);

  for (int i=0; i<taille; i++)
    for (int j=0; j<taille; j++)
      for (int k=0; k<taille; k++)
	matOut[i*taille+j] += matIn[k*taille+i]*matIn[k*taille+j];
}

/* On multiplie XX' */
template<class T>
void SquareMatrixMultXXprim(T* matIn, T* matOut, int taille)
{
  SetZero<T>(matOut,taille*taille);

  for (int i=0; i<taille; i++)
    for (int j=0; j<taille; j++)
      for (int k=0; k<taille; k++)
	matOut[i*taille+j] += matIn[i*taille+k]*matIn[j*taille+k];
}

/*! \fn void InitTransposeMap(int m, int n, int* Tmap)
 *  \brief this function initialise a map vector that can be used to transpose matrix
 *  \return the size of the Tmap vector = m*n
 */
inline
int InitTransposeMap(int m, int n, int* & Tmap)
{
  int size = m*n;
  if(Tmap==NULL) Tmap = AllocVector<int>(size);

  for(int i=0;i<m;i++)
    for(int j=0;j<n;j++)
      Tmap[i*n+j] = j*m+i;

  return size;
}

/*! \fn void DynMatMulVectAddBruit_32f(const float *matr, const float *vectmul, const float *covbruit, const float *vectrnd, int n, float *dest)
 *  \brief Cette fonction permet de calculer rapidement la prediction d'une particule avec bruit de dynamique calcule a partir 
 *         de la covariance de bruit et d'un vecteur tire selon N(0,1)
 *  \param n le nombre de parametres a estimer 
 *  \param taille la taille du demi vecteur pour le memcpy
 *  \param matr = matrice de dynamique de type modele AR du deuxieme ordre dim = [2n x 2n]
 *  \param vectmul = vecteur d'etat (une particule) de dimension dim =[2n x 1]
 *  \param covbruit = matrice de covariance du bruit de dynamique dim = [n x n]
 *  \param vectrnd = vecteur utilise pour calculer le bruit, ce vecteur est issu d'un tir selon N(0,1) et dim = [n x 1]
 *  \return dest = resultat de la prediction + bruit (Particule a l'instant k+1)
 */
template<class T>
inline void DynMatMulVectAddBruit(const T* matr, 
				  const T* vectmul, 
				  const T* covbruit,
				  const T* vectrnd, 
				  int n,int taille, 
				  T* dest)
{
  
  int i,j;
  int incr = n+n;


  for(i=0, j=n ; i<n ; i++, j++, matr += incr, covbruit+= n)
    dest[i] = matr[i]*vectmul[i] + matr[j]*vectmul[j] + covbruit[i]*vectrnd[i];      
    
  /* recopie du passe */
  memcpy(dest+n,vectmul,taille);

}

/*! \fn CV_INLINE void VectAddBruit_32f(const float *vect, 
				const float *covbruit,
				const float *vectrnd, 
				int n,float *dest)
 *  \brief Cette fonction permet d'ajouter un bruit sur un vecteur a partir du vecteur initial,
 *  d'une matrice de covariance DIAGONALE et d'un vecteur tire selon une normale N(0,1)
 *  \param vect le vecteur d'entree
 *  \param covbruit la covariance (elle doit etre diagonale pour cette fonction)
 *  \param vectrnd vecteur tire selon N(0,1)
 *  \param n la taille du vecteur
 *  \return dest le resultat vect = vect + covbruit * vectrnd
 */
template<class T>
inline void VectAddBruit(const T* vect, 
			 const T* covbruit,
			 const T* vectrnd, 
			 int n, T* dest)
{
  
  int i;

  for(i=0 ; i<n ; i++, covbruit+= n)
    dest[i] = vect[i] + covbruit[i]*vectrnd[i];      
}

/*! \fn void DynMatMulVect_32f(const float *matr, const float *vectmul, int n, float *dest)
 *  \brief Cette fonction permet de calculer rapidement la prediction d'une particule sans ajout de bruit
 *  \param n le nombre de parametres a estimer 
 *  \param taille la taille du demi vecteur pour le memcpy
 *  \param matr = matrice de dynamique de type modele AR du deuxieme ordre dim = [2n x 2n]
 *  \param vectmul = vecteur d'etat (une particule) de dimension dim =[2n x 1]
 *  \return dest = resultat de la prediction sans bruit (Particule a l'instant k+1)
 */
template<class T>
inline void DynMatMulVect(const T* matr,const T* vectmul,int n,int taille,T* dest)
{  
  int i,j;
  int incr = n+n;
  for(i=0, j=n ; i<n ; i++, j++, matr += incr)
    dest[i] = matr[i]*vectmul[i] + matr[j]*vectmul[j];
    
  /* recopie du passe */
  memcpy(dest+n,vectmul,taille);
}

/*! \fn CovMatMulRndVectAddMean_32f(const float *cov, const float *vectrnd, const float *vectmean, int n, float *dest)
 *  \brief Cette fonction calcule les parametres d'un vecteur (particule pour moi) en les tirant autour d'un vecteur moyen
 *         et avec une covariance cov
 *  \param n le nombre de parametres du systeme
 *  \param cov = la covariance qui sert a tirer   dim = [n x n]
 *  \param vectrnd = un vecteur tire selon N(0,1) pour estimer le bruit sur la moyenne    dim = [n x 1]
 *  \param vectmean = vecteur contenant les parametres moyens autour desquels on veut tirer   dim = [n x 1]
 *  \return dest :  vecteur initialiser autour de vectmean avec une covariance cov (ce vecteur est une particule donc 
 *                  est composee de l'instant courant et de l'instant precedent, ici on initialise le passe egal au present
 *	    dim = [2n x 1] sous la forme X = [X_k  X_{k-1}] avec X_{k-1} = X_k
 */
template<class T>
inline void CovMatMulRndVectAddMean(const T* cov, 
				    const T* vectrnd, 
				    const T* vectmean, 
				    int n, T* dest)
{  
  int i;
  for(i=0 ; i<n ; i++, cov += n)
    dest[i] = cov[i]*vectrnd[i] + vectmean[i];          
  /* recopie : passe = present */
  memcpy(dest+n,dest,n*sizeof(T));
}


/**
	Constructs a lower triangular matrix L, such that L*L'= A.
	If A is not symmetric positive-definite (SPD), only a
	partial factorization is performed. 
	return 1 if the factorizaiton was successful.
*/
template <class Real>
int Cholesky(const Real* A, Real *L_, int dim)
{
  int isspd=0;
  
  // Main loop.
  for (int j = 0; j < dim; j++) 
    {
      Real d = 0.0;
      for (int k = 0; k < j; k++) 
	{
	  Real s = 0.0;
	  for (int i = 0; i < k; i++) 
	    {
	      s += L_[k*dim+i]*L_[j*dim+i];
            }
	  L_[j*dim+k] = s = (A[j*dim+k] - s)/L_[k*dim+k];
	  d = d + s*s;
	  isspd = isspd && (A[k*dim+j]==A[j*dim+k]); 
	}
      d = A[j*dim+j] - d;
      isspd = isspd && (d > 0.0);
      L_[j*dim+j] = sqrt(d > 0.0 ? d : 0.0);
      for (int k = j+1; k < dim; k++) 
	{
	  L_[j*dim+k] = 0.0;
	}
    }
  return isspd;
}

/*! \fn int IsDiagonalCov(float *c)
 *  \brief this function check is the matrix c is diagonal
 *  \param c the matrix to be checked
 *  \param dim the matrix size
 *  \return an int that insdicate if c is diagonal
 *  @arg 0 : c is not diagonal
 *  @arg 1 : c is diagonal
*/
//template<class T>
//int isDiagonal(T* c, int dim);

template <class T>
int isDiagonal(T* c, int dim)
{
  
  /* Teste si la matrice est diagonale */
  for(int i=0;i<dim;i++)
    for(int j=0;j<dim;j++)
      {
	if((i!=j)&&(c[i*dim+j]>0)) return 0;
      }

  return 1;
}
template<class T>
inline T* getSubMatr2(T* Matr, int dim, int nbparam, int *parlist)
{
  /* Allocation des mean et cov temporaire */
  T* Mtmp = new T[nbparam*nbparam];
  int id;

  /* recuperation des moyennes */
  for(int i=0;i<nbparam;i++)
    {
      id = parlist[i];
      
      /* recuperation des covariances */
      for(int j=0;j<nbparam;j++)
	{
	  Mtmp[i*nbparam+j] = Matr[id*dim+parlist[j]];
	}
    }
  return Mtmp;
}


/* Extraction sous partie d'une matrice */
template<class T>
inline T* getSubMatr(T* Matr, int dim, int nbparam, int startp, int endp)
{
  int *parlist = new int[nbparam];

  /* init liste des parametres a extraire */
  for(int i=0,j=startp;j<=endp;i++,j++)
    parlist[i] = j;

  /* Extraction */
  T* Matrtmp = getSubMatr2<T>(Matr,dim,nbparam,parlist);

  /* Liberation de la memoire */
  delete [] parlist;

  return Matrtmp;
}




#endif

/* End of file. */
