// Copyright (C) 2009-2010 Gael Guennebaud <gael.guennebaud@inria.fr>
// Public License v. 2.0. If a copy of the MPL was not distributed

#include "common.h"

int EIGEN_BLAS_FUNC(hemv)(char *uplo, int *n, RealScalar *palpha, RealScalar *pa, int *lda, RealScalar *px, int *incx, RealScalar *pbeta, RealScalar *py, int *incy)
{
  typedef void (*functype)(int, const Scalar*, int, const Scalar*, int, Scalar*, Scalar);
  static functype func[2];

  static bool init = false;
  if(!init)
  {
    for(int k=0; k<2; ++k)
      func[k] = 0;

    func[UP] = (internal::selfadjoint_matrix_vector_product<Scalar,int,ColMajor,Upper,false,false>::run);
    func[LO] = (internal::selfadjoint_matrix_vector_product<Scalar,int,ColMajor,Lower,false,false>::run);

    init = true;
  }

  Scalar* a = reinterpret_cast<Scalar*>(pa);
  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* y = reinterpret_cast<Scalar*>(py);
  Scalar alpha  = *reinterpret_cast<Scalar*>(palpha);
  Scalar beta   = *reinterpret_cast<Scalar*>(pbeta);

  
  int info = 0;
  if(UPLO(*uplo)==INVALID)        info = 1;
  else if(*n<0)                   info = 2;
  else if(*lda<std::max(1,*n))    info = 5;
  else if(*incx==0)               info = 7;
  else if(*incy==0)               info = 10;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"HEMV ",&info,6);

  if(*n==0)
    return 1;

  Scalar* actual_x = get_compact_vector(x,*n,*incx);
  Scalar* actual_y = get_compact_vector(y,*n,*incy);

  if(beta!=Scalar(1))
  {
    if(beta==Scalar(0)) vector(actual_y, *n).setZero();
    else                vector(actual_y, *n) *= beta;
  }

  if(alpha!=Scalar(0))
  {
    int code = UPLO(*uplo);
    if(code>=2 || func[code]==0)
      return 0;

    func[code](*n, a, *lda, actual_x, 1, actual_y, alpha);
  }

  if(actual_x!=x) delete[] actual_x;
  if(actual_y!=y) delete[] copy_back(actual_y,y,*n,*incy);

  return 1;
}



int EIGEN_BLAS_FUNC(hpr)(char *uplo, int *n, RealScalar *palpha, RealScalar *px, int *incx, RealScalar *pap)
{
  typedef void (*functype)(int, Scalar*, const Scalar*, RealScalar);
  static functype func[2];

  static bool init = false;
  if(!init)
  {
    for(int k=0; k<2; ++k)
      func[k] = 0;

    func[UP] = (internal::selfadjoint_packed_rank1_update<Scalar,int,ColMajor,Upper,false,Conj>::run);
    func[LO] = (internal::selfadjoint_packed_rank1_update<Scalar,int,ColMajor,Lower,false,Conj>::run);

    init = true;
  }

  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* ap = reinterpret_cast<Scalar*>(pap);
  RealScalar alpha = *palpha;

  int info = 0;
  if(UPLO(*uplo)==INVALID)                                            info = 1;
  else if(*n<0)                                                       info = 2;
  else if(*incx==0)                                                   info = 5;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"HPR  ",&info,6);

  if(alpha==Scalar(0))
    return 1;

  Scalar* x_cpy = get_compact_vector(x, *n, *incx);

  int code = UPLO(*uplo);
  if(code>=2 || func[code]==0)
    return 0;

  func[code](*n, ap, x_cpy, alpha);

  if(x_cpy!=x)  delete[] x_cpy;

  return 1;
}

int EIGEN_BLAS_FUNC(hpr2)(char *uplo, int *n, RealScalar *palpha, RealScalar *px, int *incx, RealScalar *py, int *incy, RealScalar *pap)
{
  typedef void (*functype)(int, Scalar*, const Scalar*, const Scalar*, Scalar);
  static functype func[2];

  static bool init = false;
  if(!init)
  {
    for(int k=0; k<2; ++k)
      func[k] = 0;

    func[UP] = (internal::packed_rank2_update_selector<Scalar,int,Upper>::run);
    func[LO] = (internal::packed_rank2_update_selector<Scalar,int,Lower>::run);

    init = true;
  }

  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* y = reinterpret_cast<Scalar*>(py);
  Scalar* ap = reinterpret_cast<Scalar*>(pap);
  Scalar alpha = *reinterpret_cast<Scalar*>(palpha);

  int info = 0;
  if(UPLO(*uplo)==INVALID)                                            info = 1;
  else if(*n<0)                                                       info = 2;
  else if(*incx==0)                                                   info = 5;
  else if(*incy==0)                                                   info = 7;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"HPR2 ",&info,6);

  if(alpha==Scalar(0))
    return 1;

  Scalar* x_cpy = get_compact_vector(x, *n, *incx);
  Scalar* y_cpy = get_compact_vector(y, *n, *incy);

  int code = UPLO(*uplo);
  if(code>=2 || func[code]==0)
    return 0;

  func[code](*n, ap, x_cpy, y_cpy, alpha);

  if(x_cpy!=x)  delete[] x_cpy;
  if(y_cpy!=y)  delete[] y_cpy;

  return 1;
}

int EIGEN_BLAS_FUNC(her)(char *uplo, int *n, RealScalar *palpha, RealScalar *px, int *incx, RealScalar *pa, int *lda)
{
  typedef void (*functype)(int, Scalar*, int, const Scalar*, const Scalar*, const Scalar&);
  static functype func[2];

  static bool init = false;
  if(!init)
  {
    for(int k=0; k<2; ++k)
      func[k] = 0;

    func[UP] = (selfadjoint_rank1_update<Scalar,int,ColMajor,Upper,false,Conj>::run);
    func[LO] = (selfadjoint_rank1_update<Scalar,int,ColMajor,Lower,false,Conj>::run);

    init = true;
  }

  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* a = reinterpret_cast<Scalar*>(pa);
  RealScalar alpha = *reinterpret_cast<RealScalar*>(palpha);

  int info = 0;
  if(UPLO(*uplo)==INVALID)                                            info = 1;
  else if(*n<0)                                                       info = 2;
  else if(*incx==0)                                                   info = 5;
  else if(*lda<std::max(1,*n))                                        info = 7;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"HER  ",&info,6);

  if(alpha==RealScalar(0))
    return 1;

  Scalar* x_cpy = get_compact_vector(x, *n, *incx);

  int code = UPLO(*uplo);
  if(code>=2 || func[code]==0)
    return 0;

  func[code](*n, a, *lda, x_cpy, x_cpy, alpha);

  matrix(a,*n,*n,*lda).diagonal().imag().setZero();

  if(x_cpy!=x)  delete[] x_cpy;

  return 1;
}

int EIGEN_BLAS_FUNC(her2)(char *uplo, int *n, RealScalar *palpha, RealScalar *px, int *incx, RealScalar *py, int *incy, RealScalar *pa, int *lda)
{
  typedef void (*functype)(int, Scalar*, int, const Scalar*, const Scalar*, Scalar);
  static functype func[2];

  static bool init = false;
  if(!init)
  {
    for(int k=0; k<2; ++k)
      func[k] = 0;

    func[UP] = (internal::rank2_update_selector<Scalar,int,Upper>::run);
    func[LO] = (internal::rank2_update_selector<Scalar,int,Lower>::run);

    init = true;
  }

  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* y = reinterpret_cast<Scalar*>(py);
  Scalar* a = reinterpret_cast<Scalar*>(pa);
  Scalar alpha = *reinterpret_cast<Scalar*>(palpha);

  int info = 0;
  if(UPLO(*uplo)==INVALID)                                            info = 1;
  else if(*n<0)                                                       info = 2;
  else if(*incx==0)                                                   info = 5;
  else if(*incy==0)                                                   info = 7;
  else if(*lda<std::max(1,*n))                                        info = 9;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"HER2 ",&info,6);

  if(alpha==Scalar(0))
    return 1;

  Scalar* x_cpy = get_compact_vector(x, *n, *incx);
  Scalar* y_cpy = get_compact_vector(y, *n, *incy);

  int code = UPLO(*uplo);
  if(code>=2 || func[code]==0)
    return 0;

  func[code](*n, a, *lda, x_cpy, y_cpy, alpha);

  matrix(a,*n,*n,*lda).diagonal().imag().setZero();

  if(x_cpy!=x)  delete[] x_cpy;
  if(y_cpy!=y)  delete[] y_cpy;

  return 1;
}

int EIGEN_BLAS_FUNC(geru)(int *m, int *n, RealScalar *palpha, RealScalar *px, int *incx, RealScalar *py, int *incy, RealScalar *pa, int *lda)
{
  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* y = reinterpret_cast<Scalar*>(py);
  Scalar* a = reinterpret_cast<Scalar*>(pa);
  Scalar alpha = *reinterpret_cast<Scalar*>(palpha);

  int info = 0;
       if(*m<0)                                                       info = 1;
  else if(*n<0)                                                       info = 2;
  else if(*incx==0)                                                   info = 5;
  else if(*incy==0)                                                   info = 7;
  else if(*lda<std::max(1,*m))                                        info = 9;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"GERU ",&info,6);

  if(alpha==Scalar(0))
    return 1;

  Scalar* x_cpy = get_compact_vector(x,*m,*incx);
  Scalar* y_cpy = get_compact_vector(y,*n,*incy);

  internal::general_rank1_update<Scalar,int,ColMajor,false,false>::run(*m, *n, a, *lda, x_cpy, y_cpy, alpha);

  if(x_cpy!=x)  delete[] x_cpy;
  if(y_cpy!=y)  delete[] y_cpy;

  return 1;
}

int EIGEN_BLAS_FUNC(gerc)(int *m, int *n, RealScalar *palpha, RealScalar *px, int *incx, RealScalar *py, int *incy, RealScalar *pa, int *lda)
{
  Scalar* x = reinterpret_cast<Scalar*>(px);
  Scalar* y = reinterpret_cast<Scalar*>(py);
  Scalar* a = reinterpret_cast<Scalar*>(pa);
  Scalar alpha = *reinterpret_cast<Scalar*>(palpha);

  int info = 0;
       if(*m<0)                                                       info = 1;
  else if(*n<0)                                                       info = 2;
  else if(*incx==0)                                                   info = 5;
  else if(*incy==0)                                                   info = 7;
  else if(*lda<std::max(1,*m))                                        info = 9;
  if(info)
    return xerbla_(SCALAR_SUFFIX_UP"GERC ",&info,6);

  if(alpha==Scalar(0))
    return 1;

  Scalar* x_cpy = get_compact_vector(x,*m,*incx);
  Scalar* y_cpy = get_compact_vector(y,*n,*incy);

  internal::general_rank1_update<Scalar,int,ColMajor,false,Conj>::run(*m, *n, a, *lda, x_cpy, y_cpy, alpha);

  if(x_cpy!=x)  delete[] x_cpy;
  if(y_cpy!=y)  delete[] y_cpy;

  return 1;
}
