// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_SCOPED_EVP_AEAD_CTX_H_
#define NET_QUIC_CRYPTO_SCOPED_EVP_AEAD_CTX_H_

#include <openssl/evp.h>

#include "base/basictypes.h"

namespace net {

class ScopedEVPAEADCtx {
 public:
  ScopedEVPAEADCtx();
  ~ScopedEVPAEADCtx();

  EVP_AEAD_CTX* get();

 private:
  EVP_AEAD_CTX ctx_;

  DISALLOW_COPY_AND_ASSIGN(ScopedEVPAEADCtx);
};

}  

#endif  
