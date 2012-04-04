#ifndef SQUAREROOTUTILS_H
#define SQUAREROOTUTILS_H

#include "matrixutils.h"

//----------------------------------------------------------------------
//---------           FONCTIONS SQUARE ROOT PERSOS           -----------
//----------------------------------------------------------------------
template <class T>
// \param matrice matrice generee dim*(taille + dim) (out)
// \param sigmaPoints (in)
// \param dim dimension des sigma points (in)
// \param taille nb de sigma Points a considerer (in)
// \param bruit_sqrt matrice de cholesky associee au bruit dim*dim (in)
// \param reference vecteur a soustraire a chaque sigma point (in)
// \param poids_sqrt racine du poids utilise (in)
int genererMatrice(T* matrice, T* sigmaPoints, int dim, int taille, T* bruit_sqrt, T* reference, T poids_sqrt)
{
  int taille_totale = taille + dim;
  
  
  for (int i=0; i<taille; i++)
    for (int j=0; j<dim; j++)
      matrice[j*taille_totale+i]=poids_sqrt*(sigmaPoints[(i+1)*dim+j]-reference[j]);
  
  for (int i=0; i<dim; i++)
    for (int j=0; j<dim; j++)
      matrice[j*taille_totale+i+taille]=bruit_sqrt[j*dim+i];
  
  return 1;
}





// \fn int SolveUpperSystem(T* X, T* Up, T* Res, int m, int n)
// \brief resoud X*Up = Res
// \param X est m*n (out)
// \param Up est n*n triangulaire superieure (in)
// \param Res est m*n (in)
template <class T>
int SolveUpperSystem(T* X, T* Up, T* Res, int m, int n)
{
  T sum;

  for (int j=0; j<n; j++)
    for (int i=0; i<m; i++)
      {
	sum=0;
	for (int k=0; k<j; k++) sum+=X[i*n+k]*Up[k*n+j];
        X[i*n+j] = (Res[i*n+j]-sum)/Up[j*n+j];
      }
  
  return 1;
}


// \fn int SolveLowerSystem(T* X, T* Low, T* Res, int m, int n)
// \brief resoud X*Low = Res
// \param X est m*n (out)
// \param Low est n*n triangulaire inferieure (in)
// \param Res est m*n (in) 
template <class T>
int SolveLowerSystem(T* X, T* Low, T* Res, int m, int n)
{
  T sum;

  for (int j=n-1; j>=0; j--)
    for (int i=0; i<m; i++)
      {
	sum=0;
	for (int k=j+1; k<n; k++) sum+=X[i*n+k]*Low[k*n+j];
        X[i*n+j] = (Res[i*n+j]-sum)/Low[j*n+j];
      }
  
  return 1;
}




//----------------------------------------------------------------------
//---------           FONCTIONS DECOMPOSITION QR          --------------
//----------------------------------------------------------------------

template <class T>
T hypot(const T &a, const T &b)
{
  if (a==0)
    return abs(b);
  else
    {
      T c = b/a;
      return fabs(a) * sqrt(1 + c*c);
    }
}



// \fn int QR(T* A, T* Rdiag, T* QR_, int m, int n)
// \brief calcule une representation de la decomposition QR d une matrice
//        A priori cette fonction n est utile qu en interne a ce fichier
// \param Rdiag vecteur 1D de dimension n (out)
// \param QR matrice m * n (out) m>=n
// \param A matrice m * n (in) m>=n
template <class T>
int QR(T* A, T* Rdiag, T* QR_, int m, int n)
{

  //T* QR_ = AllocVector(m*n);
  CopyMatrix(A,n,m,QR_);

  
  // Main loop.
  for (int k = 0; k < n; k++) 
    {
      // Compute 2-norm of k-th column without under/overflow.
      T nrm = 0;

      for (int i = k; i < m; i++)
	nrm = hypot(nrm,QR_[i*n+k]);
  
      if (nrm != 0.0) 
	{
	  // Form k-th Householder vector.
	  if (QR_[k*n+k] < 0) nrm = -nrm;
	  
	  for (int i = k; i < m; i++) 
	    QR_[i*n+k] /= nrm;
	  
	  QR_[k*n+k] += 1.0;
	  
	  // Apply transformation to remaining columns.
	  for (int j = k+1; j < n; j++) 
	    {
	      T s = 0.0; 
	      for (int i = k; i < m; i++)
		s += QR_[i*n+k]*QR_[i*n+j];
	      s = -s/QR_[k*n+k];
	      for (int i = k; i < m; i++)
		QR_[i*n+j] += s*QR_[i*n+k];
	    }
	}

      Rdiag[k] = -nrm;
    }
  
  return 1;
}

/* Meme fonction que la precedente mais sans recopie de A dans QR_ La matrice d'entree est modifiee et contient QR */
template <class T>
int QR(T* QR_, T* Rdiag, int m, int n)
{
  // Main loop.
  for (int k = 0; k < n; k++) 
    {
      // Compute 2-norm of k-th column without under/overflow.
      T nrm = 0;

      for (int i = k; i < m; i++)
	nrm = hypot(nrm,QR_[i*n+k]);
  
      if (nrm != 0.0) 
	{
	  // Form k-th Householder vector.
	  if (QR_[k*n+k] < 0) nrm = -nrm;
	  
	  for (int i = k; i < m; i++) 
	    QR_[i*n+k] /= nrm;
	  
	  QR_[k*n+k] += 1.0;
	  
	  // Apply transformation to remaining columns.
	  for (int j = k+1; j < n; j++) 
	    {
	      T s = 0.0; 
	      for (int i = k; i < m; i++)
		s += QR_[i*n+k]*QR_[i*n+j];
	      s = -s/QR_[k*n+k];
	      for (int i = k; i < m; i++)
		QR_[i*n+j] += s*QR_[i*n+k];
	    }
	}
      Rdiag[k] = -nrm;
    }
  return 1;
}






// \fn int GetR(T* QR_, T* Rdiag, T* R, int n)
// \brief cette fonction calcule la matrice R a partir de la representation interne
//        de la decomposition QR d'une matrice.
//        Cette fonction renvoie la matrice R sous forme "economy size" cad que
//        seuls les n 1eres lignes de R sont calculees (les suivantes sont toutes nulles)
//        R est triangulaire superieure
//        A priori cette fonction n est utile qu en interne a ce fichier
// \param R matrice carree n*n triangulaire(out)
// \param Rdiag vecteur 1D de taille n (in)
// \param QR_ matrice m*n (in)
template <class T>
int GetR(T* QR_, T* Rdiag, T* R, int n)
{

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) 
      {
	if (i < j) R[i*n+j] = QR_[i*n+j];
	else if (i == j) R[i*n+j] = Rdiag[i];
	else R[i*n+j] = 0.0;   
      }

  return 1;
}


// \fn int GetQ(T* QR_, T* Q, int m, int n)
// \brief cette fonction calcule la matrice Q a partir de la representation interne
//        de la decomposition QR d'une matrice.
//        Cette fonction renvoie la matrice Q sous forme "economy size" cad que
//        seuls les n 1eres colonnes de Q sont calculees 
//        (les suivantes ne sont pas forcement nulles, mais elles ne servent a rien 
//        lors de la multiplication Q*R puisque les m-n dernieres lignes de R
//        sont nulles).
//        A priori cette fonction n est utile qu en interne a ce fichier
// /param Q matrice m*n (out) m>=n
// /param QR matrice m*n (in) m>=n
// /param m (in)
// /param n (in)
template <class T>
int GetQ(T* QR_, T* Q, int m, int n)
{

  for (int k = n-1; k >= 0; k--) 
    {
      for (int i = 0; i < m; i++) 
	Q[i*n+k] = 0.0;
    
      Q[k*n+k] = 1.0;
      for (int j = k; j < n; j++) 
	{
	  if (QR_[k*n+k] != 0) 
	    {
	      T s = 0.0;
	      for (int i = k; i < m; i++)
		s += QR_[i*n+k]*Q[i*n+j];
	  
	      s = -s/QR_[k*n+k];
	      for (int i = k; i < m; i++) 
		Q[i*n+j] += s*QR_[i*n+k];
	      
	    }
	}
    }

  return 1;
}



// \fn int GetRFromQRDecomposition(T* R, T* A, int m, int n)
// \brief Cette fonction calcule la matrice R de la decomposition QR
//        de la matrice A. R est une matrice "economy size" (n*n et non
//        pas m*n, puisque les m-n dernieres lignes sont nulles)
//        La matrice R renvoyee est triangulaire superieure
// \param R matrice carree n * n (out) m>=n
// \param A matrice m * n (in) m>=n
// \param m (in)
// \param n (in)
template <class T>
int GetRFromQRDecomposition(T* R, T* A, int m, int n)
{
  T* qr = AllocVector<T>(m*n);
  T* rDiag = AllocVector<T>(n);

  QR(A,rDiag,qr,m,n);
  GetR(qr,rDiag,R,n);

  DeleteVector<T>(qr);
  DeleteVector<T>(rDiag);
  return 1;
}




//----------------------------------------------------------------------
//---------           FONCTIONS RAJOUTEES                 --------------
//----------------------------------------------------------------------
template <class T>
void Transform(T* A, T* Vin, T* Vout, int m, int n)
{
  SetZero<T>(Vout,m);

  for (int i=0; i<m; i++)
    for (int j=0; j<n; j++)
      Vout[i] += A[i*n+j]*Vin[j];
}

template <class T>
void SquareTransform(T* A, T* Vin, T* Vout, int size)
{
  SetZero<T>(Vout,size);

  for (int i=0; i<size; i++)
    for (int j=0; j<size; j++)
      Vout[i] += A[i*size+j]*Vin[j];
}


template <class T>
void MatrixTranspose(T* in, T* out, int m , int n)
{
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      out[i*m+j]=in[j*n+i];
}

template <class T>
void MatrixMult(T* in1, T* in2, T* out, int m, int n, int o)
{
  SetZero<T>(out,m*o);

  for (int i=0; i<m; i++)
    for (int j=0; j<o; j++)
      for (int k=0; k<n; k++)
	out[i*o+j] += in1[i*o+k]*in2[k*o+j];

}

template <class T>
void SquareMatrixAdd(T* in1, T* in2, T* out, int size)
{
   for (int i=0; i<size; i++)
    for (int j=0; j<size; j++)
      out[i*size+j]=in1[i*size+j]+in2[i*size+j];
}


template <class T>
void SquareMatrixMult(T* in1, T* in2, T* out, int size)
{
  SetZero<T>(out,size*size);

  for (int i=0; i<size; i++)
    for (int j=0; j<size; j++)
      for (int k=0; k<size; k++)
	out[i*size+j] += in1[i*size+k]*in2[k*size+j];

}

template <class T>
void SquareMatrixTranspose(T* in, T* out, int size)
{
  for (int i=0; i<size; i++)
    for (int j=0; j<size; j++)
      out[i*size+j]=in[j*size+i];
}

template <class T>
void SquareUpperMatrixTranspose(T* inout, int size)
{
  for (int i=0; i<size; i++)
    for (int j=0; j<i; j++)
      inout[i*size+j]=inout[j*size+i];

  for (int i=0; i<size; i++)
    for (int j=i+1; j<size; j++)
      inout[i*size+j]=0;
}

template <class T>
void SquareLowerMatrixTranspose(T* inout, int size)
{
  for (int i=0; i<size; i++)
    for (int j=i+1; j<size; j++)
      inout[i*size+j]=inout[j*size+i];

  for (int i=0; i<size; i++)
    for (int j=0; j<i; j++)
      inout[i*size+j]=0;
}

//----------------------------------------------------------------------
//---------           FONCTIONS CHOLESKY UPDATE REECRITES        -------
//----------------------------------------------------------------------

template <class T>
T SumSquare(T* vecteur, int size)
{
  T sum = 0;

  for (int i=0; i<size; i++) 
    sum += vecteur[i]*vecteur[i];

  return sum;
}




//----------------------------------------------------------------------
//--------           FONCTIONS CHOLESKY UPDATE MODIFIEES             ---
//----------------------------------------------------------------------

// \fn T pythag(T f, T g, T& c, T& s)
// \brief return z=sqrt(f*f+g*g), c=f/z, s=g/z
//        set c=1,s=0 if z==0
//        avoid floating point overflow or divide by zero
// \param f (in)
// \param g (in)
// \param c (out)
// \param s (out)
template <class T>
T pythag(T f, T g, T& c, T& s)
{
   if (f==0 && g==0) { c=1.0; s=0.0; return 0.0; }
   T af = f>=0 ? f : -f;
   T ag = g>=0 ? g : -g;
   if (ag<af)
   {
      T h = g/f; 
      T sq = sqrt(1.0+h*h);
      if (f<0) sq = -sq;           // make return value non-negative
      c = 1.0/sq; 
      s = h/sq; 
      return sq*f;
   }
   else
   {
      T h = f/g; 
      T sq = sqrt(1.0+h*h);
      if (g<0) sq = -sq;
      s = 1.0/sq; 
      c = h/sq; 
      return sq*g;
   }
}


// Misc numerical things
template <class T>
inline void GivensRotation(T cGivens, T sGivens, T& x, T& y)
{
   // allow for possibility &x = &y
   T tmp0 = cGivens * x + sGivens * y;
   T tmp1 = -sGivens * x + cGivens * y;
   x = tmp0; y = tmp1;
}
   
template <class T>
inline void GivensRotationR(T cGivens, T sGivens, T& x, T& y)
{
   // also change sign of y
   // allow for possibility &x = &y
   T tmp0 = cGivens * x + sGivens * y;
   T tmp1 = sGivens * x - cGivens * y;
   x = tmp0; y = tmp1;
}   



// Contributed by Nick Bennett of Schlumberger-Doll Research; modified by RBD

// The enclosed routines can be used to update the Cholesky decomposition of
// a positive definite symmetric matrix.  A good reference for this routines
// can be found in
// LINPACK User's Guide, Chapter 10, Dongarra et. al., SIAM, Philadelphia, 1979

// produces the Cholesky decomposition of A + x.t() * x where A = chol.t() * chol


// chol est triangulaire superieure.

template <class T>
void RankOneUpperCholeskyUpdate(T* cholup, T* x, int size)
{
  T* cGivens = AllocVector<T>(size);
  SetZero(cGivens,size);
  T* sGivens = AllocVector<T>(size);
  SetZero(sGivens,size);
  
  for(int j = 0; j < size; j++) // process the jth column of chol
    {
      // apply the previous Givens rotations k = 1,...,j-1 to column j
      for(int k = 0; k < j; k++)
	GivensRotation(cGivens[k], sGivens[k], cholup[k*size+j], x[j]);
      
      // determine the jth Given's rotation
      pythag(cholup[j*size+j], x[j], cGivens[j], sGivens[j]);
      
      // apply the jth Given's rotation
      {
	T tmp0 = cGivens[j] * cholup[j*size+j] + sGivens[j] * x[j];
	cholup[j*size+j] = tmp0; 
	x[j] = 0.0;
      }
      
    }

  DeleteVector(sGivens);
  DeleteVector(cGivens);
  
}




// fonction rajoutee pour permettre de faire un update a partir d une matrice
// triangulaire inferieure. C est strictement la meme fonction que la 
// precedente, a ceci pres que l algo transpose les termes au fur et a mesure 
// pour les calculs qu il fait.
template <class T>
void RankOneLowerCholeskyUpdate(T* chollow, T* r1Modification, int size)
{

  T* cGivens = AllocVector<T>(size);
  SetZero(cGivens,size);
  T* sGivens = AllocVector<T>(size);
  SetZero(sGivens,size);
  
  for(int j = 0; j < size; j++) // process the jth line of chol
    {
      // apply the previous Givens rotations k = 1,...,j-1 to line j
      for(int k = 0; k < j; k++)
	GivensRotation(cGivens[k], sGivens[k], chollow[j*size+k], r1Modification[j]);
      
      // determine the jth Given's rotation
      pythag(chollow[j*size+j], r1Modification[j], cGivens[j], sGivens[j]);
      
      // apply the jth Given's rotation
      {
	T tmp0 = cGivens[j] * chollow[j*size+j] + sGivens[j] * r1Modification[j];
	chollow[j*size+j] = tmp0; 
	r1Modification[j] = 0.0;
      }
      
    }

  DeleteVector(sGivens);
  DeleteVector(cGivens);
  
}









// produces the Cholesky decomposition of A - x.t() * x where A = chol.t() * chol
template <class T>
int RankOneUpperCholeskyDowndate(T* cholup, T* x, int size)
{
  T* a = AllocVector<T>(size);
  SetZero(a,size);
  
  for (int i = 0; i < size; i++)
    {
      // accumulate subtr sum
      T subtrsum = 0.0;
      for(int k = 0; k < i; k++) subtrsum += a[k] * cholup[k*size+i];
      
      a[i] = (x[i] - subtrsum) / cholup[i*size+i];
    }
  
  // test that l2 norm of a is < 1
  T squareNormA = SumSquare<double>(a,size);
  if (squareNormA >= 1.0)
    return 0; // = erreur
  
  T alpha = sqrt(1.0 - squareNormA);
  
  // compute and apply Givens rotations to the vector a
  T* cGivens = AllocVector<T>(size);
  SetZero(cGivens,size);
  T* sGivens = AllocVector<T>(size);
  SetZero(sGivens,size);
  
  for(int i = size-1; i >= 0; i--)
    alpha = pythag(alpha, a[i], cGivens[i], sGivens[i]);
  
  // apply Givens rotations to the jth column of cholup
  T* xtilde = AllocVector<T>(size);
  SetZero(xtilde,size);
  
  for(int j = size-1; j >= 0; j--)
    {
      // only the first j rotations have an affect on cholup,0
      for(int k = j; k >= 0; k--)
	GivensRotation(cGivens[k], -sGivens[k], cholup[k*size+j], xtilde[j]);
    }
  
  
  DeleteVector(a);
  DeleteVector(xtilde);
  DeleteVector(sGivens);
  DeleteVector(cGivens);

   return 1;
}




// produces the Cholesky decomposition of A - x.t() * x where A = chol.t() * chol
template <class T>
int RankOneLowerCholeskyDowndate(T* chollow, T* x, int size)
{
  T* a = AllocVector<T>(size);
  SetZero(a,size);
  
  for (int i = 0; i < size; i++)
    {
      // accumulate subtr sum
      T subtrsum = 0.0;
      for(int k = 0; k < i; k++) subtrsum += a[k] * chollow[i*size+k];
      
      a[i] = (x[i] - subtrsum) / chollow[i*size+i];
    }
  
  // test that l2 norm of a is < 1
  T squareNormA = SumSquare<double>(a,size);
  if (squareNormA >= 1.0)
    return 0; // = erreur
  
  T alpha = sqrt(1.0 - squareNormA);
  
  // compute and apply Givens rotations to the vector a
  T* cGivens = AllocVector<T>(size);
  SetZero(cGivens,size);
  T* sGivens = AllocVector<T>(size);
  SetZero(sGivens,size);
  
  for(int i = size-1; i >= 0; i--)
    alpha = pythag(alpha, a[i], cGivens[i], sGivens[i]);
  
  // apply Givens rotations to the jth column of cholup
  T* xtilde = AllocVector<T>(size);
  SetZero(xtilde,size);
  
  for(int j = size-1; j >= 0; j--)
    {
      // only the first j rotations have an affect on cholup,0
      for(int k = j; k >= 0; k--)
	GivensRotation(cGivens[k], -sGivens[k], chollow[j*size+k], xtilde[j]);
    }
  
  
  DeleteVector(a);
  DeleteVector(xtilde);
  DeleteVector(sGivens);
  DeleteVector(cGivens);

  return 1;
}

#endif
