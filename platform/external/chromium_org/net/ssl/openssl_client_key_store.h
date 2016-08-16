// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_OPENSSL_CLIENT_KEY_STORE_H_
#define NET_SSL_OPENSSL_CLIENT_KEY_STORE_H_

#include <openssl/evp.h>

#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "crypto/openssl_util.h"
#include "crypto/scoped_openssl_types.h"
#include "net/base/net_export.h"

namespace net {

class X509Certificate;

class NET_EXPORT OpenSSLClientKeyStore {
 public:
  
  static OpenSSLClientKeyStore* GetInstance();

  
  
  
  
  
  
  
  
  
  
  
  NET_EXPORT bool RecordClientCertPrivateKey(const X509Certificate* cert,
                                             EVP_PKEY* private_key);

  
  
  
  
  crypto::ScopedEVP_PKEY FetchClientCertPrivateKey(const X509Certificate* cert);

  
  void Flush();

 protected:
  OpenSSLClientKeyStore();

  ~OpenSSLClientKeyStore();

  
  
  
  
  void AddKeyPair(EVP_PKEY* pub_key, EVP_PKEY* private_key);

 private:
  
  
  class KeyPair {
   public:
    explicit KeyPair(EVP_PKEY* pub_key, EVP_PKEY* priv_key);
    KeyPair(const KeyPair& other);
    void operator=(const KeyPair& other);
    ~KeyPair();

    crypto::ScopedEVP_PKEY public_key;
    crypto::ScopedEVP_PKEY private_key;

   private:
    KeyPair();  
  };

  
  int FindKeyPairIndex(EVP_PKEY* public_key);

  std::vector<KeyPair> pairs_;

  friend struct DefaultSingletonTraits<OpenSSLClientKeyStore>;

  DISALLOW_COPY_AND_ASSIGN(OpenSSLClientKeyStore);
};

}  

#endif  
