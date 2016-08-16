// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_AES_128_GCM_12_ENCRYPTER_H_
#define NET_QUIC_CRYPTO_AES_128_GCM_12_ENCRYPTER_H_

#include "net/quic/crypto/aead_base_encrypter.h"

namespace net {

class NET_EXPORT_PRIVATE Aes128Gcm12Encrypter : public AeadBaseEncrypter {
 public:
  enum {
    
    kAuthTagSize = 12,
  };

  Aes128Gcm12Encrypter();
  virtual ~Aes128Gcm12Encrypter();

#if !defined(USE_OPENSSL)
 protected:
  
  virtual void FillAeadParams(base::StringPiece nonce,
                              base::StringPiece associated_data,
                              size_t auth_tag_size,
                              AeadParams* aead_params) const OVERRIDE;
#endif

 private:
  DISALLOW_COPY_AND_ASSIGN(Aes128Gcm12Encrypter);
};

}  

#endif  
