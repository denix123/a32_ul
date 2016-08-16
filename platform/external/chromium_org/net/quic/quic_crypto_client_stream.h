// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CRYPTO_CLIENT_STREAM_H_
#define NET_QUIC_QUIC_CRYPTO_CLIENT_STREAM_H_

#include <string>

#include "net/quic/crypto/channel_id.h"
#include "net/quic/crypto/proof_verifier.h"
#include "net/quic/crypto/quic_crypto_client_config.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_crypto_stream.h"
#include "net/quic/quic_server_id.h"

namespace net {

class QuicClientSessionBase;

namespace test {
class CryptoTestUtils;
class QuicClientSessionPeer;
}  

class NET_EXPORT_PRIVATE QuicCryptoClientStream : public QuicCryptoStream {
 public:
  QuicCryptoClientStream(const QuicServerId& server_id,
                         QuicClientSessionBase* session,
                         ProofVerifyContext* verify_context,
                         QuicCryptoClientConfig* crypto_config);
  virtual ~QuicCryptoClientStream();

  
  virtual void OnHandshakeMessage(
      const CryptoHandshakeMessage& message) OVERRIDE;

  
  
  
  virtual bool CryptoConnect();

  
  
  
  int num_sent_client_hellos() const;

  
  bool WasChannelIDSent() const;

  
  
  bool WasChannelIDSourceCallbackRun() const;

 private:
  
  
  
  class ChannelIDSourceCallbackImpl : public ChannelIDSourceCallback {
   public:
    explicit ChannelIDSourceCallbackImpl(QuicCryptoClientStream* stream);
    virtual ~ChannelIDSourceCallbackImpl();

    
    virtual void Run(scoped_ptr<ChannelIDKey>* channel_id_key) OVERRIDE;

    
    
    void Cancel();

   private:
    QuicCryptoClientStream* stream_;
  };

  
  
  
  class ProofVerifierCallbackImpl : public ProofVerifierCallback {
   public:
    explicit ProofVerifierCallbackImpl(QuicCryptoClientStream* stream);
    virtual ~ProofVerifierCallbackImpl();

    
    virtual void Run(bool ok,
                     const string& error_details,
                     scoped_ptr<ProofVerifyDetails>* details) OVERRIDE;

    
    
    void Cancel();

   private:
    QuicCryptoClientStream* stream_;
  };

  friend class test::CryptoTestUtils;
  friend class test::QuicClientSessionPeer;

  enum State {
    STATE_IDLE,
    STATE_INITIALIZE,
    STATE_SEND_CHLO,
    STATE_RECV_REJ,
    STATE_VERIFY_PROOF,
    STATE_VERIFY_PROOF_COMPLETE,
    STATE_GET_CHANNEL_ID,
    STATE_GET_CHANNEL_ID_COMPLETE,
    STATE_RECV_SHLO,
    STATE_INITIALIZE_SCUP,
    STATE_VERIFY_PROOF_DONE,
  };

  
  
  void HandleServerConfigUpdateMessage(
      const CryptoHandshakeMessage& server_config_update);

  
  
  void DoHandshakeLoop(const CryptoHandshakeMessage* in);

  
  
  void DoInitializeServerConfigUpdate(
      QuicCryptoClientConfig::CachedState* cached);

  
  
  QuicAsyncStatus DoVerifyProof(QuicCryptoClientConfig::CachedState* cached);

  
  
  
  QuicErrorCode DoVerifyProofComplete(
      QuicCryptoClientConfig::CachedState* cached);

  
  
  void SetCachedProofValid(QuicCryptoClientConfig::CachedState* cached);

  
  
  bool RequiresChannelID(QuicCryptoClientConfig::CachedState* cached);

  QuicClientSessionBase* client_session();

  State next_state_;
  
  
  int num_client_hellos_;

  QuicCryptoClientConfig* const crypto_config_;

  
  std::string nonce_;
  
  const QuicServerId server_id_;

  
  uint64 generation_counter_;

  
  bool channel_id_sent_;

  
  bool channel_id_source_callback_run_;

  
  
  
  ChannelIDSourceCallbackImpl* channel_id_source_callback_;

  
  
  
  scoped_ptr<ChannelIDKey> channel_id_key_;

  
  
  scoped_ptr<ProofVerifyContext> verify_context_;

  
  
  ProofVerifierCallbackImpl* proof_verify_callback_;

  
  
  
  bool verify_ok_;
  string verify_error_details_;
  scoped_ptr<ProofVerifyDetails> verify_details_;

  DISALLOW_COPY_AND_ASSIGN(QuicCryptoClientStream);
};

}  

#endif  
