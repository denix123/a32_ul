// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CLIENT_SESSION_BASE_H_
#define NET_QUIC_QUIC_CLIENT_SESSION_BASE_H_

#include "net/quic/quic_crypto_client_stream.h"
#include "net/quic/quic_session.h"

namespace net {

class NET_EXPORT_PRIVATE QuicClientSessionBase : public QuicSession {
 public:
  QuicClientSessionBase(QuicConnection* connection,
                        const QuicConfig& config);

  virtual ~QuicClientSessionBase();

  
  
  
  
  
  virtual void OnProofValid(
      const QuicCryptoClientConfig::CachedState& cached) = 0;

  
  
  
  virtual void OnProofVerifyDetailsAvailable(
      const ProofVerifyDetails& verify_details) = 0;

  
  virtual void OnCryptoHandshakeEvent(CryptoHandshakeEvent event) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(QuicClientSessionBase);
};

}  

#endif  
