// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_STRIKE_REGISTER_CLIENT_H_
#define NET_QUIC_CRYPTO_STRIKE_REGISTER_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/quic/crypto/strike_register.h"
#include "net/quic/quic_time.h"

namespace net {

class NET_EXPORT_PRIVATE StrikeRegisterClient {
 public:
  
  
  class NET_EXPORT_PRIVATE ResultCallback {
   public:
    ResultCallback() {}
    virtual ~ResultCallback() {}
    void Run(bool nonce_is_valid_and_unique, InsertStatus nonce_error) {
      RunImpl(nonce_is_valid_and_unique, nonce_error);
      delete this;
    }

   protected:
    virtual void RunImpl(bool nonce_is_valid_and_unique,
                         InsertStatus nonce_error) = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(ResultCallback);
  };

  StrikeRegisterClient() {}
  virtual ~StrikeRegisterClient() {}

  
  virtual bool IsKnownOrbit(base::StringPiece orbit) const = 0;
  
  
  
  
  virtual void VerifyNonceIsValidAndUnique(
      base::StringPiece nonce,
      QuicWallTime now,
      ResultCallback* cb) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(StrikeRegisterClient);
};

}  

#endif  
