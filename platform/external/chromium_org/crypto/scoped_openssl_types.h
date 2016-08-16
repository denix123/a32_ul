// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_SCOPED_OPENSSL_TYPES_H_
#define CRYPTO_SCOPED_OPENSSL_TYPES_H_

#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/dsa.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>

#include "base/memory/scoped_ptr.h"

namespace crypto {

template <typename Type, void (*Destroyer)(Type*)>
struct OpenSSLDestroyer {
  void operator()(Type* ptr) const { Destroyer(ptr); }
};

template <typename PointerType, void (*Destroyer)(PointerType*)>
struct ScopedOpenSSL {
  typedef scoped_ptr<PointerType, OpenSSLDestroyer<PointerType, Destroyer> >
      Type;
};

struct OpenSSLFree {
  void operator()(uint8_t* ptr) const { OPENSSL_free(ptr); }
};

typedef ScopedOpenSSL<BIGNUM, BN_free>::Type ScopedBIGNUM;
typedef ScopedOpenSSL<EC_KEY, EC_KEY_free>::Type ScopedEC_KEY;
typedef ScopedOpenSSL<BIO, BIO_free_all>::Type ScopedBIO;
typedef ScopedOpenSSL<DSA, DSA_free>::Type ScopedDSA;
typedef ScopedOpenSSL<ECDSA_SIG, ECDSA_SIG_free>::Type ScopedECDSA_SIG;
typedef ScopedOpenSSL<EC_KEY, EC_KEY_free>::Type ScopedEC_KEY;
typedef ScopedOpenSSL<EVP_MD_CTX, EVP_MD_CTX_destroy>::Type ScopedEVP_MD_CTX;
typedef ScopedOpenSSL<EVP_PKEY, EVP_PKEY_free>::Type ScopedEVP_PKEY;
typedef ScopedOpenSSL<EVP_PKEY_CTX, EVP_PKEY_CTX_free>::Type ScopedEVP_PKEY_CTX;
typedef ScopedOpenSSL<RSA, RSA_free>::Type ScopedRSA;

typedef scoped_ptr<uint8_t, OpenSSLFree> ScopedOpenSSLBytes;

}  

#endif  
