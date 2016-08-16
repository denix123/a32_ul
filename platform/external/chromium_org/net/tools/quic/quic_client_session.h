// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_CLIENT_SESSION_H_
#define NET_TOOLS_QUIC_QUIC_CLIENT_SESSION_H_

#include <string>

#include "base/basictypes.h"
#include "net/quic/quic_client_session_base.h"
#include "net/quic/quic_crypto_client_stream.h"
#include "net/quic/quic_protocol.h"
#include "net/tools/quic/quic_spdy_client_stream.h"

namespace net {

class QuicConnection;
class QuicServerId;
class ReliableQuicStream;

namespace tools {

class QuicClientSession : public QuicClientSessionBase {
 public:
  QuicClientSession(const QuicConfig& config, QuicConnection* connection);
  virtual ~QuicClientSession();

  
  virtual void OnProofValid(
      const QuicCryptoClientConfig::CachedState& cached) OVERRIDE;
  virtual void OnProofVerifyDetailsAvailable(
      const ProofVerifyDetails& verify_details) OVERRIDE;

  void InitializeSession(const QuicServerId& server_id,
                         QuicCryptoClientConfig* config);

  
  virtual QuicSpdyClientStream* CreateOutgoingDataStream() OVERRIDE;
  virtual QuicCryptoClientStream* GetCryptoStream() OVERRIDE;

  
  
  bool CryptoConnect();

  
  
  
  int GetNumSentClientHellos() const;

 protected:
  
  virtual QuicDataStream* CreateIncomingDataStream(QuicStreamId id) OVERRIDE;

 private:
  scoped_ptr<QuicCryptoClientStream> crypto_stream_;

  DISALLOW_COPY_AND_ASSIGN(QuicClientSession);
};

}  
}  

#endif  
